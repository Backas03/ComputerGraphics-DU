#pragma once

class Camera {
public:
	Camera();
	float getX();
	float getY();
	float getZ();
	float getYaw();
	float getPitch();
	void add(float x, float y, float z);
	void subtract(float x, float y, float z);
	void set(float x, float y, float z);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setYawAndPitch(float yaw, float pitch);
	void setYaw(float yaw);
	void setPitch(float pitch);
private:
	float x, y, z, yaw, pitch;
};