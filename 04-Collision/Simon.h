﻿#ifndef __SIMON_H__
#define __SIMON_H__


#define SIMON_POSITION_DEFAULT  50.0f, 0


#define SIMON_GRAVITY 0.005f
#define SIMON_VJUMP 0.8f

#define SIMON_WALKING_SPEED 0.2f //0.12f 




#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING 1



#define SIMON_ANI_BEGIN_WALKING 1
#define SIMON_ANI_END_WALKING 3
#define SIMON_ANI_BEGIN_HITTING 5
#define SIMON_ANI_END_HITTING 7
#define SIMON_ANI_BEGIN_SITHITTING 15
#define SIMON_ANI_END_SITHITTING 17

#define SiMON_ANI_IDLE 0

#define SIMON_ANI_JUMPING 4

#define SIMON_ANI_SITTING 4




#include "GameObject.h"
#include "Camera.h"
#include "LargeCandle.h"
#include "Whip.h"
#include "debug.h"
//#include "Weapon.h"
//#include "MorningStar.h"

class Simon : public CGameObject
{
public:

	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isAttacking;

	Whip* whip;

public:
	Simon();
	~Simon();


	void CollisionWithItem(vector<LPGAMEOBJECT>* coObjects);
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	 void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	// void UpdatewItem(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	 void Render(Camera *camera);
	 void RenderBoundingBox(Camera *camera);

	void Left();  // set lại hướng của simon
	void Right(); // set lại hướng của simon
	void Go();
	void Sit();
	void Jump();


	void Stop();

	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);

	void Attack();


};






#endif