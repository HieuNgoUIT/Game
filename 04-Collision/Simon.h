#ifndef __SIMON_H__
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
#include "SubWeapon.h"
#include "CheckPoint.h"
#include "Zombie.h"
#include "Knife.h"
#include "Axe.h"
#include "Sound.h"
#include "HiddenStair.h"
//#include "Weapon.h"
//#include "MorningStar.h"

class Simon : public CGameObject
{
public:

	bool isWalking;
	bool isJumping;
	bool isSitting;
	bool isAttacking;
	bool throwSubwp;
	bool isOnStair;
	bool isBottomStair;//check co dang o duoi ko
	bool isWalkFromBot;//check dang tren cau thang
	bool isWalkFromTop;
	bool isTopStair;
	bool isStage21;
	bool isCameraStair;
	bool isDoneCameraStair;
	//bool isKnife;
	int useableHeart = 50;
	int score = 0;
	Whip* whip;
	SubWeapon *subwp;
	bool isSubwp;
public:
	Simon();
	~Simon();
	int untouchable;
	DWORD untouchable_start;
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void CollisionWithItem(vector<LPGAMEOBJECT>* coObjects);
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	 void PreProcessOnStair(CGameObject *hiddenstair,  Camera *camera);
	 void PreProcessBeforeOnStair(CGameObject *hiddenstair, Camera *camera);
	 void Update(DWORD dt,  Camera *camera, vector<LPGAMEOBJECT> *coObjects = NULL, vector<LPGAMEOBJECT>* coItems=NULL);
	// void UpdatewItem(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	 void  CollisionWithStair(vector<LPGAMEOBJECT>* coObjects , Camera *camera);
	 void Render(Camera *camera);
	 void RenderBoundingBox(Camera *camera);

	void Left();  // set lại hướng của simon
	void Right(); // set lại hướng của simon
	void Go();
	void Sit();
	void Jump();
	void AutoMove();

	void Stop();

	void CollisionWithBrick(vector<LPGAMEOBJECT> *coObjects = NULL);
	void CollisionWithZombie(vector<LPGAMEOBJECT> *coObjects = NULL);
	bool isCollisionWithCheckPoint(CheckPoint *checkpoint);
	void Attack();
	void ThrowSubWp();

};






#endif