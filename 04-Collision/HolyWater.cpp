#include "HolyWater.h"

HolyWater::~HolyWater()
{
}
HolyWater::HolyWater(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Sub_weapons\\HOLY_WATER_ACTION.png", 3, 1, 3);
	_sprite = new Sprite(_texture, 300);
	x = X;
	y = Y;
	tag = 3;
	//currentPos = y;
	//isDead = false;
}
void HolyWater::Update(DWORD dt, float left, float right, vector<LPGAMEOBJECT>* coObjects)
{

	if (!isFinish)
	{
		if (!CheckTop)
		{
			vy =- 0.1f;
			vx = direction * 0.15f;
		}
		if (y < currentPos - 20)
		{
			CheckTop = true;
		}
		if (CheckTop)
		{
			vx = 0.09f*direction;
			vy = 0.3f;
		}
		
		CGameObject::Update(dt);
		//x += dx;
		//y += dy;
		vector<LPGAMEOBJECT> coObjects_Brick;
		coObjects_Brick.clear();
		vector<LPGAMEOBJECT> coObjects_Enemy;
		coObjects_Enemy.clear();
		
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->GetTag() == BRICK_TAG)
				coObjects_Brick.push_back(coObjects->at(i));
			if(coObjects->at(i)->GetTag() == ENEMY_TAG)
				coObjects_Enemy.push_back(coObjects->at(i));
			
			
		}	
		CollisionWithBrick(&coObjects_Brick); // check Collision and update x, y for simon
		CollisionWithEnemy(&coObjects_Enemy);
		
		/*for (int i = 0; i < coObjects->size(); i++)
			i*/
	}


}
void HolyWater::CollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents); 

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		
		y += min_ty * dy + ny * 0.4f; 

		if (nx != 0)
		{
			vx = 0;
			vy = 0;
			_sprite->Update(dt);
			if (_sprite->GetIndex() >= 2)
			{
				this->isFinish = true;
			}
		}
		

		if (ny != 0)
		{
			vx = 0;
			vy = 0;
			_sprite->Update(dt);
			if (_sprite->GetIndex() >= 2)
			{
				this->isFinish = true;
			}
			
		}

		
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}
void HolyWater::Create(float simonX, float simonY, int simondirection)
{
	this->x = simonX;
	this->y = simonY+20;
	this->currentPos = simonY;
	this->direction = simondirection;
	this->remainingTime = 100;//set thoi gian ton tai vu khi
	this->isFinish = false;
	this->CheckTop = false;
	Sound::GetInstance()->Play(HOLY_WATER);

}
