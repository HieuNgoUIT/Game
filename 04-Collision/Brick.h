#ifndef __BRICK_H__
#define __BRICK_H__

#define BRICK_FRAME_WIDTH 32
#define BRICK_FRAME_HEIGHT 32

#include "GameObject.h"
#include "Camera.h"
class Brick : public CGameObject
{
protected:
	int width;
	int height;
	int type;
public:
	Brick(int TYPE,int X, int Y, int W, int H);
	void Render(Camera *camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	
};


#endif