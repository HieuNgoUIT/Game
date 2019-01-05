#pragma once

#define SIMON_POSITION_DEFAULT  50.0f, 101

#define SIMON_WALKING_SPEED 0.2f //0.12f 

#define SIMON_GRAVITY 0.005f
#define SIMON_VJUMP 0.9f


#define SIMON_STATE_IDLE 0
#define SIMON_STATE_WALKING 1



#define SIMON_ANI_BEGIN_WALKING 1
#define SIMON_ANI_END_WALKING 3

#define SIMON_ANI_BEGIN_HITTING 5
#define SIMON_ANI_END_HITTING 7

#define SIMON_ANI_BEINGHIT 8

#define SIMON_ANI_BEGIN_GOSTAIRUP 12
#define SIMON_ANI_END_GOSTAIRUP 13

#define SIMON_ANI_BEGIN_GOSTAIRDOWN 10
#define SIMON_ANI_END_GOSTAIRDOWN 11

#define SIMON_ANI_BEGIN_SITHITTING 15
#define SIMON_ANI_END_SITHITTING 17

#define SIMON_ANI_BEGIN_STAIRHITUP 21
#define SIMON_ANI_END_STAIRHITUP 23

#define SIMON_ANI_BEGIN_STAIRHITDOWN 18
#define SIMON_ANI_END_STAIRHITDOWN 20

#define SiMON_ANI_IDLE 0

#define SIMON_ANI_JUMPING 4

#define SIMON_ANI_SITTING 4

#include "GameObject.h"
#include "Camera.h"
#include "LargeCandle.h"
#include "Whip.h"
#include "SubWeapon.h"
#include "CheckPoint.h"
#include "Zombie.h"
#include "Knife.h"
#include "Axe.h"
#include "Sound.h"
#include "HolyWater.h"
#include "HiddenStair.h"
#include "Bmr.h"
#include "debug.h"

class Simon : public CGameObject
{
public:
	static Simon * sinstance;
	static Simon * GetInstance();

	bool isBottomStair;//check co dang o duoi ko
	bool isWalkFromBot;//check dang tren cau thang, dung de xy ly cau thang
	bool isWalkFromTop;
	bool isTopStair;

	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isAttacking;
	bool throwSubwp;
	bool isSubwp;//co subwp ko
	bool isOnStair;//tren thang

	bool isFightingBoss;
	bool isRosary;
	bool isStopwatch;
	bool isCollideDor;
	bool isCollideCheckPoint;

	int useableHeart = 5;
	int scores;
	int life = 3;
	int isRenderSubwp;

	Whip* whip;
	SubWeapon *subwp;

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
	void CheckBoundaries(int left, int right);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, vector<LPGAMEOBJECT>* coItems = NULL);
	void CollisionWithStair(vector<LPGAMEOBJECT>* coObjects);
	void Render(Camera *camera);
	void RenderBoundingBox(Camera *camera);


	void Move();
	void Sit();
	void Jump();
	void AutoMove();
	void SetDirectionLeft();
	void SetDirectionRight();
	void Stop();
	void Attack();
	void ThrowSubWp();

	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithEnemy(vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithDoor(vector<LPGAMEOBJECT> *coObjects = NULL);
	bool isCollisionWithCheckPoint(LPGAMEOBJECT checkpoint);
	
	vector<LPGAMEOBJECT> coObjects_Brick;
	vector<LPGAMEOBJECT> coObjects_HiddenStair;	
	vector<LPGAMEOBJECT> coObjects_Enemy;	
	vector<LPGAMEOBJECT> coObjects_Door;
	LPGAMEOBJECT checkpoint = NULL;
};






