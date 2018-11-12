#include "Simon.h"



Simon::Simon()
{
	_texture = new Texture("Resource\\sprites\\SIMON.png", 8, 3, 24);
	_sprite = new Sprite(_texture, 100);
	whip = new Whip(x, y);
	tag = 1;

	isWalking = 0;
	isJumping = 0;
	isSitting = 0;
	isAttacking = 0;

	//Health = 16; // simon dính 16 phát là chết

	//_ListWeapon.clear();
	//_ListWeapon.push_back(new MorningStar());
}


Simon::~Simon()
{
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isSitting == true) // simon đang ngồi
	{
		left = x + 12;
		top = y - 1; // không chỉnh lại y bởi vì hàm Sit() đã điều chỉnh
		right = x + SIMON_BBOX_WIDTH - 17;
		bottom = y + SIMON_BBOX_SITTING_HEIGHT - 3;
	}
	else
	{
		left = x + 12;
		top = y - 1;
		right = x + SIMON_BBOX_WIDTH - 17;
		bottom = y + SIMON_BBOX_HEIGHT - 3;
	}

}

void Simon::CollisionWithLargeCandle(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents); // Lấy danh sách các va chạm

												  // No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		/*	x += dx;
			y += dy;*/
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// nếu ko va chạm thì min_tx,min_ty = 1.0, còn nếu có thì nó trả về thời gian va chạm. 
		//Còn nx,ny là hướng va chạm,  = 0 nếu ko va chạm;

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		//y += min_ty * dy + ny * 0.4f; // ny = -1 thì hướng từ trên xuống....

		if (nx != 0)
		{
			vx = 0; // nếu mà nx, ny <>0  thì nó va chạm rồi. mà chạm rồi thì dừng vận tốc cho nó đừng chạy nữa
		}


		if (ny != 0)
		{
			vy = 0;

		}


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<LargeCandle *>(e->obj))
			{
				LargeCandle *largecandle = dynamic_cast<LargeCandle *>(e->obj);
				// jump on top >> kill Goomba and deflect a bit 
				if (e->nx != 0)
				{
					largecandle->isDead = true;
				}
			}
		}
		//}


		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
}
void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/* Không cho lọt khỏi camera */
	if (x < -10)
		x = -10;
	//if (x + SIMON_BBOX_WIDTH > MapWidth)
	//	x = MapWidth - SIMON_BBOX_WIDTH;


	/* Update về sprite */

	int index = _sprite->GetIndex();

	if (isSitting == true)
	{
		_sprite->SelectIndex(SIMON_ANI_SITTING);
	}
	else
		if (isWalking == true) // đang di chuyển
		{
			if (isJumping == false) // ko nhảy
			{
				if (index < SIMON_ANI_BEGIN_WALKING || index >= SIMON_ANI_END_WALKING)
					_sprite->SelectIndex(1);
				if (isAttacking == true)
				{
					_sprite->SelectIndex(5);
				}

				//cập nhật frame mới
				_sprite->Update(dt); // dt này được cập nhật khi gọi update; 
			}
			else
			{
				if (isAttacking == true)
				{
					_sprite->SelectIndex(5);
				}
				else
				{
					_sprite->SelectIndex(SIMON_ANI_JUMPING);
				}
				
			}

		}
		else
			if (isJumping == true) // nếu ko đi mà chỉ nhảy
			{
				_sprite->SelectIndex(SIMON_ANI_JUMPING);
			}
			else if (isAttacking == true)
			{
				_sprite->SelectIndex(5);

			}
			else
			{
				_sprite->SelectIndex(SiMON_ANI_IDLE);		// SIMON đứng yên

			}

	/* Update về sprite */

	 // k phai dau, qua ham render la len hinh r

	if (isAttacking == true)
	{
		if (whip->isFinish == false)
		{
			whip->SetPosition(this->x, this->y);
			whip->Update(dt, coObjects);

		}
		if (whip->isFinish == true)
		{
			isAttacking = false;
		}
		//whip->isFinish = true;
	}

	CGameObject::Update(dt);
	vy += SIMON_GRAVITY * dt;// Simple fall down


	vector<LPGAMEOBJECT> coObjects_Brick;
	coObjects_Brick.clear();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == 21)
			coObjects_Brick.push_back(coObjects->at(i));
	CollisionWithBrick(&coObjects_Brick); // check Collision and update x, y for simon

	/*vector<LPGAMEOBJECT> coObjects_LargeCandle;
	coObjects_LargeCandle.clear();
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetType() == 41)
			coObjects_LargeCandle.push_back(coObjects->at(i));
	CollisionWithLargeCandle(&coObjects_LargeCandle);*/

}

