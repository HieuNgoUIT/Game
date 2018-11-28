﻿#include "Simon.h"



Simon::Simon()
{
	_texture = new Texture("Resource\\sprites\\simon.png", 8, 3, 24);
	_sprite = new Sprite(_texture, 100);
	whip = new Whip(x, y);
	subwp = new SubWeapon(x, y);
	tag = 1;

	isWalking = 0;
	isJumping = 0;
	isSitting = 0;
	isAttacking = 0;
	direction = 1;
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
		right = x + _texture->FrameHeight;
		bottom = y + _texture->FrameHeight - 21;
	}
	else
	{
		left = x + 12;
		top = y - 1;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight - 3;
	}

}

void Simon::CollisionWithItem(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents); // Lấy danh sách các va chạm


	//DebugOut(L"[INFO] KeyUp: %d\n", coObjects->size());
	for (int i = 0; i < coObjects->size(); i++) //aabb item
	{
		if (isColliding(this, coObjects->at(i)))
		{
			coObjects->at(i)->isDead = true;
			whip->typeOfWhip = 1;
			//this->useableHeart+=1;
		}
	}

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




		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Item *>(e->obj))
			{
				Item *item = dynamic_cast<Item *>(e->obj);
				// jump on top >> kill Goomba and deflect a bit 
				if (e->t > 0 && e->t <= 1)
				{
					item->isDead = true;
				}
			}
		}
		//}


		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems)
{
	CGame *game = CGame::GetInstance();
	/* Không cho lọt khỏi camera */
	if (x < -10)
		x = -10;
	/*if (x >3000)
		x = 3000;*/
	if (isStage21 && x < 3050)
	{
		x = 3050;
	}



	/* Update về sprite */
#pragma region Sprite update
	int index = _sprite->GetIndex();

	if (isOnStair) {
		_sprite->SelectIndex(10);
		if (game->IsKeyDown(DIK_UP) || game->IsKeyDown(DIK_DOWN))
		{
			_sprite->Update(dt);
		}


	}
	else if (isSitting == true) //dang ngoi
	{
		_sprite->SelectIndex(SIMON_ANI_SITTING);
		if (isAttacking == true)
		{
			/*if (index < SIMON_ANI_BEGIN_SITHITTING || index >= SIMON_ANI_END_SITHITTING)
			{*/
			_sprite->SelectIndex(SIMON_ANI_BEGIN_SITHITTING);
			_sprite->Update(dt);
			/*}*/

		}
	}
	else
		if (isWalking == true) // đang di chuyển
		{
			if (isJumping == false) // ko nhảy
			{
				if (index < SIMON_ANI_BEGIN_WALKING || index >= SIMON_ANI_END_WALKING)
					_sprite->SelectIndex(SIMON_ANI_BEGIN_WALKING);
				if (isAttacking == true)
				{
					/*if (index < SIMON_ANI_BEGIN_HITTING || index > SIMON_ANI_END_HITTING)*/
					_sprite->SelectIndex(SIMON_ANI_BEGIN_HITTING);
				}

				//cập nhật frame mới
				_sprite->Update(dt); // dt này được cập nhật khi gọi update; 
			}
			else
			{
				if (isAttacking == true)
				{
					/*if (index < 5 || index >= 7)*/
					_sprite->SelectIndex(SIMON_ANI_BEGIN_HITTING);
					_sprite->Update(dt);
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
				if (isAttacking == true)
				{
					/*if (index < 5 || index >= 7)*/
					_sprite->SelectIndex(5);
					_sprite->Update(dt);
				}
				else
				{
					_sprite->SelectIndex(SIMON_ANI_JUMPING);
				}

			}
			else if (isAttacking == true)
			{
				/*if (index < 5 || index >= 7)*/
				_sprite->SelectIndex(5);
				_sprite->Update(dt);
			}
			else
			{
				_sprite->SelectIndex(SiMON_ANI_IDLE);		// SIMON đứng yên

			}

	/* Update về sprite */

	// k phai dau, qua ham render la len hinh r
#pragma endregion



	if (isAttacking == true)
	{
		if (whip->isFinish == false)
		{
			if (direction == -1)
			{
				whip->SetPosition(this->x - 30, this->y); //set pos cho bbox whip
			}
			else
			{
				whip->SetPosition(this->x, this->y);
			}

			whip->Update(dt, coObjects);

		}
		if (whip->isFinish == true)
		{
			isAttacking = false;
		}
		//whip->isFinish = true;
	}//whip
	//knife
	if (throwSubwp == true)
	{
		if (!subwp->isFinish) // chua finish thi update
		{
			subwp->SetPosition(subwp->x, subwp->y);
			subwp->Update(dt, coObjects);
		}
		if (subwp->isFinish == true) //finish thi cho quang
		{
			throwSubwp = 0;
		}

	}
	//stair
	if (isOnStair == true)
	{
		//bat dau tu ben duoi
		if (game->IsKeyDown(DIK_UP) && !isWalkFromTop)
		{
			if (direction == -1 && isLeft == 0)
			{
				direction = -direction;
			}
			if (direction == 1 && isLeft == 0)
			{
				vx = 0;
				vy = 0;
				x++;
				y--;
				CGameObject::Update(dt);

			}
			else if (direction == -1 && isLeft)
			{
				vx = 0;
				vy = 0;
				x--;
				y--;
				CGameObject::Update(dt);
			}



		} //bat dau tu ben duoi
		//di xuong o giua cau thang
		if (game->IsKeyDown(DIK_DOWN) && isWalkFromBot) {
			if (direction == 1 && isLeft == 0 || direction == -1 && isLeft == 1) { 
				direction = -direction; // dang o giua cau thang, huong ben phai ma` ko qua trai thi` quay lai, tuong tu
			}							// ben trai ma ko qua phai thi quay lai
			if (direction == -1 && isLeft == 0)
			{
				vx = 0;
				vy = 0;
				x--;
				y++;
				CGameObject::Update(dt);
			}
			else if (direction == 1 && isLeft == true)
			{
				vx = 0;
				vy = 0;
				x++;
				y++;
				CGameObject::Update(dt);
			}

		}//dang o giua cau thang

		//bat dau tu ben tren
		if (game->IsKeyDown(DIK_DOWN)&& !isWalkFromBot)
		{
			if (direction == 1 && isLeft == 1)
			{
				direction = -direction;
			}
			if (direction == 1 && isLeft == 0)
			{
				vx = 0;
				vy = 0;
				x++;
				y++;
				CGameObject::Update(dt);
			}
			else if(direction == -1 && isLeft )
			{
				vx = 0;
				vy = 0;
				x--;
				y++;
				CGameObject::Update(dt);
			}

		}//
		//die len o giua cau thang
		if (game->IsKeyDown(DIK_UP) && isWalkFromTop)
		{
			if (direction == -1 && isLeft == true || direction == 1 && isLeft == false) {
				direction = -direction; //giua cau thang, qua trai
			}
			if (direction == 1 && isLeft == true)
			{
				vx = 0;
				vy = 0;
				x++;
				y--;
				CGameObject::Update(dt);
			}
			else if (direction == -1 && isLeft == false)
			{
				vx = 0;
				vy = 0;
				x--;
				y--;
				CGameObject::Update(dt);
			}

		}
	}

	if (!isOnStair)
	{
		CGameObject::Update(dt);
		vy += SIMON_GRAVITY * dt;// Simple fall down
	}



	vector<LPGAMEOBJECT> coObjects_Brick;
	coObjects_Brick.clear();
	vector<LPGAMEOBJECT> coObjects_HiddenStair;
	coObjects_HiddenStair.clear();
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetTag() == 21)
			coObjects_Brick.push_back(coObjects->at(i));
		if (coObjects->at(i)->GetTag() == -7 || coObjects->at(i)->GetTag() == 7)
			coObjects_HiddenStair.push_back(coObjects->at(i));
	}


	CollisionWithBrick(&coObjects_Brick); // check Collision and update x, y for simon
	CollisionWithStair(&coObjects_HiddenStair);

	vector<LPGAMEOBJECT> coObjects_Item;
	coObjects_Item.clear();
	for (int i = 0; i < coItems->size(); i++)
		if (coItems->at(i)->GetTag() == 69)
			coObjects_Item.push_back(coItems->at(i));
	CollisionWithItem(&coObjects_Item);






}


