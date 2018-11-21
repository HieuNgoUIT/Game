﻿#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"

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
	int tag;
	int id; // ID của object
	int health;
	float x; 
	float y;
	bool dropItem;
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt
	int isCreated = 0;
	float vx;
	float vy;
	bool isTake;
	int direction;
	bool isCreatedItem=false;
	int state;
	bool isDead;
	DWORD dt; 
	
	Texture * _texture;
	Sprite * _sprite;
	Texture *texturebox = new Texture("textures\\bbox.png");

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	//int GetState() { return this->state; }

	void RenderBoundingBox( Camera *camera);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);
	bool isColliding(LPGAMEOBJECT object, LPGAMEOBJECT other);
	void AddAnimation(int aniId);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera)=0 ;
	virtual void SetState(int state) { this->state = state; }
	int GetTag();
	void SetDropItem(bool x) { this->dropItem = x; }

	~CGameObject();
};

