#pragma once
#include "GameObject.h"
#include "LargeCandle.h"
#include "HitEffect.h"
#include "Sound.h"
#include "Boss.h"
class Whip :public CGameObject
{
public:
	static int score;
	static int GetScore();
	Whip(int X, int Y);
	Whip();
	~Whip();
	bool isFinish;
	int typeOfWhip;
	void RenderBoundingBox(Camera* camera);
	 void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	 void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	 void CollisionWithLargeCandle(vector<LPGAMEOBJECT>* coObjects);
	 void CollisionWithCandle(vector<LPGAMEOBJECT>* coObjects);
	 void CollisionWithEnemy(vector<LPGAMEOBJECT> *coObjects = NULL);
	
	 void Create(float simonX, float simonY, int simondirection);
 void Render(Camera * camera);
};

