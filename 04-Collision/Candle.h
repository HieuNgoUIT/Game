#pragma once
#include "GameObject.h"
#include "Item.h"
class Candle :public CGameObject {
public:
	Item * item;
	Candle(int TYPE,int X, int Y,int numberItem);
	~Candle();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, float simonx = 0, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera * camera);
	char* ConvertItemNumbertoString(int number);
};