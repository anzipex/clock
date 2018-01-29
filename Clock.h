/** 
 * @file Clock.h
 * @brief Description of class Clock
 * @author a.akulin
 * @date January 25, 2018
 */

#ifndef CLOCK_H
#define CLOCK_H

#include "textures.h"

/**
 * @brief Draw a rectangle with a texture
 * @param width
 * @param height
 */
void DrawDebugRect(const float width, const float height);

/**
 * @brief Draw a texture
 * @param texture
 */
void DrawTexture(Texture *texture);

/**
 * @brief Draw a rectangle that draws a texture
 * @param width
 * @param height
 */
void DrawRect(int width, int height);

class Clock {
public:
    Clock();

    void draw();
    void saveCurrentHour(int hour);
    void saveCurrentMinute(int minute);
    void saveCurrentSecond(int second);

    const int getHour();
    const int getMinute();
    const int getSecond();

    void setRotateHourArrow(float degree);
    void setRotateMinuteArrow(float degree);
    void setRotateSecondArrow(float degree);

private:
    void drawCircle();
    void drawBackground();
    void drawHourArrow();
    void drawMinuteArrow();
    void drawSecondArrow();

    Texture _circle;
    Texture _background;
    Texture _hours;
    Texture _minutes;
    Texture _seconds;

    int _curHour;
    int _curMinute;
    int _curSecond;

    float _rotateHours;
    float _rotateMinutes;
    float _rotateSeconds;
};

#endif /* CLOCK_H */