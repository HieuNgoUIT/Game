﻿#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"
#include "HitEffect.h"
#include "DeadEffect.h"
#include "debug.h"
#include "Textures.h"
using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:
	int texId;
	int tag;
	int health;
	float x; 
	float y;	
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt
	float vx;
	float vy;
	bool isTake;//grid
	int direction;
	bool isDead;
	bool isLeft;

	int isCreated = 0; // danh cho item
	bool dropItem; //danh cho item
	int itemNumber;

	DWORD dt; 

	HitEffect *hiteffect;
	DeadEffect *deadffect;

	Texture * _texture;
	Sprite * _sprite;

	

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void RenderBoundingBox( Camera *camera);
	void UpdateEffect(DWORD dt);
	void RenderEffect(Camera* camera);
	int GetTag();
	void SetDropItem(bool x) { this->dropItem = x; }
	bool isColliding(LPGAMEOBJECT object, LPGAMEOBJECT other);
	void AddAnimation(int aniId);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, float simonx = 0, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera) = 0;

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);
	

	CGameObject();
	~CGameObject();
};

