#include "Merman.h"

Merman::Merman(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Enemies\\MERMAN.png", 3, 1, 3);
	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag = 500;//enemy from 500
	direction = 1;
	startXpos = X;
	startYpos = Y;
	watereffect = new WaterEffect();
	watereffect1 = new WaterEffect();
	watereffect2 = new WaterEffect();

}

Merman::~Merman()
{
}

void Merman::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (!isDead)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}
}

void Merman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDead)
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
		vx = 0.02f*direction;
		if (y > 700)
		{
			Sound::GetInstance()->Play(SLASH_WATER);
			watereffect->SetPosition(this->x + 5, this->y -50);
			watereffect1->SetPosition(this->x + 10, this->y - 60);
			watereffect2->SetPosition(this->x + 20, this->y - 70);
		}
		if (y < 500)
		{

			isReachPoint = true;
			vy = 0.05f*dt;


		}
		if (!isReachPoint)
		{
			vy -= 0.0005f * dt;
			y += dy;
		}

		_sprite->Update(dt);
		watereffect->Update(dt, this->direction);
		watereffect1->Update(dt, -this->direction);
		watereffect2->Update(dt, this->direction);
		vector<LPGAMEOBJECT> coObjects_Brick;
		coObjects_Brick.clear();
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->GetTag() == 41)
				coObjects_Brick.push_back(coObjects->at(i));
		}
		if (isReachPoint)
		{
			CollisionWithBrick(&coObjects_Brick);
		}

	}

}

void Merman::Render(Camera * camera)
{
	if (!isDead)
	{

		D3DXVECTOR2 pos = camera->Transform(x, y);
		if (direction == -1)
			_sprite->Draw(pos.x, pos.y);
		else
			_sprite->DrawFlipX(pos.x, pos.y);
		if (isReachPoint)
		{
			watereffect->Render(camera);
			watereffect1->Render(camera);
			watereffect2->Render(camera);
		}
	


		RenderBoundingBox(camera);
	}
	else
	{
		CGameObject::RenderEffect(camera);
	}
}

void Merman::CollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
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

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0)
			vx = 0;

		if (ny != 0)
		{
			vy = 0;
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Merman::RePosition()
{
	this->x = startXpos;
	this->reviveTime = 200;
	this->hiteffect->isDoneRender = false;
	this->deadffect->isDoneRender = false;
}
