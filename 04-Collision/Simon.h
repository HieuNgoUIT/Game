﻿#ifndef __SIMON_H__
#define __SIMON_H__


#define SIMON_POSITION_DEFAULT  50.0f, 101


#define SIMON_GRAVITY 0.005f
#define SIMON_VJUMP 0.9f

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
#include "SubWeapon.h"
#include "CheckPoint.h"
#include "Zombie.h"
#include "Knife.h"
#include "Axe.h"
#include "Sound.h"
#include "HolyWater.h"
#include "HiddenStair.h"

//#include "Weapon.h"
//#include "MorningStar.h"

class Simon : public CGameObject
{
public:
	static Simon * sinstance;
	static Simon * GetInstance();

	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isAttacking;
	bool throwSubwp;
	bool isSubwp;//co subwp ko
	bool isOnStair;//tren thang

	bool isBottomStair;//check co dang o duoi ko
	bool isWalkFromBot;//check dang tren cau thang, dung de xy ly cau thang
	bool isWalkFromTop;
	bool isTopStair;

	bool isFightingBoss;

	bool isStage1;
	bool isStage2;//canh dau
	bool isStage21;//after 1 dooor
	bool isStage22;//after 2 door

	bool isRosary;
	bool isStopwatch;

	bool isrenderKnife;
	bool isrenderHolyWater;
	bool isrenderAxe;
	bool isrenderRosary;

	bool isCollideDor;
	//bool isDoneCameraStair;
	
	int useableHeart = 5;
	int scores;
	int life = 3;
	int countupdatesprite;

	Whip* whip;
	SubWeapon *subwp;

public:
	Simon();
	~Simon();

	int untouchable;
	DWORD untouchable_start;
	int beingHit;
	DWORD beingHit_start;

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartBeingHit() { beingHit = 1; beingHit_start = GetTickCount(); }
	void CollisionWithItem(vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void ResetLife();
	void CheckBoundaries(int left,int right);

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, vector<LPGAMEOBJECT>* coItems = NULL);
	
	void  CollisionWithStair(vector<LPGAMEOBJECT>* coObjects);
	void Render(Camera *camera);
	void RenderBoundingBox(Camera *camera);

	void Left(); 
	void Right(); 
	void Go();
	void Sit();
	void Jump();
	void AutoMove();

	void Stop();

	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithEnemy(vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithDoor(vector<LPGAMEOBJECT> *coObjects = NULL);
	bool isCollisionWithCheckPoint(CheckPoint *checkpoint);

	void Attack();
	void ThrowSubWp();

};






#endif