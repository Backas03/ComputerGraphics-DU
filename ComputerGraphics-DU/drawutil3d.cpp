#include <GL/glut.h>
#include <cmath>
#include "drawutil3d.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void drawFloor3D() {
    glColor3f(0.62f, 0.62f, 0.62f);// ¹Ù´Ú »ö»ó
    glBegin(GL_QUADS);
    glVertex2f(-2.0f, -2.0f);
    glVertex2f(2.0f, -2.0f);
    glVertex2f(2.0f, 2.0f);
    glVertex2f(-2.0f, 2.0f);
    glEnd();
}

void drawCharactor3D() {
    const float radius = 0.075f;
    const float pi = 3.14159265358979323846;

    glColor3f(1.0, 0, 0);

    for (int i = 0; i < 50; ++i) {
        float theta1 = i * pi / 50;
        float theta2 = (i + 1) * pi / 50;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= 50; ++j) {
            float phi = j * 2.0 * pi / 50;

            float x1 = radius * sin(theta1) * cos(phi);
            float y1 = radius * sin(theta1) * sin(phi);
            float z1 = radius * cos(theta1);

            float x2 = radius * sin(theta2) * cos(phi);
            float y2 = radius * sin(theta2) * sin(phi);
            float z2 = radius * cos(theta2);

            glVertex3f(x1, y1, z1 + 0.225);
            glVertex3f(x2, y2, z2 + 0.225);
        }
        glEnd();
    }
    // Áß°£ ºÎºÐ
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 50; ++i) {
        float theta = (i / static_cast<float>(50)) * 2.0 * pi;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex3f(x, y, 0.15 / 2.0 + 0.15);
        glVertex3f(x, y, -0.15 / 2.0 + 0.15);
    }
    glEnd();
    for (int i = 0; i < 50; ++i) {
        float theta1 = i * pi / 50;
        float theta2 = (i + 1) * pi / 50;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= 50; ++j) {
            float phi = j * 2.0 * pi / 50;

            float x1 = radius * sin(theta1) * cos(phi);
            float y1 = radius * sin(theta1) * sin(phi);
            float z1 = radius * cos(theta1);

            float x2 = radius * sin(theta2) * cos(phi);
            float y2 = radius * sin(theta2) * sin(phi);
            float z2 = radius * cos(theta2);

            glVertex3f(x1, y1, z1 + 0.075);
            glVertex3f(x2, y2, z2 + 0.075);
        }
        glEnd();
    }
}

