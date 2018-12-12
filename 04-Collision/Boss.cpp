#include "Boss.h"

Boss::Boss(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Bosses\\VAMPIRE_BAT.png", 3, 1, 3);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag = 500;//enemy from 500
	CheckTop = true;
	//	direction = -1;
		//currentPos = y;
		//startXpos = X;
	//	startYpos = Y;
		/*vx = -0.1f;*/
		//vy = 10;
}

Boss::~Boss()
{
}

void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (!isDead)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}
}

void Boss::Update(DWORD dt, float simonx, float simony, vector<LPGAMEOBJECT>* coObjects)
{
	GoStartPosition(dt, simonx, simony);
	GoSimonPosition(dt, simonx, simony);

	int index = _sprite->GetIndex();
	if (index == 0)
		_sprite->SelectIndex(1);
	_sprite->Update(dt);




}



void Boss::Render(Camera * camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);

	_sprite->Draw(pos.x, pos.y);

}

void Boss::RePosition()
{
	this->x = startXpos;
	this->reviveTime = 200;
	this->hiteffect->isDoneRender = false;
	this->deadffect->isDoneRender = false;
}

void Boss::GoStartPosition(DWORD dt, float simonx, float simony)
{

	if (CheckRight)
	{
		vy = -0.05f;

		vx = -0.05f;
		CGameObject::Update(dt);
		x += dx;
		y += dy;
	}

	if (y < 110)
	{
		CheckTop = true;
		CheckRight = false;
	}
	if (CheckTop) // bat dau o checktop
	{
		if (x > 5100 || y < 240) //di qua ben trai
		{
			vx = -0.07f;
			vy = 0.05f;
			CGameObject::Update(dt);
			x += dx;
			y += dy;
		}
		else
		{
			CheckLeft = true;  //chuyen qua ham tan cong
			CheckTop = false;
		}


	}






}

void Boss::GoSimonPosition(DWORD dt, float simonx, float simony)
{

	if (CheckLeft)
	{

		if (y < 400 && x < 5350)
		{
			vy = 0.05f;
			vx = 0.05f;
			CGameObject::Update(dt);
			x += dx;
			y += dy;
		}
		else
		{
			CheckBot = true;
			CheckLeft = false;
		}

	}
	if (CheckBot)
	{
		if (x < 5600)
		{
			vy = -0.03f;
			vx = 0.07f;
			CGameObject::Update(dt);
			x += dx;
			y += dy;
		}
		else
		{

			CheckRight = true;
			CheckBot = false;


		}

	}






}


