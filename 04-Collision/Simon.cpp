#include "Simon.h"

Simon * Simon::sinstance = NULL;

Simon * Simon::GetInstance()
{
	if (sinstance == NULL)
		sinstance = new Simon();
	return sinstance;
}

Simon::Simon()
{
	_texture = new Texture("Resource\\sprites\\simon.png", 8, 3, 24);
	_sprite = new Sprite(_texture, 150);
	whip = new Whip(x, y);
	subwp = new SubWeapon(/*x, y*/);
	tag = 1;

	isWalking = 0;
	isJumping = 0;
	isSitting = 0;
	isAttacking = 0;

	direction = 1;
	health = 80; // dinh 8 lan, =80 tai vi render thanh mau 16x5

	//_ListWeapon.clear();
	//_ListWeapon.push_back(new MorningStar());
}

Simon::~Simon()
{
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (isSitting == true)
	{
		left = x + 12;
		top = y - 1;
		right = x + _texture->FrameHeight;
		bottom = y + _texture->FrameHeight - 21;
	}
	else if (isOnStair)
	{
		/*if (direction == 1)
		{*/
		left = x + 20;
		top = y + 20;
		right = x + _texture->FrameWidth;
		bottom = y + _texture->FrameHeight - 3;
		/*	}
			else
			{
				left = x + 12;
				top = y - 1;
				right = x + _texture->FrameWidth - 15;
				bottom = y + _texture->FrameHeight - 3;
			}
	*/
	}

	else
	{
		left = x + 12;
		top = y - 1;
		right = x + _texture->FrameWidth - 15;
		bottom = y + _texture->FrameHeight - 3;
	}

}

void Simon::CheckBoundaries(int left, int right)
{
	if (x < left)
	{
		x = left;
	}
	if (x > right)
	{
		x = right;
	}
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems)
{
	CGame *game = CGame::GetInstance();

	if (GetTickCount() - untouchable_start > 5000)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount() - beingHit_start > 500)
	{
		beingHit_start = 0;
		beingHit = 0;
	}


#pragma region Sprite update
	if (untouchable)
	{
		_sprite->SetRGBA(100, 100, 100);//mau trong suot
	}
	else
	{
		_sprite->SetRGBA();
	}

	if (isRenderSubwp == true)
	{
		int index = _sprite->GetIndex();
		if (index < SIMON_ANI_BEGIN_HITTING || index >SIMON_ANI_END_HITTING)
		{
			_sprite->SelectIndex(SIMON_ANI_BEGIN_HITTING);
			if (index > SIMON_ANI_BEGIN_HITTING)
			{
				isRenderSubwp = false;
			}
		}
		_sprite->Update(dt);
	}
	else if (beingHit)
	{
		_sprite->SelectIndex(SIMON_ANI_BEINGHIT);
	}
	else if (isOnStair)
	{
		if (isAttacking == true)
		{
			if (direction == 1) //di len
			{
				_sprite->PlayAnimation(SIMON_ANI_BEGIN_STAIRHITUP, SIMON_ANI_END_STAIRHITUP, dt);
			}
			else
			{
				_sprite->PlayAnimation(SIMON_ANI_BEGIN_STAIRHITDOWN, SIMON_ANI_END_STAIRHITDOWN, dt);
			}


		}
		else if (game->IsKeyDown(DIK_UP))
		{
			_sprite->PlayAnimation(SIMON_ANI_BEGIN_GOSTAIRUP, SIMON_ANI_END_GOSTAIRUP, dt);

		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			_sprite->PlayAnimation(SIMON_ANI_BEGIN_GOSTAIRDOWN, SIMON_ANI_END_GOSTAIRDOWN, dt);
		}




	}
	else if (isSitting == true) //dang ngoi
	{
		if (isAttacking == true)
		{
			_sprite->PlayAnimation(SIMON_ANI_BEGIN_SITHITTING, SIMON_ANI_END_SITHITTING, dt);
		}
		else
		{
			_sprite->SelectIndex(SIMON_ANI_SITTING);
		}
	}
	else if (isWalking == true) // đang di chuyển
	{
		if (isJumping == false) // ko nhảy
		{
			if (isAttacking == true)
			{
				_sprite->PlayAnimation(SIMON_ANI_BEGIN_HITTING, SIMON_ANI_END_HITTING, dt);
			}
			else
			{
				_sprite->PlayAnimation(SIMON_ANI_BEGIN_WALKING, SIMON_ANI_END_WALKING, dt);
			}

		}
		else
		{
			if (isAttacking == true)
			{
				_sprite->PlayAnimation(SIMON_ANI_BEGIN_HITTING, SIMON_ANI_END_HITTING, dt);
			}
			else
			{
				_sprite->SelectIndex(SIMON_ANI_JUMPING);
			}

		}

	}
	else
	{
		if (isJumping == true) // nếu ko đi mà chỉ nhảy
		{
			if (isAttacking == true)
			{
				_sprite->PlayAnimation(SIMON_ANI_BEGIN_HITTING, SIMON_ANI_END_HITTING, dt);
			}
			else
			{
				_sprite->SelectIndex(SIMON_ANI_JUMPING);
			}

		}
		else if (isAttacking == true)
		{
			_sprite->PlayAnimation(SIMON_ANI_BEGIN_HITTING, SIMON_ANI_END_HITTING, dt);
		}
		else
		{
			_sprite->SelectIndex(SiMON_ANI_IDLE);		// SIMON đứng yên
		}
	}


	/* Update về sprite */