void Simon::CollisionWithStair(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++) //check va cham stair duoi va tren
	{
		if (isColliding(this, coObjects->at(i)))
		{
			CGame *game = CGame::GetInstance();
			if (game->IsKeyDown(DIK_UP)) //stair duoi
			{
				if (coObjects->at(i)->GetTag() == -7)
				{
					isOnStair = true; //tren thang
					isBottomStair = true; //bat dau tu duoi
					isTopStair = false; //ko phai tren
					this->direction = coObjects->at(i)->direction; //gan simon direction = sarit direction
					this->isLeft = coObjects->at(i)->isLeft;
					isWalkFromBot = true;// o giua cau thang nhung o duoi
					isWalkFromTop = false; // o giua cau thang nhung o tren
				}

			}
			if (game->IsKeyDown(DIK_DOWN))
			{
				if (coObjects->at(i)->GetTag() == 7)
				{
					isOnStair = true;
					isTopStair = true;
					isBottomStair = false;
					this->direction = coObjects->at(i)->direction;
					this->isLeft = coObjects->at(i)->isLeft;
					isWalkFromTop = true;
					isWalkFromBot = false;

				}

			}

		}
	}
	if (isOnStair)
	{
		for (int i = 0; i < coObjects->size(); i++)  //check va cham khi dang di chuyen
		{
			if (isColliding(this, coObjects->at(i)))
			{
				if (coObjects->at(i)->GetTag() == 7 && isBottomStair == true)
				{
					isOnStair = false;
					isWalkFromBot = false;
				}
				if (coObjects->at(i)->GetTag() == -7 && isTopStair == true)
				{
					isOnStair = false;
					isWalkFromTop = false;
				}


			}
		}
	}
}

