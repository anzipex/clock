#include <iostream>
#include <chrono>
#include <GL/glut.h>
#include "Clock.h"

Clock *myclock = nullptr;
uint64_t GetMillisec();
uint64_t PrevUpdateTime = GetMillisec();
float UpdatePerSecond = 60;
uint64_t PrevFrameTime = GetMillisec();
float FPS = 60;

uint64_t GetMillisec() {
    using namespace std;
    using namespace chrono;

    const auto timePoint = high_resolution_clock::now();
    const auto duration = timePoint.time_since_epoch();
    return duration_cast<milliseconds>(duration).count();
}

void GetTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    myclock->saveCurrentHour(30.0F * ltm->tm_hour);
    myclock->saveCurrentMinute(6.0F * ltm->tm_min);
    myclock->saveCurrentSecond(6.0F * ltm->tm_sec);
}

void DisplayFunc() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    GetTime();
    myclock->draw();

    glutSwapBuffers();
}

void IdleFunc() {
    const auto time = GetMillisec();
    auto updateTimeExp = time - PrevUpdateTime;

    while (updateTimeExp > (1000 / UpdatePerSecond)) {

        myclock->setRotateHourArrow(myclock->getHour());
        myclock->setRotateMinuteArrow(myclock->getMinute());
        myclock->setRotateSecondArrow(myclock->getSecond());

        updateTimeExp -= 1000 / UpdatePerSecond;
        PrevUpdateTime = time;
    }

    const auto frameTimeExp = time - PrevFrameTime;

    if (frameTimeExp > (1000 / FPS)) {
        glutPostRedisplay();
        PrevFrameTime = time;
    }
}

void ReshapeFunc(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, 0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void DisplayClock(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Clock");
    glutDisplayFunc(DisplayFunc);
    glutIdleFunc(IdleFunc);
    glutReshapeFunc(ReshapeFunc);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char** argv) {
    DisplayClock(argc, argv);
    myclock = new Clock;
    glutMainLoop();
    delete myclock;
    return 0;
}