#pragma endregion

	if (isAttacking == true)
	{
		if (whip->isFinish == false)
		{

			whip->SetPosition(this->x, this->y); //set pos cho bbox whip
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
			//subwp->SetPosition(subwp->x, subwp->y+10);
			subwp->Update(dt, x - SCREEN_WIDTH / 2, x + SCREEN_WIDTH / 2, coObjects);
			if (dynamic_cast<StopWatch *>(subwp))
			{
				isStopwatch = true;
			}
		}
		if (subwp->isFinish == true) //finish thi cho quang
		{
			throwSubwp = false;
			if (dynamic_cast<StopWatch *>(subwp))
			{
				isStopwatch = false;
			}
		}

	}
	//stair
	if (isOnStair == true)
	{
		//bat dau tu ben duoi
		if (game->IsKeyDown(DIK_UP) && !isWalkFromTop)
		{
			if (direction == -1 && isLeft == 0 || direction == 1 && isLeft == 1)
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
		if (game->IsKeyDown(DIK_DOWN) && !isWalkFromBot)
		{
			if (direction == 1 && isLeft == true || direction == -1 && isLeft == false)
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
			else if (direction == -1 && isLeft)
			{
				vx = 0;
				vy = 0;
				x--;
				y++;
				CGameObject::Update(dt);
			}
			//if (direction == 3 && isLeft==0)//truong hop db water
			//{
			//	vx = 0;
			//	vy = 0;
			//	x=3230;
			//	y=520;
			//	direction = 1;
			//	isLeft = 0;
			//}


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
	else
	{
		CGameObject::Update(dt);
		vy += SIMON_GRAVITY * dt;// Simple fall down
								 //vx += 0.5f*dt;
	}


	coObjects_Brick.clear();
	coObjects_HiddenStair.clear();
	coObjects_Enemy.clear();
	coObjects_Door.clear();
	checkpoint = NULL;

	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetTag() == BRICK_TAG || coObjects->at(i)->GetTag() == BREAKABLEBRICK_TAG)
			coObjects_Brick.push_back(coObjects->at(i));
		if (coObjects->at(i)->GetTag() == BOTSTAIR || coObjects->at(i)->GetTag() == TOPSTAIR)
			coObjects_HiddenStair.push_back(coObjects->at(i));
		if (coObjects->at(i)->GetTag() == ENEMY_TAG)
			coObjects_Enemy.push_back(coObjects->at(i));
		if (coObjects->at(i)->GetTag() == DOOR_TYPE)
			coObjects_Door.push_back(coObjects->at(i));
		if (coObjects->at(i)->GetTag() == CP_TYPE)
			checkpoint = coObjects->at(i);
	}

	CollisionWithItem(coItems);
	CollisionWithEnemy(&coObjects_Enemy);
	CollisionWithBrick(&coObjects_Brick);
	CollisionWithStair(&coObjects_HiddenStair);
	CollisionWithDoor(&coObjects_Door);
	CollisionWithCheckPoint(checkpoint);
}

