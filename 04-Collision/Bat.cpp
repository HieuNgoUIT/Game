#include "Bat.h"

Bat::Bat(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Enemies\\BAT.png", 4, 1, 4);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag = 500;//enemy from 500
	direction = -1;
	currentPos = y;
	startXpos = X;
	startYpos = Y;
	/*vx = -0.1f;*/
	//vy = 10;
	health = 10;
}

Bat::~Bat()
{
}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (health>0)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}
}

void Bat::Update(DWORD dt, float simonx , vector<LPGAMEOBJECT>* coObjects)
{
	if (health<=0)
	{
		CGameObject::UpdateEffect(dt);
		reviveTime--;
		if (reviveTime < 0)
		{
			RePosition();
			this->isDead = false;
		}

	}
	else
	{

		CGameObject::Update(dt);
		if (simonx > startXpos - 400 && simonx < startXpos + 320)
		{
			allowToDo = true;
		}
		if (allowToDo)
		{
			if (y >currentPos + 35)
			{
				CheckBot = true;
				CheckTop = false;
			}
			if (y <currentPos - 35)
			{
				CheckTop = true;
				CheckBot = false;
			}
			if (CheckBot)
			{
				vy = -0.005f*dt;

			}
			if (CheckTop)
			{
				vy = 0.005f*dt;

			}
			if (!CheckBot && !CheckTop)
			{
				vy = -0.005f*dt;
			}

			vx = 0.1f*direction;
			x += dx;
			y += dy;
			_sprite->Update(dt);
		}
		
		
	}
	

	




}



void Bat::Render(Camera * camera)
{
	if (health>0)
	{

		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (direction == -1)
			_sprite->Draw(pos.x, pos.y);
		else
			_sprite->DrawFlipX(pos.x, pos.y);
		RenderBoundingBox(camera);
	}
	else
	{
		CGameObject::RenderEffect(camera);
	}
}

void Bat::RePosition()
{
	this->x = startXpos;
	this->reviveTime = 200;
	this->hiteffect->isDoneRender = false;
	this->deadffect->isDoneRender = false;
	health = 10;
}