void Simon::Render(Camera *camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);

	if (trend == -1)
		_sprite->Draw(pos.x, pos.y);
	else
		_sprite->DrawFlipX(pos.x, pos.y);


	if (whip->isFinish == false)
	{
		whip->Render(camera);
	}
	RenderBoundingBox(camera);
}


void Simon::Left()
{
	trend = -1;
}

void Simon::Right()
{
	trend = 1; // quay qua phải
}

void Simon::Go()
{
	vx = SIMON_WALKING_SPEED * trend;
	isWalking = 1;

}

void Simon::Sit()
{
	vx = 0;
	isWalking = 0;

	if (isSitting == false) // nếu trước đó simon chưa ngồi
		y = y + 16; // kéo simon xuống

	isSitting = 1;
}

void Simon::Jump()
{
	if (isSitting == true)
		return;
	vy -= SIMON_VJUMP;
	isJumping = true;
}

void Simon::Stop()
{
	if (vx != 0)
		vx -= dt * SIMON_GRAVITY*0.1*trend;
	if (trend == 1 && vx < 0)
		vx = 0;
	if (trend == -1 && vx > 0)
		vx = 0;
	// tóm lại là vx = 0 :v


	isWalking = 0;
	if (isSitting == true) // nếu simon đang ngồi
	{
		isSitting = 0; // hủy trạng thái ngồi
		y = y - 18; // kéo simon lên
	}

}
void Simon::RenderBoundingBox(Camera *camera)
{
	CGameObject::RenderBoundingBox(camera);
}
void Simon::CollisionWithBrick(vector<LPGAMEOBJECT>* coObjects)
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

		if (nx != 0)
			vx = 0; // nếu mà nx, ny <>0  thì nó va chạm rồi. mà chạm rồi thì dừng vận tốc cho nó đừng chạy nữa

		if (ny != 0)
		{
			vy = 0;
			isJumping = false; // kết thúc nhảy
		}

		//// Collision logic with Goombas
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];
		//	if (dynamic_cast<Goomba *>(e->obj))
		//	{
		//		Goomba *goomba = dynamic_cast<Goomba *>(e->obj);
		//		// jump on top >> kill Goomba and deflect a bit 
		//		if (e->ny < 0)
		//		{
		//			if (goomba->GetState() != GOOMBA_STATE_DIE)
		//			{
		//				goomba->SetState(GOOMBA_STATE_DIE);
		//				vy = -MARIO_JUMP_DEFLECT_SPEED;
		//			}
		//		}
		//		else if (e->nx != 0)
		//		{
		//			if (untouchable == 0)
		//			{
		//				if (goomba->GetState() != GOOMBA_STATE_DIE)
		//				{
		//					if (level > MARIO_LEVEL_SMALL)
		//					{
		//						level = MARIO_LEVEL_SMALL;
		//						StartUntouchable();
		//					}
		//					else
		//						SetState(MARIO_STATE_DIE);
		//				}
		//			}
		//		}
		//	}
		//}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Simon::Attack()
{
	if (isAttacking == true) // đang tấn công thì thôi
		return;

	isAttacking = true;
	whip->Create(this->x, this->y, this->trend); // set vị trí weapon theo simon
}