void Simon::Render(Camera *camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);

	if (direction == -1)
		_sprite->Draw(pos.x, pos.y);
	else
		_sprite->DrawFlipX(pos.x, pos.y);


	if (whip->isFinish == false && beingHit == 0)
	{
		whip->Render(camera);
	}
	if (throwSubwp == 1)
	{
		if (!dynamic_cast<StopWatch *>(subwp))
		{
			subwp->Render(camera);
		}

	}
	RenderBoundingBox(camera);
}

void Simon::SetDirectionLeft()
{
	direction = -1;
	whip->direction = -1;
}

void Simon::SetDirectionRight()
{
	direction = 1;
	whip->direction = 1;
}

void Simon::Move()
{
	vx = SIMON_WALKING_SPEED * direction;
	isWalking = 1;

}

void Simon::Sit()
{
	vx = 0;
	isWalking = 0;

	if (isSitting == false)
		y = y + 16;

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
	Move();
	CGameObject::Update(dt);
	x += dx;
	_sprite->Update(dt);
}

void Simon::Stop()
{
	vx = 0;
	isWalking = 0;
	if (isSitting == true)
	{
		isSitting = 0;
		y = y - 18;
	}

}

void Simon::Attack()
{
	if (isAttacking == true)
		return;

	isAttacking = true;
	Sound::GetInstance()->Play(USING_WHIP);
	whip->Create(this->x, this->y, this->direction);
}

