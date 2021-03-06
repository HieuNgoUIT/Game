#include "Pander.h"

Pander::Pander(int TYPE, int X, int Y)
{
//	_texture = new Texture("Resource\\sprites\\Enemies\\PANTHER.png", 4, 1, 4);
//	_sprite = new Sprite(_texture, 100);
	this->x = X;
	this->y = Y;
	tag = ENEMY_TAG;//enemy from 500
	direction = -1;
	startXpos = X;
	startYpos = Y;
	doJump = true;
	health = 10;
	texId = TYPE;
}

Pander::~Pander()
{
}

void Pander::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (health>0)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}
}

void Pander::Update(DWORD dt, float simonx , vector<LPGAMEOBJECT>* coObjects)
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
		if (simonx > startXpos - ACTIONBEFOREX)
		{
			allowToDo = true;
		}
		if (allowToDo)
		{
			if (doJump)
			{
				if (!CheckTop)
				{
					vy = JUMPVY;
					vx = JUMPVX *direction;
				}
				if (y < startYpos - MAXHEIGHT)
				{
					CheckTop = true;
				}
				if (CheckTop)
				{
					vy = GRAVITY*dt;
				}
				if (isGrounded)
				{
					doJump = false;
					direction = -direction;
				}
				CGameObject::Update(dt);
				_sprite->SelectIndex(3);
				
				
			}
			else
			{
				vx = RUNVX *direction;
				CGameObject::Update(dt);
				_sprite->Update(dt);
			}
		
			vector<LPGAMEOBJECT> coObjects_Brick;
			coObjects_Brick.clear();
			for (int i = 0; i < coObjects->size(); i++)
			{
				if (coObjects->at(i)->GetTag() == BRICK_TAG)
					coObjects_Brick.push_back(coObjects->at(i));
			}
			CollisionWithBrick(&coObjects_Brick);
		}
		
	}

}

void Pander::Render(Camera * camera)
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

void Pander::CollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
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

		//if (nx != 0)
		//	vx = 0;

		if (ny != 0)
		{
			isGrounded = true;
		}

	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Pander::RePosition()
{
	this->x = startXpos;
	this->y = startYpos;
	this->reviveTime = 500;
	this->hiteffect->isDoneRender = false;
	this->deadffect->isDoneRender = false;
	health = 10;
	allowToDo = 0;
}
