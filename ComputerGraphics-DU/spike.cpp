#include "spike.h"
#include <GL/glut.h>
#include <cmath>

const float explosionSize = 20;
const float spikeX = 1.75;
const float spikeY = -1.75;
const float spikeZ = 0;

float currentExplosionSize = 0.01;

bool exploded = false;
bool spikeIsMintColor = true; // 깜빡임을 위한 변수

void drawSpike3D(int currentRemainingSeconds) {
    glEnable(GL_DEPTH);
    if (currentRemainingSeconds <= 0) {
        const float pi = 3.14159265358979323846;
        glTranslatef(spikeX, spikeY, spikeZ);
        glColor3f(20 / 255.f, 20 / 255.f, 20 / 255.f);

        for (int i = 0; i < 50; ++i) {
            float theta1 = i * pi / 50;
            float theta2 = (i + 1) * pi / 50;

            glBegin(GL_QUAD_STRIP);
            for (int j = 0; j <= 50; ++j) {
                float phi = j * 2.0 * pi / 50;

                float x1 = currentExplosionSize * sin(theta1) * cos(phi);
                float y1 = currentExplosionSize * sin(theta1) * sin(phi);
                float z1 = currentExplosionSize * cos(theta1);

                float x2 = currentExplosionSize * sin(theta2) * cos(phi);
                float y2 = currentExplosionSize * sin(theta2) * sin(phi);
                float z2 = currentExplosionSize * cos(theta2);

                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
            }
            glEnd();
        }
        glutTimerFunc(60, explosionTimerCallback, 1); // explode spike
        return;
    }
    const float size = 0.04f;
    if (spikeIsMintColor) glColor3f(0.6f, 1.0f, 0.8f);
    else glColor3f(1.0f, 0.0f, 0.0f);

    glTranslatef(spikeX, spikeY, spikeZ);
    GLUquadricObj* cylinder = gluNewQuadric();
    gluCylinder(cylinder, size, size, 0.2f, 10, 10);

    // 하단을 채우기 위한 디스크 그리기
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.12f);
    gluDisk(cylinder, 0.0, size, 10, 10);
    glPopMatrix();

    gluDeleteQuadric(cylinder);

    // 두 번째 검은 원기둥 그리기 (검은색으로 색상 변경)
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.12f);
    GLUquadricObj* blackCylinder = gluNewQuadric();
    gluCylinder(blackCylinder, size, size, 0.001f, 10, 10);

    gluDeleteQuadric(blackCylinder); //

    // 60도로 떨어진 세로선 3줄 그리기
    glColor3f(0.1f, 0.1f, 0.1f);
    for (int i = 0; i < 3; ++i) {
        glPushMatrix();
        glRotatef(i * 120.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(size, 0.0f, -0.32f);
        gluCylinder(blackCylinder, size / 10, size / 10, 0.4f, 10, 10);
        glPopMatrix();
    }

    // 두 번째 원기둥
    glColor3f(0.1f, 0.1f, 0.1f);
    glTranslatef(0.0f, 0.0f, 0.07f);
    GLUquadricObj* secondCylinder = gluNewQuadric();
    gluCylinder(secondCylinder, size * 1.2, size * 1.2, 0.02f, 11, 11);


    // 두 번째 원기둥의 상단 디스크
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.02f);
    gluDisk(secondCylinder, 0.0, size * 1.2, 11, 11);
    glPopMatrix();

    // 두 번째 원기둥의 하단 디스크
    gluDisk(secondCylinder, 0.0, size * 1.2, 11, 11);

    gluDeleteQuadric(secondCylinder);

    glPushMatrix();

    const float floorSize = 0.08f;
    const float pi = 3.14159265358979323846;
    const float height = -0.15f;
    const int sides = 10;

    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= sides; ++i) {
        float angle = 2.0f * pi * static_cast<float>(i) / static_cast<float>(sides);
        float x = floorSize * cos(angle);
        float y = floorSize * sin(angle);

        glVertex3f(x, y, -0.2f);
        glVertex3f(x, y, height);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i <= sides; ++i) {
        float angle = 2.0f * pi * static_cast<float>(i) / static_cast<float>(sides);
        float x = floorSize * cos(angle);
        float y = floorSize * sin(angle);

        glVertex3f(x, y, height);
    }
    glEnd();
    glPopMatrix();

    if (currentRemainingSeconds <= 15) {
        spikeIsMintColor = currentRemainingSeconds % 2 == 0;
    }
}

void explosionTimerCallback(int value) {
    currentExplosionSize += 0.01;
    glutPostRedisplay();
    if (currentExplosionSize < explosionSize) {
        glutTimerFunc(10, explosionTimerCallback, 1);
    }
}