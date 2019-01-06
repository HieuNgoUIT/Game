#include "Whip.h"
int  Whip::score = 0;

int Whip::GetScore()
{
	return score;
}
Whip::Whip(int X, int Y)
{
	_texture = new Texture("Resource\\sprites\\Weapons\\whip1.png", 4, 3, 12);
	_sprite = new Sprite(_texture, 100);
	x = X;
	y = Y;
	tag = 2;
	typeOfWhip = 0;//whip lv dau
	//health = 1;
	//isFinish = 1;
}

Whip::Whip()
{
	/*_texture = new Texture("Resource\\sprites\\Weapons\\whip1.png", 4, 3, 12);
	_sprite = new Sprite(_texture, 100);*/

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
	if (_sprite->GetIndex() == 2 || _sprite->GetIndex() == 6 || _sprite->GetIndex() == 10) // set frame cuoi moi getbb
	{
		if (typeOfWhip < 2)
		{

			if (direction == -1)
			{
				left = x - 45;
				top = y + 20;
				right = x;
				bottom = y + _texture->FrameHeight - 30;
			}
			else
			{
				left = x + 50;
				top = y + 20;
				right = x + _texture->FrameWidth - _texture->FrameHeight / 2 - 20;
				bottom = y + _texture->FrameHeight - 30;
			}
		}
		else
		{
			if (direction == -1)
			{
				left = x - 80;
				top = y + 20;
				right = x;
				bottom = y + _texture->FrameHeight - 30;
			}
			else
			{
				left = x + 50;
				top = y + 20;
				right = x + _texture->FrameWidth - 20;
				bottom = y + _texture->FrameHeight - 30;
			}
		}
	}

}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int index = _sprite->GetIndex();

	if (typeOfWhip == 0)
	{
		if (index == 3)
		{
			if (index < 0 || index >= 2)//update main whip
				_sprite->SelectIndex(0);
			isFinish = true;
		}
	}


	if (typeOfWhip == 1)
	{
		if (index < 4 || index >= 7)
		{
			_sprite->SelectIndex(4);
		}
		if (index == 7)
		{
			isFinish = true;
		}
	}
	if (typeOfWhip == 2)
	{
		if (index < 8 || index >= 11)
		{
			_sprite->SelectIndex(8);
		}
		if (index == 11)
		{
			isFinish = true;
		}
	}
	_sprite->Update(dt);

	vector<LPGAMEOBJECT> coObjects_LargeCandle;
	coObjects_LargeCandle.clear();
	vector<LPGAMEOBJECT> coObjects_Zombie;
	coObjects_Zombie.clear();
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetTag() == LARGECANDLE_TYPE || coObjects->at(i)->GetTag() == CANDLE_TYPE)
			coObjects_LargeCandle.push_back(coObjects->at(i));
		if (coObjects->at(i)->GetTag() == ENEMY_TAG || coObjects->at(i)->GetTag() == BREAKABLEBRICK_TAG)
			coObjects_Zombie.push_back(coObjects->at(i));

	}
	CollisionWithEnemy(&coObjects_Zombie);
	CollisionWithLargeCandle(&coObjects_LargeCandle);

}
void Whip::CollisionWithLargeCandle(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (isColliding(this, coObjects->at(i)))
		{
			coObjects->at(i)->isDead = true;
			Sound::GetInstance()->Play(HIT_SOUND);
		}
	}

}
void Whip::CollisionWithCandle(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (isColliding(this, coObjects->at(i)))
		{
			coObjects->at(i)->isDead = true;
		}
	}
}
void Whip::CollisionWithEnemy(vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (isColliding(this, coObjects->at(i)))
		{
			coObjects->at(i)->health -= 10;
			this->score += 100;
			if (dynamic_cast<Boss *>(coObjects->at(i)))
			{
				Boss *boss = dynamic_cast<Boss *>(coObjects->at(i));
				boss->StartUntouchable();
				Sound::GetInstance()->Play(HIT_SOUND);
			}
		}
	}
}

void Whip::Create(float simonX, float simonY, int simondirection)
{
	this->x = simonX;
	this->y = simonY;
	this->direction = simondirection;
	isFinish = false;
	this->_sprite->SelectIndex(0);
}
void Whip::Render(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (direction == -1)
		_sprite->Draw(pos.x - 75, pos.y);
	else
		_sprite->DrawFlipX(pos.x - 25, pos.y);
	RenderBoundingBox(camera);
}
