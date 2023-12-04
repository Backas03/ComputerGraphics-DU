#include "gun.h"
#include <GL/glut.h>

Gun::Gun(Camera* camera) {
	this->camera = camera;
}

void Gun::shoot() {
    Bullet bullet = Bullet(
        this->camera->getX(),
        this->camera->getY(),
        this->camera->getZ(),
        this->camera->getYaw(),
        this->camera->getPitch()
    );
    this->bullets.push_back(bullet);
}

void Gun::updateBullets() {
    const float maxDistance = 4.f;
    for (size_t i = 0; i < this->bullets.size(); ++i) {
        Bullet& bullet = this->bullets[i];
        if (bullet.active) {
            bullet.x += 3 * bullet.speed * cos(bullet.yaw);
            bullet.y += 3 * bullet.speed * sin(bullet.yaw);
            bullet.z += 3 * bullet.speed * sin(bullet.pitch);

            // draw bullet
            glPushMatrix();
            glTranslatef(bullet.x, bullet.y, bullet.z);

            glRotatef(cos(bullet.yaw) * 90, 1.0f, 0.0f, 0.0f);
            glRotatef(sin(bullet.yaw) * 90, 0.0f, 1.0f, 0.0f);
            glRotatef(sin(bullet.pitch) * 90, 0.0f, 0.0f, 1.0f);

            GLUquadricObj* quadric = gluNewQuadric();
            gluQuadricDrawStyle(quadric, GLU_FILL);
            gluCylinder(quadric, 0.005f, 0.005f, 0.2f, 10, 10);
            gluDeleteQuadric(quadric);

            glPopMatrix();
            if (bullet.x >= maxDistance || bullet.x <= -maxDistance ||
                bullet.y >= maxDistance || bullet.y <= -maxDistance ||
                bullet.z >= maxDistance || bullet.z <= -maxDistance) {
                bullet.active = false;
            }
            continue;
        }
        glutPostRedisplay();
        this->bullets.erase(this->bullets.begin() + i);
    }
}
