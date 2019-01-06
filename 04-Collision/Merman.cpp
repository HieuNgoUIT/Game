#include "Merman.h"

Merman::Merman(int TYPE, int X, int Y)
{
//	_texture = new Texture("Resource\\sprites\\Enemies\\MERMAN.png", 3, 1, 3);
//	_sprite = new Sprite(_texture, 200);
	this->x = X;
	this->y = Y;
	tag = ENEMY_TAG;//enemy from 500
	direction = 1;
	startXpos = X;
	startYpos = Y;
	watereffect = new WaterEffect();
	watereffect1 = new WaterEffect();
	watereffect2 = new WaterEffect();
	//fireball = new FireBall(x, y);
	health = 10;
	fireball = new FireBall(x, y);
	texId = TYPE;
}

Merman::~Merman()
{
}

void Merman::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (health > 0)
	{
		left = x;
		top = y;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight;
	}
}

void Merman::Update(DWORD dt, float simonx, vector<LPGAMEOBJECT>* coObjects)
{
	if (health <= 0)
	{
		CGameObject::UpdateEffect(dt);
		reviveTime--;
		if (reviveTime < 0)
		{
			isReachPoint = false;
			RePosition();
			this->isDead = false;
		}
	}
	else
	{
		if (simonx > startXpos - ACTIONX && simonx < startXpos + ACTIONX)
		{
			allowToDo = true;
		}
		if (allowToDo)
		{
			CGameObject::Update(dt);
			vx = 0.02f*direction;
			if (y > STARTPLACE)
			{
				Sound::GetInstance()->Play(SLASH_WATER);
				watereffect->SetPosition(this->x + 5, this->y - 50);
				watereffect1->SetPosition(this->x + 10, this->y - 60);
				watereffect2->SetPosition(this->x + 20, this->y - 70);
			}
			if (y < ENDPLACE)
			{
				isReachPoint = true;
				vy = GRAVITY *dt;
			}
			if (!isReachPoint)
			{
				vy = JUMPV * dt;
				y += dy;
			}
			attackTime--;
			if (attackTime < 0 && !isAttack)
			{
				isAttack = true;
				bulletTime = 200;
				fireball->health = 10;
				fireball->SetPosition(this->x, this->y+10);
			}
			if (isAttack)
			{
				this->vx = 0;
				_sprite->SelectIndex(0);
				fireball->Update(dt, simonx);
				bulletTime--;
				if (bulletTime < 0)
				{
					isAttack = false;
					attackTime = 300;
				}
			}
			else
			{
				_sprite->Update(dt);
			}
			
		
			watereffect->Update(dt, this->direction);
			watereffect1->Update(dt, -this->direction);
			watereffect2->Update(dt, this->direction);
			vector<LPGAMEOBJECT> coObjects_Brick;
			coObjects_Brick.clear();
			for (int i = 0; i < coObjects->size(); i++)
			{
				if (coObjects->at(i)->GetTag() == BRICK_TAG)
					coObjects_Brick.push_back(coObjects->at(i));
			}
			if (isReachPoint)
			{
				CollisionWithBrick(&coObjects_Brick);
			}
		}


	}

}

void Merman::Render(Camera * camera)
{
	if (health > 0)
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
		if (attackTime < 0)
		{
			fireball->Render(camera);
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
	this->y = startYpos;
	this->reviveTime = 200;
	this->hiteffect->isDoneRender = false;
	this->deadffect->isDoneRender = false;
	health = 10;
}
