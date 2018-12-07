#pragma once
#include "Texture.h"
#include "Sprite.h"

class WaterEffect {
public:
	int x, y;
	float remainingTime = 10;
	bool isVisible;
	bool isDoneRender;
	Texture * _texture;
	Sprite * _sprite;
	WaterEffect();
	~WaterEffect();

	void Update(DWORD dt);
	void Render(Camera *camera);
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
};