#pragma once
#include "camera.h"

void drawCrosshair2D();
void drawInterface2D(int remainingSeconds, int leftEnimies, Camera* camera);
void renderBitmapString(float x, float y, const char* string);
void spikeDefuseTimerCallback(int value);