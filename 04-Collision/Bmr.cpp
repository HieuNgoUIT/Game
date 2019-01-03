#include "Bmr.h"

Bmr::~Bmr()
{
}
Bmr::Bmr(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Sub_weapons\\CROSS_ACTION.png", 3, 1, 3);
	_sprite = new Sprite(_texture, 100);
	x = X;
	y = Y;
	currentPos = y;
	//isDead = false;
}
void Bmr::Update(DWORD dt, float left, float right, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vx = direction * 0.5f;
	if (x > right)
	{
		x = right - 1;
		direction = -direction;
		isTouchBoundaryR = true;
	}
	else if (x < left)
	{
		x = left + 1;
		direction = -direction;
		isTouchBoundaryL = true;
	}
	x += dx;
	if (isTouchBoundaryR)
	{
		if (x < currentPos)
		{
			this->isFinish = true;
		}
	}
	if (isTouchBoundaryL)
	{
		if (x > currentPos)
		{
			this->isFinish = true;
		}
	}



	vector<LPGAMEOBJECT> coObjects_LargeCandle;
	coObjects_LargeCandle.clear();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetTag() == ENEMY_TAG)
			coObjects_LargeCandle.push_back(coObjects->at(i));
	CollisionWithEnemy(&coObjects_LargeCandle);

}
void Bmr::Create(float simonX, float simonY, int simondirection)
{

	this->x = simonX;
	isTouchBoundaryR = false;
	isTouchBoundaryL = false;

	this->y = simonY;
	this->currentPos = simonX;
	this->direction = simondirection;
	//	this->remainingTime = 200;//set thoi gian ton tai vu khi
	this->isFinish = false;


}