void Simon::ThrowSubWp()
{

	if (throwSubwp == true) // đang tấn công thì thôi
		return;
	if (isSubwp)
	{
		if (useableHeart != 0)
		{
			throwSubwp = 1;
			//subwp->isDead = false;
			subwp->Create(this->x, this->y, this->direction);
			if (!dynamic_cast<StopWatch *>(subwp))
			{
				subwp->_sprite->SelectIndex(0);
			}


			useableHeart--;
			isRenderSubwp = 1;
		}
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

	CalcPotentialCollisions(coObjects, coEvents);


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
		y += min_ty * dy + ny * 0.4f; 

		if (nx != 0)
			vx = 0; 

		if (ny != 0)
		{
			vy = 0;
			isJumping = false; 
		}
		
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Simon::CollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		if (nx != 0 || ny != 0)
			if (untouchable == 0)
			{
				vx = 0.5f*direction;
				vy = -0.5f;
				CGameObject::Update(dt);
				y += dy;
				x += dx;
				StartUntouchable();
				StartBeingHit();
				health -= 10;
			}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void Simon::CollisionWithDoor(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (isColliding(this, coObjects->at(i)))
		{
			isCollideDor = true;
			Stop();
			coObjects->at(i)->_sprite->Update(dt);

		}
		else
		{
			isCollideDor = false;
		}
		if (x > coObjects->at(i)->x + _texture->FrameWidth)
		{
			coObjects->at(i)->isDead = true;
		}
	}
}

void Simon::CollisionWithItem(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++) //aabb item
	{
		if (isColliding(this, coObjects->at(i)))
		{
			if (coObjects->at(i)->tag == HEART_TAG)
			{
				this->useableHeart += 1;
			}
			else if (coObjects->at(i)->tag == WHIP_TAG)
			{
				whip->typeOfWhip += 1;
			}
			else if (coObjects->at(i)->tag == REDBAG_TAG)
			{
				scores += 100;
			}
			else if (coObjects->at(i)->tag == BLUEBLAG_TAG)
			{
				scores += 100;
			}
			else if (coObjects->at(i)->tag == KNIFE_TAG)
			{
				isSubwp = true;
				subwp = new Knife(x, y);

			}
			else if (coObjects->at(i)->tag == AXE_TAG)
			{
				isSubwp = true;
				subwp = new Axe(x, y);

			}
			else if (coObjects->at(i)->tag == HOLYWATER_TAG)
			{
				isSubwp = true;
				subwp = new HolyWater(x, y);

			}
			else if (coObjects->at(i)->tag == CROSS_TAG)
			{
				isSubwp = true;
				subwp = new Bmr(x, y);
			}
			else if (coObjects->at(i)->tag == ROSARY_TAG)
			{
				isRosary = true;

			}
			else if (coObjects->at(i)->tag == STOPWATCH_TAG)
			{
				isSubwp = true;
				subwp = new StopWatch();
			}

			coObjects->at(i)->isDead = true;
			Sound::GetInstance()->Play(COLLECT_ITEM);


		}
	}
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
					//PreProcessBeforeOnStair(coObjects->at(i), camera);
					//if (this->y <= coObjects->at(i)->y) // sau khi da dieu chinh vi tri thi cho no onstair
					//{
					isOnStair = true; //tren thang
									  //isCameraStair = false;//cho camera theo map lai bth
									  /*}*/
					isBottomStair = true; //bat dau tu duoi
					isTopStair = false; //ko phai tren
					this->direction = coObjects->at(i)->direction; //gan simon direction = sarit direction
					this->isLeft = coObjects->at(i)->isLeft;
					isWalkFromBot = true;// o giua cau thang nhung o duoi
					isWalkFromTop = false; // o giua cau thang nhung o tren
					if (direction == 1)
					{
						this->x = coObjects->at(i)->x;
						this->y -= 10;
					}
					else
					{
						this->x = coObjects->at(i)->x - 20;
						this->y -= 10;
					}



				}

			}
			if (game->IsKeyDown(DIK_DOWN))
			{
				if (coObjects->at(i)->GetTag() == 7)
				{
					/*	PreProcessBeforeOnStair(coObjects->at(i), camera);
					if (this->y >= coObjects->at(i)->y)
					{*/
					isOnStair = true; //tren thang
									  /*	isCameraStair = false;
									  }*/
					isTopStair = true;
					isBottomStair = false;
					this->direction = coObjects->at(i)->direction;
					this->isLeft = coObjects->at(i)->isLeft;
					isWalkFromTop = true;
					isWalkFromBot = false;
					if (direction == -1)
					{
						this->y += 25;
						this->x = coObjects->at(i)->x - 50;
					}
					else
					{
						this->y += 20;
						this->x = coObjects->at(i)->x + 35;
					}

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
					//PreProcessOnStair(coObjects->at(i), camera); // xu ly sau khi x > x stair thi tra ve iscamerastiar =false
					isWalkFromBot = false;

					//if (isCameraStair == false)
					//{
					isOnStair = false;//xu ly camera lai bth theo map
									  //}
				}
				if (coObjects->at(i)->GetTag() == -7 && isTopStair == true)
				{
					isOnStair = false;
					isWalkFromTop = false;
				}
				if (coObjects->at(i)->GetTag() == -7 && isBottomStair == true) //bat dau o dau, cham o do
				{
					isOnStair = false;

				}
				if (coObjects->at(i)->GetTag() == 7 && isTopStair == true)//bat dau o dau, cham o do
				{
					isOnStair = false;

				}

			}
		}
	}
}

void Simon::CollisionWithCheckPoint(LPGAMEOBJECT checkPoint)
{
	if (checkPoint != NULL)
	{
		CGame *game = CGame::GetInstance();
		if (isColliding(this, checkPoint))
		{
			if (game->IsKeyDown(DIK_UP))
			{
				isCollideCheckPoint = true;
			}
			else
			{
				isCollideCheckPoint = false;
			}
		}
	}




}


