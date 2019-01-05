#pragma once

#define BRICK_WIDTH 32
#define BRICK_HEIGHT 32

#include "GameObject.h"
#include "Camera.h"
class Brick : public CGameObject
{
	int type;
	int width;
	int height;
public:
	Brick(int TYPE, int X, int Y, int W, int H);
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);

};

