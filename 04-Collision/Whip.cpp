#include "Whip.h"

Whip::Whip(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Weapons\\VAMPIRE_KILLER.png", 3, 1, 3);
	_sprite = new Sprite(_texture, 100);
	x = X;
	y = Y;
	tag = 2;
	health = 1;
	isFinish = 1;
}

Whip::Whip()
{
}

Whip::~Whip()
{
}

void Whip::RenderBoundingBox(Camera * camera)
{
	CGameObject::RenderBoundingBox(camera);
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	_sprite->Update(dt);
	//CGameObject::Update(dt);
	/*vector<LPGAMEOBJECT> coObjects_LargeCandle;
	coObjects_LargeCandle.clear();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == 41)
			coObjects_LargeCandle.push_back(coObjects->at(i));
	CollisionWithLargeCandle(&coObjects_LargeCandle);*/
}
void Whip::CollisionWithLargeCandle(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents); // Lấy danh sách các va chạm

												  // No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// nếu ko va chạm thì min_tx,min_ty = 1.0, còn nếu có thì nó trả về thời gian va chạm. 
		//Còn nx,ny là hướng va chạm,  = 0 nếu ko va chạm;

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f; // ny = -1 thì hướng từ trên xuống....

		//if (nx != 0)
		//	vx = 0; // nếu mà nx, ny <>0  thì nó va chạm rồi. mà chạm rồi thì dừng vận tốc cho nó đừng chạy nữa

		//if (ny != 0)
		//{
		//	vy = 0;
		//	
		}

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<LargeCandle *>(e->obj))
			{
				LargeCandle *largecandle = dynamic_cast<LargeCandle *>(e->obj);
				// jump on top >> kill Goomba and deflect a bit 
				 if (e->nx != 0)
				{
					 largecandle->Delete();
				}
			}
		}
	

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}
void Whip::Create(float simonX, float simonY, int simonTrend)
{
	this->x = simonX;
	this->y = simonY;
	this->trend = simonTrend;
	isFinish = 0;
}
void Whip::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (trend == -1)
		_sprite->Draw(pos.x, pos.y);
	else
		_sprite->DrawFlipX(pos.x, pos.y);
	RenderBoundingBox(camera);
}
