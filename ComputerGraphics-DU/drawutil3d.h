#pragma once
#include "camera.h"

void drawFloor3D();
void drawCharactor3D();
void drawWalls3D();
void drawBox3DAt(float x, float y, float z, float size, float depth);
void drawGun3D(Camera* camera);