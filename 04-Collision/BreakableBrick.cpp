#include "BreakableBrick.h"


BreakableBrick::BreakableBrick(int TYPE, int X, int Y, int W, int H)
{
	texId = TYPE;
	tag = BREAKABLEBRICK_TAG;
	if (TYPE == BREAKABLEBRICK_TYPE1)
	{
//		_texture = new Texture("Resource\\sprites\\Ground\\Brick.png", 1, 1, 1);
	}
	else
	{
//		_texture = new Texture("Resource\\sprites\\Ground\\8.png", 1, 1, 1);
	}
	
//	_sprite = new Sprite(_texture, 1000);
	this->x = X;
	this->y = Y;
	this->width = W;
	this->height = H;
	health = 10;
	be1 = new BrickEffect();
	be2 = new BrickEffect();
	be3 = new BrickEffect();
	be4 = new BrickEffect();
	be1->SetPosition(this->x + 20, this->y - 50);
	be2->SetPosition(this->x + 40, this->y - 60);
	be3->SetPosition(this->x - 20, this->y - 70);
	be4->SetPosition(this->x - 35, this->y - 70);
}

void BreakableBrick::Render(Camera *camera)
{
	if (health > 0)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		for (int i = 0; i < (int)ceil(width / BRICK_FRAME_WIDTH); i++)
			for (int j = 0; j < (int)ceil(height / BRICK_FRAME_HEIGHT); j++)
				_sprite->Draw(pos.x + i * BRICK_FRAME_WIDTH, pos.y + j * BRICK_FRAME_HEIGHT);
		CGameObject::RenderBoundingBox(camera);
	}
	else
	{
		be1->Render(camera);
		be2->Render(camera);
		be3->Render(camera);
		be4->Render(camera);
	}

}



void BreakableBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (health > 0)
	{
		l = x;
		t = y;
		r = x + (float)ceil(width / BRICK_FRAME_WIDTH)*BRICK_FRAME_WIDTH;
		b = y + (float)ceil(height / BRICK_FRAME_HEIGHT)*BRICK_FRAME_HEIGHT;
	}
	
}

void BreakableBrick::Update(DWORD dt, float simonx, vector<LPGAMEOBJECT>* coObjects)
{
	if (health <= 0)
	{
		be1->Update(dt, 1);
		be2->Update(dt, -1);
		be3->Update(dt, 1);
		be4->Update(dt, -1);
	}
}