void drawWalls3D() {
    glColor3f(0.9f, 0.8f, 0.7f);

    // ¹Ù´ÚÀ» °¨½Î´Â ³× ¸é¿¡ º® Ãß°¡
    glBegin(GL_QUADS);

    // À­ÂÊ º®
    glVertex3f(2.0f, 2.0f, 0.0f);
    glVertex3f(2.0f, 2.0f, 0.6f);
    glVertex3f(2.0f, -2.0f, 0.6f);
    glVertex3f(2.0f, -2.0f, 0.0f);

    glVertex3f(2.0f, 2.0f, 0.0f);
    glVertex3f(2.0f, 2.0f, 0.6f);
    glVertex3f(-2.0f, 2.0f, 0.6f);
    glVertex3f(-2.0f, 2.0f, 0.0f);

    glVertex3f(-2.0f, -2.0f, 0.0f);
    glVertex3f(-2.0f, -2.0f, 0.6f);
    glVertex3f(-2.0f, 2.0f, 0.6f);
    glVertex3f(-2.0f, 2.0f, 0.0f);

    glVertex3f(-2.0f, -2.0f, 0.0f);
    glVertex3f(-2.0f, -2.0f, 0.6f);
    glVertex3f(2.0f, -2.0f, 0.6f);
    glVertex3f(2.0f, -2.0f, 0.0f);

    glEnd();

    // »ç°¢Çü »ö»ó ¼³Á¤
    glColor3f(0.6f, 0.4f, 0.2f);

    // LEFT º®¸é »ç°¢Çü
    glBegin(GL_QUADS);
    // ¾Õ¸é
    glVertex3f(2.0f, 2.0f, 0.6f);
    glVertex3f(2.0f, 1.85f, 0.6f);
    glVertex3f(-2.0f, 1.85f, 0.6f);
    glVertex3f(-2.0f, 2.0f, 0.6f);

    // µÞ¸é (³»Ãß·²¸µ)
    glVertex3f(2.0f, 2.0f, 0.7f);   // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(2.0f, 2.0f, 0.6f);   // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(-2.0f, 2.0f, 0.6f);  // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(-2.0f, 2.0f, 0.7f);   // z-ÁÂÇ¥ Á¶Á¤
    glEnd();

    // Bottom º®¸é »ç°¢Çü
    glBegin(GL_QUADS);
    // ¾Õ¸é
    glVertex3f(-2.0f, 2.0f, 0.6f);
    glVertex3f(-1.85f, 2.0f, 0.6f);
    glVertex3f(-1.85f, -2.0f, 0.6f);
    glVertex3f(-2.0f, -2.0f, 0.6f);

    // µÞ¸é (³»Ãß·²¸µ)
    glVertex3f(-2.0f, 2.0f, 0.7f);   // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(-1.85f, 2.0f, 0.6f);  // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(-1.85f, -2.0f, 0.6f); // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(-2.0f, -2.0f, 0.7f);   // z-ÁÂÇ¥ Á¶Á¤
    glEnd();

    // Right º®¸é »ç°¢Çü
    glBegin(GL_QUADS);
    // ¾Õ¸é
    glVertex3f(-1.85f, -2.0f, 0.6f);
    glVertex3f(-1.85f, -1.85f, 0.6f);
    glVertex3f(2.0f, -1.85f, 0.6f);
    glVertex3f(2.0f, -2.0f, 0.6f);

    // µÞ¸é (³»Ãß·²¸µ)
    glVertex3f(-2.0f, -2.0f, 0.7f);   // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(-2.0f, -1.85f, 0.6f);  // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(2.0f, -1.85f, 0.6f);    // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(2.0f, -2.0f, 0.7f);     // z-ÁÂÇ¥ Á¶Á¤
    glEnd();

    // Top º®¸é »ç°¢Çü
    glBegin(GL_QUADS);
    // ¾Õ¸é
    glVertex3f(2.0f, -1.85f, 0.6f);
    glVertex3f(1.85f, -1.85f, 0.6f);
    glVertex3f(1.85f, 2.0f, 0.6f);
    glVertex3f(2.0f, 2.0f, 0.6f);

    // µÞ¸é (³»Ãß·²¸µ)
    glVertex3f(2.0f, -2.0f, 0.7f);   // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(1.85f, -2.0f, 0.6f);  // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(1.85f, 2.0f, 0.6f);    // z-ÁÂÇ¥ Á¶Á¤
    glVertex3f(2.0f, 2.0f, 0.7f);     // z-ÁÂÇ¥ Á¶Á¤
    glEnd();
}

