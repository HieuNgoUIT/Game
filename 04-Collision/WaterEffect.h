#pragma once
#include "Texture.h"
#include "Sprite.h"

class WaterEffect {
public:
	float x, y;
	float vx, vy, dx, dy;
	float remainingTime = 10;
	bool isVisible;
	bool isDoneRender;
	Texture * _texture;
	Sprite * _sprite;
	WaterEffect();
	~WaterEffect();

	void Update(DWORD dt,int direction);
	void Render(Camera *camera);
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
};