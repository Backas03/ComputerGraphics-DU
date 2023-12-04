#include "camera.h"
Camera::Camera() {
	this->x = -1.75;
	this->y = -1.75;
	this->z = 0.2f;
	this->yaw = 0;
	this->pitch = 0;
}

float Camera::getX() {
	return this->x;
}

float Camera::getY() {
	return this->y;
}

float Camera::getZ() {
	return this->z;
}

float Camera::getYaw() {
	return this->yaw;
}

float Camera::getPitch() {
	return this->pitch;
}

void Camera::add(float x, float y, float z) {
	this->x += x;
	this->y += y;
	this->z += z;
}

void Camera::subtract(float x, float y, float z) {
	this->x -= x;
	this->y -= y;
	this->z -= z;
}

void Camera::set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Camera::setX(float x) {
	this->x = x;
}

void Camera::setY(float y) {
	this->y = y;
}

void Camera::setZ(float z) {
	this->z = z;
}

void Camera::setYawAndPitch(float yaw, float pitch) {
	this->yaw = yaw;
	this->pitch = pitch;
}

void Camera::setYaw(float yaw) {
	this->yaw = yaw;
}

void Camera::setPitch(float pitch) {
	this->pitch = pitch;
}