#include <iostream>
#include <GL/glut.h>
#include "textures.h"
#include "Clock.h"

void DrawDebugRect(const float width, const float height) {
    const auto hw = width / 2;
    const auto hh = height / 2;

    glBegin(GL_LINE_LOOP);

    glColor3ub(255, 0, 0);
    glVertex2f(hw, hh);

    glColor3ub(0, 255, 0);
    glVertex2f(-hw, hh);

    glColor3ub(0, 0, 255);
    glVertex2f(-hw, -hh);

    glColor3ub(255, 255, 255);
    glVertex2f(hw, -hh);

    glEnd();
}

void DrawRect(int width, int height) {
    const auto hw = width / 2;
    const auto hh = height / 2;

    glBegin(GL_QUADS);
    glVertex2f(hw, hh);
    glVertex2f(-hw, hh);
    glVertex2f(-hw, -hh);
    glVertex2f(hw, -hh);
    glEnd();
}

void DrawTexture(Texture *texture) {
    glEnable(GL_TEXTURE_2D);

    texture->bind();

    const auto hw = texture->width() / 2;
    const auto hh = texture->height() / 2;

    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(hw, hh);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-hw, hh);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-hw, -hh);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(hw, -hh);

    glEnd();

    glDisable(GL_TEXTURE_2D);

#ifndef NDEBUG
    // DrawDebugRect(texture->width(), texture->height());
#endif // NDEBUG
}

Clock::Clock() :
circle_("textures/circleMetal.png"),
background_("textures/background.png"),
hours_("textures/hourArrow.png"),
minutes_("textures/minuteArrow.png"),
seconds_("textures/secondArrow.png"),
curHour_(0),
curMinute_(0),
curSecond_(0),
rotateHours_(0),
rotateMinutes_(0),
rotateSeconds_(0) {
}

void Clock::drawCircle() {
    glPushMatrix();
    DrawTexture(&circle_);
    glPopMatrix();
}

void Clock::drawHourArrow() {
    glPushMatrix();
    glRotatef(rotateHours_, 0, 0, 1.0f);
    glTranslatef(0, 62.5f, 0);
    DrawTexture(&hours_);
    glPopMatrix();
}

void Clock::drawMinuteArrow() {
    glPushMatrix();
    glRotatef(rotateMinutes_, 0, 0, 1.0f);
    glTranslatef(0, 90.0f, 0);
    DrawTexture(&minutes_);
    glPopMatrix();
}

void Clock::drawSecondArrow() {
    glPushMatrix();
    glRotatef(rotateSeconds_, 0, 0, 1.0f);
    glTranslatef(0, 91.0f, 0);
    DrawTexture(&seconds_);
    glPopMatrix();
}

void Clock::drawBackground() {
    glPushMatrix();
    DrawTexture(&background_);
    glPopMatrix();
}

void Clock::saveCurrentHour(int hour) {
    curHour_ = hour;
}

void Clock::saveCurrentMinute(int minute) {
    curMinute_ = minute;
}

void Clock::saveCurrentSecond(int second) {
    curSecond_ = second;
}

int Clock::getHour() {
    return curHour_;
}

int Clock::getMinute() {
    return curMinute_;
}

int Clock::getSecond() {
    return curSecond_;
}

void Clock::setRotateHourArrow(float degree) {
    rotateHours_ = -degree;
}

void Clock::setRotateMinuteArrow(float degree) {
    rotateMinutes_ = -degree;
}

void Clock::setRotateSecondArrow(float degree) {
    rotateSeconds_ = -degree;
}

void Clock::draw() {
    drawBackground();
    drawHourArrow();
    drawMinuteArrow();
    drawSecondArrow();
    drawCircle();
}
