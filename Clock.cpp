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
_circle("textures/circleMetal.png"),
_background("textures/background.png"),
_hours("textures/hourArrow.png"),
_minutes("textures/minuteArrow.png"),
_seconds("textures/secondArrow.png"),
_curHour(0),
_curMinute(0),
_curSecond(0),
_rotateHours(0),
_rotateMinutes(0),
_rotateSeconds(0) {
}

void Clock::drawCircle() {
    glPushMatrix();
    DrawTexture(&_circle);
    glPopMatrix();
}

void Clock::drawHourArrow() {
    glPushMatrix();
    glRotatef(_rotateHours, 0, 0, 1.0f);
    glTranslatef(0, 62.5f, 0);
    DrawTexture(&_hours);
    glPopMatrix();
}

void Clock::drawMinuteArrow() {
    glPushMatrix();
    glRotatef(_rotateMinutes, 0, 0, 1.0f);
    glTranslatef(0, 90.0f, 0);
    DrawTexture(&_minutes);
    glPopMatrix();
}

void Clock::drawSecondArrow() {
    glPushMatrix();
    glRotatef(_rotateSeconds, 0, 0, 1.0f);
    glTranslatef(0, 91.0f, 0);
    DrawTexture(&_seconds);
    glPopMatrix();
}

void Clock::drawBackground() {
    glPushMatrix();
    DrawTexture(&_background);
    glPopMatrix();
}

void Clock::saveCurrentHour(int hour) {
    _curHour = hour;
}

void Clock::saveCurrentMinute(int minute) {
    _curMinute = minute;
}

void Clock::saveCurrentSecond(int second) {
    _curSecond = second;
}

const int Clock::getHour() {
    return _curHour;
}

const int Clock::getMinute() {
    return _curMinute;
}

const int Clock::getSecond() {
    return _curSecond;
}

void Clock::setRotateHourArrow(float degree) {
    _rotateHours = -degree;
}

void Clock::setRotateMinuteArrow(float degree) {
    _rotateMinutes = -degree;
}

void Clock::setRotateSecondArrow(float degree) {
    _rotateSeconds = -degree;
}

void Clock::draw() {
    drawBackground();
    drawHourArrow();
    drawMinuteArrow();
    drawSecondArrow();
    drawCircle();
}
