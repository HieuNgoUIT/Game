#include "Brick.h"


Brick::Brick(int TYPE,int X, int Y, int W, int H)
{
	tag = 41;
	if (TYPE == 12)
	{
		_texture = new Texture("Resource\\sprites\\Ground\\2.png", 1, 1, 1);
	}
	else
	{
		_texture = new Texture("Resource\\sprites\\Ground\\brick.png", 1, 1, 1);
	}
	_sprite = new Sprite(_texture, 1000);
	this->x = X;
	this->y = Y;
	this->width = W;
	this->height = H;
	isDead = 0;
}

void Brick::Render(Camera *camera)
{
	D3DXVECTOR2 pos=camera->Transform(x, y);
	for (int i = 0; i < (int)ceil(width / BRICK_FRAME_WIDTH); i++)
		for (int j = 0; j < (int)ceil(height / BRICK_FRAME_HEIGHT); j++)
			_sprite->Draw(pos.x + i * BRICK_FRAME_WIDTH, pos.y + j * BRICK_FRAME_HEIGHT);
	CGameObject::RenderBoundingBox(camera);
}



void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + (float)ceil(width / BRICK_FRAME_WIDTH)*BRICK_FRAME_WIDTH;
	b = y + (float)ceil(height / BRICK_FRAME_HEIGHT)*BRICK_FRAME_HEIGHT;
}