#pragma once
#include "camera.h"
#include <iostream>
#include <unordered_set>
#include <cmath>

struct Bullet {
    float x;
    float y;
    float z;
    float yaw, pitch;
    float speed;
    bool active;

    Bullet(float x, float y, float z, float yaw, float pitch) : 
        x(x),
        y(y),
        z(z),
        yaw(yaw),
        pitch(pitch),
        speed(0.2f),
        active(true) {}
};

class Gun {
public:
    Gun(Camera* camera);
    void shoot();
    void updateBullets();
private:
    Camera* camera;
    std::vector<Bullet> bullets;
};