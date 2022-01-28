#pragma once

#include "textures.h"

/**
 * @brief Draw rectangle with a texture
 * @param width
 * @param height
 */
void DrawDebugRect(float width, float height);

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

    int getHour();
    int getMinute();
    int getSecond();

    void setRotateHourArrow(float degree);
    void setRotateMinuteArrow(float degree);
    void setRotateSecondArrow(float degree);

private:
    void drawCircle();
    void drawBackground();
    void drawHourArrow();
    void drawMinuteArrow();
    void drawSecondArrow();

    Texture circle_;
    Texture background_;
    Texture hours_;
    Texture minutes_;
    Texture seconds_;

    int curHour_;
    int curMinute_;
    int curSecond_;

    float rotateHours_;
    float rotateMinutes_;
    float rotateSeconds_;
};
