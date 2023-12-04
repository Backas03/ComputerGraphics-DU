#include <GL/glut.h>
#include <cmath>
#include <unordered_set>
#include "camera.h"
#include "gun.h"
#include "drawutil3d.h"
#include "drawutil2d.h"
#include "spike.h"

using namespace std;

Camera camera = Camera();
Gun gun = Gun(&camera);

int currentRemainingSeconds;
int leftEnimies;
bool enemyStatus[5] = {true, true, true, true, true};
float enemyLocation[5][3] = {
    {0.3, -1.8, 0.3},
    {0.9, -1.5, 0.0},
    {1.6, 1.4, 0.0},
    {-1.85, -0.218, 0.3},
    {-1.2, 1.2, 0.0}
};

void drawScene() {
    glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    /* 3d start */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const float cameraX = camera.getX();
    const float cameraY = camera.getY();
    const float cameraZ = camera.getZ();
    const float cameraYaw = camera.getYaw();
    const float cameraPitch = camera.getPitch();
    gluLookAt(cameraX, cameraY, cameraZ,
        cameraX + cos(cameraYaw) * cos(cameraPitch),
        cameraY + sin(cameraYaw) * cos(cameraPitch),
        cameraZ + sin(cameraPitch),
        0.0, 0.0, 1.0);
    drawFloor3D();
    drawWalls3D();
    if (currentRemainingSeconds > 0) drawGun3D(&camera);

    drawBox3DAt(-1.85f, -0.5f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(-1.85f, -0.5f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(-1.57f, -0.5f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(-1.57f, -0.5f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(-1.29f, -0.5f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(-1.29f, -0.5f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(-1.85f, -0.218f, 0.25f, 0.2f, 0.2f);//ㄴ모양 box

    drawBox3DAt(0.0f, -1.85f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -1.85f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -1.57f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -1.57f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -1.29f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -1.29f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -1.01f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -1.01f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -0.73f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -0.73f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -0.45f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -0.45f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -0.17f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, -0.17f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, 0.11f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, 0.11f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, 0.39f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.0f, 0.39f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(-0.282f, 0.67f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(-0.282f, 0.67f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(-0.562f, 0.67f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(-0.562f, 0.67f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(-0.842f, 0.67f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(-0.842f, 0.67f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.28f, -1.85f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.56f, -1.85f, 0.25f, 0.2f, 0.2f);//ㄱ모양 box

    drawBox3DAt(1.25f, -1.85f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(1.25f, -1.85f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(1.25f, -1.57f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(1.25f, -1.57f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(1.25f, -1.29f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(1.25f, -1.29f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(1.25f, -1.01f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(1.25f, -1.01f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(1.25f, -0.73f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(1.25f, -0.73f, 0.25f, 0.2f, 0.2f);

    drawBox3DAt(1.1f, 1.25f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(1.1f, 1.25f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.82f, 1.25f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.82f, 1.25f, 0.25f, 0.2f, 0.2f);
    drawBox3DAt(0.54f, 1.25f, 0.53f, 0.2f, 0.2f);
    drawBox3DAt(0.54f, 1.25f, 0.25f, 0.2f, 0.2f);

    for (int i = 0; i < 5; i++) {
        bool alive = enemyStatus[i];
        if (alive) {
            float x = enemyLocation[i][0];
            float y = enemyLocation[i][1];
            float z = enemyLocation[i][2];
            glPushMatrix();
            glTranslatef(x, y, z);
            drawCharactor3D();
            glPopMatrix();
        }
    }
    drawSpike3D(currentRemainingSeconds);

    gun.updateBullets();
    /* 3d end */

    /* 2d start */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);

    drawCrosshair2D();
    drawInterface2D(currentRemainingSeconds, leftEnimies, &camera);
    /* 2d end */

    glutSwapBuffers();
}

void updateTimeFunc(int value) {
    if (currentRemainingSeconds > 0) {
        currentRemainingSeconds--;
        glutPostRedisplay();
        glutTimerFunc(1000, updateTimeFunc, value);
        return;
    }
}

unordered_set<char> keys;
void updateKeys(int value) {
    float speed = currentRemainingSeconds > 0 ? 0.0075f : 0.02f;
    float cameraYaw = camera.getYaw();
    float cameraPitch = camera.getPitch();
    float dx = cos(cameraYaw) * speed;
    float dy = sin(cameraYaw) * speed;
    for (char key : keys) {
        if (key == 'w') {
            camera.add(dx, dy, 0);
        }
        else if (key == 's') {
            camera.subtract(dx, dy, 0);
        }
        else if (key == 'a') {
            camera.subtract(cos(cameraYaw - 1.6) * speed, sin(cameraYaw - 1.6) * speed, 0);
        }
        else if (key == 'd') {
            camera.add(cos(cameraYaw - 1.6) * speed, sin(cameraYaw - 1.6) * speed, 0);
        }
        else if (key == ' ') {
            camera.add(0, 0, speed);
        }
        else if (key == 112) { // shift key
            camera.subtract(0, 0, speed);
        }
    }
    glutPostRedisplay();
    glutTimerFunc(10, updateKeys, 0);
}

void handleKeypress(unsigned char key, int x, int y) {
    keys.insert(tolower(key));
}

void handleKeyRelease(unsigned char key, int x, int y) {
    keys.erase(tolower(key));
}

void handleSpecialKeypress(int key, int x, int y) {
    keys.insert(tolower(key));
}

void handleSpecialKeyRelease(int key, int x, int y) {
    keys.erase(tolower(key));
}

int windowCenterX, windowCenterY;

// GLUT 콜백 함수: 창 크기 조절을 처리합니다.
void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w / (float)h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    // 창 중심 좌표 업데이트
    windowCenterX = w / 2;
    windowCenterY = h / 2;

    glutWarpPointer(windowCenterX, windowCenterY);
}

bool isMouseInsideWindow = true;
void onMouseEntry(int state) {
    isMouseInsideWindow = (state == GLUT_ENTERED);
    if (!isMouseInsideWindow) {
        // 마우스가 창 밖으로 나갔을 때 커서를 보이게 함.
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
    else {
        glutSetCursor(GLUT_CURSOR_NONE);
    }
}

void mouseMotion(int x, int y) {
    if (isMouseInsideWindow) {
        int deltaX = windowCenterX - x;
        int deltaY = windowCenterY - y;

        const float sensitivity = 0.003f;

        camera.setYaw(camera.getYaw() + deltaX * sensitivity);
        camera.setPitch(camera.getPitch() + deltaY * sensitivity);

        // Pitch 각도를 제한하여 너무 위아래로 회전하지 않도록 함.
        camera.setPitch(fmax(fmin(camera.getPitch(), 3.141592f / 2.0 - 0.01), -3.141592f / 2.0 + 0.01));

        // 마우스 위치를 창 중심으로 이동.
        glutWarpPointer(windowCenterX, windowCenterY);

        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        gun.shoot();
        if (leftEnimies > 0) {
            enemyStatus[--leftEnimies] = false;
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // 깊이 버퍼 사용을 추가합니다.
    glutInitWindowSize(1366, 768);
    glutCreateWindow("OpenGL First-Person View");

    // 커서 초기화
    glutSetCursor(GLUT_CURSOR_NONE);

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyRelease);
    glutSpecialFunc(handleSpecialKeypress);
    glutSpecialUpFunc(handleSpecialKeyRelease);
    glutReshapeFunc(MyReshape);
    glutEntryFunc(onMouseEntry);
    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouse);

    glutTimerFunc(25, updateKeys, 0);

    const int remainingTime = 37;
    currentRemainingSeconds = remainingTime;
    leftEnimies = 5;
    glutTimerFunc(1000, updateTimeFunc, remainingTime);

    glutMainLoop();

    return 0;
}