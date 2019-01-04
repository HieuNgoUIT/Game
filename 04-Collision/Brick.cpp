#include "Brick.h"


Brick::Brick(int TYPE,int X, int Y, int W, int H)
{
	tag = BRICK_TAG;
	texId = TYPE;
	this->x = X;
	this->y = Y;
	this->width = W;
	this->height = H;
	
}

void Brick::Render(Camera *camera)
{
	if (texId == BRICK_TYPE1)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		for (int i = 0; i < (int)ceil(width / BRICK_FRAME_WIDTH); i++)
			for (int j = 0; j < (int)ceil(height / BRICK_FRAME_HEIGHT); j++)
				_sprite->Draw(pos.x + i * BRICK_FRAME_WIDTH, pos.y + j * BRICK_FRAME_HEIGHT);
		
	}
	CGameObject::RenderBoundingBox(camera);
}



void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + (float)ceil(width / BRICK_FRAME_WIDTH)*BRICK_FRAME_WIDTH;
	b = y + (float)ceil(height / BRICK_FRAME_HEIGHT)*BRICK_FRAME_HEIGHT;
}