void drawBox3DAt(float x, float y, float z, float size, float depth) {
    glPushMatrix();
    glTranslatef(x, y, z - size / 2); // ¹Ù´Ú°ú Á¤·Ä
    glScalef(size, size, depth);

    // »óÀÚ ±×¸®±â
    glColor3f(100 / 255.f, 190 / 255.f, 140 / 255.f); // ¿Á»ö (RGB)À¸·Î ¼³Á¤
    glBegin(GL_QUADS);
    // Àü¸é ¸é
    glVertex3f(-0.7f, -0.7f, 0.7f);
    glVertex3f(0.7f, -0.7f, 0.7f);
    glVertex3f(0.7f, 0.7f, 0.7f);
    glVertex3f(-0.7f, 0.7f, 0.7f);
    // back side
    glVertex3f(-0.7f, -0.7f, -0.7f);
    glVertex3f(0.7f, -0.7f, -0.7f);
    glVertex3f(0.7f, 0.7f, -0.7f);
    glVertex3f(-0.7f, 0.7f, -0.7f);
    // left side
    glVertex3f(-0.7f, -0.7f, 0.7f);
    glVertex3f(-0.7f, 0.7f, 0.7f);
    glVertex3f(-0.7f, 0.7f, -0.7f);
    glVertex3f(-0.7f, -0.7f, -0.7f);
    // right side
    glVertex3f(0.7f, -0.7f, 0.7f);
    glVertex3f(0.7f, 0.7f, 0.7f);
    glVertex3f(0.7f, 0.7f, -0.7f);
    glVertex3f(0.7f, -0.7f, -0.7f);
    // top side
    glVertex3f(-0.7f, 0.7f, 0.7f);
    glVertex3f(0.7f, 0.7f, 0.7f);
    glVertex3f(0.7f, 0.7f, -0.7f);
    glVertex3f(-0.7f, 0.7f, -0.7f);
    // bottom side
    glVertex3f(-0.7f, -0.7f, 0.7f);
    glVertex3f(0.7f, -0.7f, 0.7f);
    glVertex3f(0.7f, -0.7f, -0.7f);
    glVertex3f(-0.7f, -0.7f, -0.7f);
    glEnd();

    glLineWidth(10.0f); // Set line thickness to 1.0
    glColor3f(0.5f, 0.5f, 0.5f); // Gray color (RGB)

    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.7f, -0.7f, 0.7f);
    glVertex3f(0.7f, -0.7f, 0.7f);
    glVertex3f(0.7f, 0.7f, 0.7f);
    glVertex3f(-0.7f, 0.7f, 0.7f);
    glEnd();

    // back side border
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.7f, -0.7f, -0.7f);
    glVertex3f(0.7f, -0.7f, -0.7f);
    glVertex3f(0.7f, 0.7f, -0.7f);
    glVertex3f(-0.7f, 0.7f, -0.7f);
    glVertex3f(-0.7f, -0.7f, -0.7f); // start diagonally
    glVertex3f(0.7f, 0.7f, -0.7f); // diagonal end
    glEnd();

    // left side border
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.7f, -0.7f, 0.7f);
    glVertex3f(-0.7f, 0.7f, 0.7f);
    glVertex3f(-0.7f, 0.7f, -0.7f);
    glVertex3f(-0.7f, -0.7f, -0.7f);
    glVertex3f(-0.7f, -0.7f, 0.7f); // start diagonally
    glVertex3f(-0.7f, 0.7f, -0.7f); // diagonal end
    glEnd();

    // border on right side
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.7f, -0.7f, 0.7f);
    glVertex3f(0.7f, 0.7f, 0.7f);
    glVertex3f(0.7f, 0.7f, -0.7f);
    glVertex3f(0.7f, -0.7f, -0.7f);
    glVertex3f(0.7f, -0.7f, 0.7f); // start diagonally
    glVertex3f(0.7f, 0.7f, -0.7f); // diagonal end
    glEnd();

    // top side border
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.7f, 0.7f, 0.7f);
    glVertex3f(0.7f, 0.7f, 0.7f);
    glVertex3f(0.7f, 0.7f, -0.7f);
    glVertex3f(-0.7f, 0.7f, -0.7f);
    glVertex3f(-0.7f, 0.7f, 0.7f); // start diagonally
    glVertex3f(0.7f, 0.7f, -0.7f); // diagonal end
    glEnd();

    // bottom border
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.7f, -0.7f, 0.7f);
    glVertex3f(0.7f, -0.7f, 0.7f);
    glVertex3f(0.7f, -0.7f, -0.7f);
    glVertex3f(-0.7f, -0.7f, -0.7f);
    glVertex3f(-0.7f, -0.7f, 0.7f); // start diagonally
    glVertex3f(0.7f, -0.7f, -0.7f); // diagonal end
    glEnd();

    glPopMatrix();
}

void drawGun3D(Camera* camera) {
    // Calculate gun orientation based on camera orientation
    float gunYaw = camera->getYaw() - 1.6;  // Adjust as needed
    float gunPitch = camera->getPitch();     // Adjust as needed

    // Get camera position
    float cameraX = camera->getX();
    float cameraY = camera->getY();
    float cameraZ = camera->getZ();

    // Calculate gun position relative to camera
    float gunOffsetX = cos(camera->getYaw()) * 0.2 + cos(gunYaw) * 0.2;
    float gunOffsetY = sin(camera->getYaw()) * 0.2 + sin(gunYaw) * 0.2;
    float gunOffsetZ = sin(camera->getPitch()) * 0.2 + sin(gunPitch) * 0.1;

    // Set up the gun transformation
    glPushMatrix();
    glTranslatef(cameraX + gunOffsetX, cameraY + gunOffsetY, cameraZ + gunOffsetZ - 0.1);
    glRotatef((gunYaw - 0.8) * 180.0 / M_PI, 0.0, 0.0, 1.0);
    //glRotatef((gunPitch - 0.6) * 180.0 / M_PI, 0.0, 1.0, 0.0);

    // Draw the gun
    glColor3f(0.5f, 0.5f, 0.5f); // Gun body color (gray)

    // Draw gun body
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.025f);
    glScalef(0.1, 0.01f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(0.1f, 0.1f, 0.1f); // Magazine and handle color (black)

    // Draw magazine
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.02f);
    glScalef(0.005f, 0.005f, 0.015f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Draw handle
    glPushMatrix();
    glTranslatef(-0.01f, 0.0f, 0.02f);
    glScalef(0.004f, 0.004f, 0.015f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Reset transformation
    glPopMatrix();
}