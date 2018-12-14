#include "Boss.h"

Boss::Boss(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Bosses\\VAMPIRE_BAT.png", 3, 1, 3);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag = 500;//enemy from 500
	CheckTop = true;
	health = 80;
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
	if (x < 5060)
		x = 5060;
	GoStartPosition(dt, simonx, simony);
	GoSimonPosition(dt, simonx, simony);

	int index = _sprite->GetIndex();
	if (index == 0)
		_sprite->SelectIndex(1);
	_sprite->Update(dt);




}



void Boss::Render(Camera * camera)
{
	if (!isDead)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		_sprite->Draw(pos.x, pos.y);
		RenderBoundingBox(camera);
	}
	

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
	if (CheckTop) // bat dau o checktop
	{
		if (/*x > 5100 ||*/ y < 240) //di qua ben trai
		{
			vx = -0.1f;
			vy = 0.1f;
			CGameObject::Update(dt);
			x += dx;
			y += dy;
		}
		else if (waittingtimebeforeattack > 0)
		{
			waittingtimebeforeattack--;
		}
		else
		{
			CheckLeft = true;  //chuyen qua ham tan cong
			positionyToHit = simony;
			positionxToHit = simonx;
			CheckTop = false;
		}


	}
	if (CheckRight)
	{
		vy = -0.2f;
		vx = -0.2f;
		CGameObject::Update(dt);
		x += dx;
		y += dy;
	}

	if (y < 110)
	{
		waittingtimebeforeattack = 300;
		CheckTop = true;
		CheckRight = false;
	}
	






}

void Boss::GoSimonPosition(DWORD dt, float simonx, float simony)
{

	if (CheckLeft)
	{

		if (y < 400 )
		{
			vy = 0.3f;
			vx = 0.3f;
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
		if (x < positionxToHit && y>positionyToHit)
		{
			vy = -0.1f;
			vx = 0.2f;
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