void Simon::Render(Camera *camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);

	if (direction == -1)
		_sprite->Draw(pos.x, pos.y);
	else
		_sprite->DrawFlipX(pos.x, pos.y);


	if (whip->isFinish == false)
	{
		whip->Render(camera);
	}
	if (throwSubwp == 1)
	{
		subwp->Render(camera);
	}
	RenderBoundingBox(camera);
}


void Simon::Left()
{
	direction = -1;
	whip->direction = -1;
}

void Simon::Right()
{
	direction = 1; // quay qua phải
	whip->direction = 1;
}

void Simon::Go()
{
	vx = SIMON_WALKING_SPEED * direction;
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

void Simon::AutoMove()
{
	Go();
	CGameObject::Update(dt);
	x += dx;
	_sprite->Update(dt);
}

void Simon::Stop()
{/*
	if (vx != 0)
		vx -= dt * SIMON_GRAVITY*0.1*direction;
	if (direction == 1 && vx < 0)
		vx = 0;
	if (direction == -1 && vx > 0)*/
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

	if (isOnStair)
	{
		for (int i = 0; i < coObjects->size(); i++) //aabb item
		{
			if (isColliding(this, coObjects->at(i)))
			{
				isOnStair = false;
				this->y = y - 25;



			}
		}
	}

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

bool Simon::isCollisionWithCheckPoint(CheckPoint* checkPoint)
{
	//for (int i = 0; i < coObjects->size(); i++) //aabb item
	//{
	if (isColliding(this, checkPoint))
	{
		return true;
	}
	//}
	return false;


}

void Simon::Attack()
{
	if (isAttacking == true) // đang tấn công thì thôi
		return;

	isAttacking = true;
	whip->Create(this->x, this->y, this->direction); // set vị trí weapon theo simon
}

void Simon::ThrowSubWp()
{
	if (throwSubwp == true) // đang tấn công thì thôi
		return;
	if (useableHeart != 0)
	{
		throwSubwp = 1;
		subwp->Create(this->x, this->y, this->direction);
		useableHeart--;
	}
}
