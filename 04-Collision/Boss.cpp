#include "Boss.h"

Boss::Boss()
{
}

Boss::Boss(int X, int Y)
{
//	_texture = new Texture("Resource\\sprites\\Bosses\\VAMPIRE_BAT.png", 3, 1, 3);
//	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag = ENEMY_TAG;//enemy from 500
	CheckTop = true;
	health = 10;
	item = new Item("Resource\\sprites\\Items\\13.png", x, 240);
	deadffect->remainingTime = 500;//boss thi cho render lau 1 ti
	
}

Boss::~Boss()
{
}

void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (health >= 0)
	{
		if (!untouchable)
		{
			left = x;
			top = y;
			right = x + _texture->FrameWidth;
			bottom = y + _texture->FrameHeight;
		}
	}
	
}

void Boss::Update(DWORD dt, float simonx, float simony, vector<LPGAMEOBJECT>* coObjects)
{
	if (health >= 0)
	{

		if (GetTickCount() - untouchable_start > 500)
		{
			untouchable_start = 0;
			untouchable = 0;
		}
		if (x < 5060)
			x = 5060;
		GoStartPosition(dt, simonx, simony);
		GoSimonPosition(dt, simonx, simony);

		int index = _sprite->GetIndex();
		if (index == 0)
			_sprite->SelectIndex(1);
		_sprite->Update(dt);

	}
	else
	{
		isDead = true;
		item->Update(dt,NULL, coObjects);
		deadffect->Update(dt);
		if (Sound::GetInstance()->IsPLaying(BOSS_BATTLE_POISON_MIND))
		{
			Sound::GetInstance()->Stop(BOSS_BATTLE_POISON_MIND);
		}
		Sound::GetInstance()->Play(STAGE_CLEAR);
	}




}



void Boss::Render(Camera * camera)
{
	if (!isDead)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		_sprite->Draw(pos.x, pos.y);
		RenderBoundingBox(camera);
	}
	else
	{
		if (deadffect->isDoneRender == false)
		{
			deadffect->isVisible = true;
			deadffect->SetPosition(this->x , this->y);
			deadffect->Render(camera);
		}
		item->Render(camera);

	}


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
		waittingtimebeforeattack = 125;
		CheckTop = true;
		CheckRight = false;
	}







}

void Boss::GoSimonPosition(DWORD dt, float simonx, float simony)
{

	if (CheckLeft)
	{

		if (y < 400)
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
			vx = 0.1f;
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

void Boss::ResetPosition()
{
	health = 80;
	SetPosition(5300, 100);
	_sprite->SelectIndex(0);
	CheckTop = true;
	CheckBot = false;
	CheckLeft = false;
	CheckRight = false;
}


