#include <GL/glut.h>
#include "drawutil2d.h"
#include "camera.h"
#include <random>
#include <iomanip>
#include <cmath>

const float defuseRadius = 0.5f;
const int defuseSpeed = 50;

float defuseProgress = 0.f;
float distance = 2.f;
bool defusing = false;

void drawCrosshair2D() {
    const int crosshairSize = 10;

    glColor3f(1.0f, 1.0f, 1.0f); // 흰색으로 설정
    glLineWidth(1.f);
    // 수평선
    glBegin(GL_LINES);
    glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2 - crosshairSize, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2 + crosshairSize, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    glEnd();

    // 수직선
    glBegin(GL_LINES);
    glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2 - crosshairSize);
    glVertex2f(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2 + crosshairSize);
    glEnd();
}

void drawInterface2D(int remainingSeconds, int leftEnimies, Camera* camera) {
    if (remainingSeconds > 0) {
        const float spikeX = 1.75;
        const float spikeY = -1.75;
        const float spikeZ = 0;
        const float x = camera->getX();
        const float y = camera->getY();
        const float z = camera->getZ();
        distance = sqrt(pow(spikeX - x, 2) + pow(spikeY - y, 2) + pow(spikeZ - z, 2));
        if (distance <= defuseRadius) {
            glBegin(GL_POLYGON);
            glColor4ub(250, 237, 125, 255);
            int length = 223 * defuseProgress;
            glVertex2f(580, 154);
            glVertex2f(580 + length, 154);
            glVertex2f(580 + length, 184);
            glVertex2f(580, 184);
            glEnd();

            glPushMatrix();
            glColor4ub(255, 255, 255, 255);
            glTranslatef(645, 150, 0);
            glRotatef(180, 1, 0, 0);
            glScalef(0.15, 0.15, 0);
            const char* s = "DEFUSING";
            for (int i = 0; i < 9; i++) {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
            }
            glPopMatrix();

            glEnable(GL_BLEND);
            glBegin(GL_POLYGON);
            glColor4ub(144, 144, 144, 200);
            glVertex2f(580 + 60, 126);
            glVertex2f(580 + 60, 156);
            glVertex2f(803 - 60, 156);
            glVertex2f(803 - 60, 126);
            glEnd();
            glDisable(GL_BLEND);

            glBegin(GL_LINES);
            glColor4ub(255, 255, 255, 255);
            glVertex2f(691, 154);
            glVertex2f(691, 184);
            glEnd();

            glBegin(GL_LINES);
            glVertex2f(580, 154);
            glVertex2f(803, 154);
            glVertex2f(803, 184);
            glVertex2f(580, 184);
            glEnd();

            glBegin(GL_POLYGON);
            glColor4ub(72, 72, 72, 255);
            glVertex2f(580, 154);
            glVertex2f(803, 154);
            glVertex2f(803, 184);
            glVertex2f(580, 184);
            glEnd();


            if (!defusing) {
                defusing = true;
                glutTimerFunc(defuseSpeed, spikeDefuseTimerCallback, 0);
            }
        }
        else {
            defusing = false;
            defuseProgress = 0.f;
        }
    }

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int widthSpace = 100;
    int heightSpace = 10;
    int height = 70;

    // 남은 시간 표시
    int minutes = remainingSeconds / 60;
    int seconds = remainingSeconds % 60;

    static char buffer[6];
    sprintf_s(buffer, "%02d:%02d", minutes, seconds);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(windowWidth / 2 - 80, height / 2 + heightSpace + 25, 0);
    if (remainingSeconds <= 15) { // 15초 이하로 남으면 시간을 빨간색으로 표시
        glColor4ub(255, 0, 0, 200);
    }
    else {
        glColor4ub(255, 255, 255, 200);
    }
    glScalef(0.5, 0.5, 0);
    glRotatef(180, 1, 0, 0);
    for (int i = 0; i < 6; ++i) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, buffer[i]);
    }
    glPopMatrix();

    // 파란팀 남은 인원 그리기 (1명, 초록 원)
    if (remainingSeconds > 0) {
        glPushMatrix();
        glColor4ub(0, 255, 0, 200);
        glTranslatef(400, height / 2 + heightSpace, 0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
        for (int j = 0; j <= 360; ++j) {
            float radian = j * 3.14159265 / 180.0;
            glVertex2f(cos(radian) * 25.0, sin(radian) * 25.0);
        }
        glEnd();
        glPopMatrix();
    }

    // 빨간팀 남은 인원 그리기 (빨간 원)
    glPushMatrix();
    glColor4ub(255, 0, 0, 200);
    int enemyDrawInterval = 50;
    glTranslatef(windowWidth / 2 - widthSpace + 300, height / 2 + heightSpace, 0);
    for (int i = 0; i < leftEnimies; i++) {
        glTranslatef(60, 0, 0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
        for (int j = 0; j <= 360; ++j) {
            float radian = j * 3.14159265 / 180.0;
            glVertex2f(cos(radian) * 25.0, sin(radian) * 25.0);
        }
        glEnd();
    }
    glPopMatrix();

    // 백그라운드 박스
    glEnable(GL_BLEND);
    glBegin(GL_POLYGON);
    glColor4ub(144, 144, 144, 200);
    glVertex2f(widthSpace, heightSpace);
    glVertex2f(windowWidth - widthSpace, heightSpace);
    glVertex2f(windowWidth - widthSpace, heightSpace + height);
    glVertex2f(widthSpace, heightSpace + height);
    glEnd();
    glDisable(GL_BLEND);

    if (remainingSeconds <= 0) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glColor4ub(255, 255, 255, 255);
        glTranslatef(605, 205, 0);
        glScalef(0.5, 0.5, 0);
        glRotatef(180, 1, 0, 0);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 'L');
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 'O');
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 'S');
        glutStrokeCharacter(GLUT_STROKE_ROMAN, 'T');

        glScalef(0.3, 0.3, 0);
        glTranslatef(-1090, -300, 0);
        const char* s = "TEAM ELIMINATED";
        for (int i = 0; i < 16; ++i) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, s[i]);
        }
        glPopMatrix();

        glEnable(GL_BLEND);
        glBegin(GL_POLYGON);
        const int start = windowWidth / 2 - 255;
        glColor4ub(155, 36, 36, 200);
        glVertex2f(start + 100, 100);
        glVertex2f(start + 400, 100);
        glVertex2f(start + 400, 300);
        glVertex2f(start + 100, 300);
        glEnd();
        glDisable(GL_BLEND);
    }
}

void spikeDefuseTimerCallback(int value) {
    if (defuseProgress >= 1.f) {
        return;
    }
    defuseProgress += 0.01;
    glutPostRedisplay();
    if (distance <= defuseRadius) {
        glutTimerFunc(defuseSpeed, spikeDefuseTimerCallback, defuseProgress);
    }
}