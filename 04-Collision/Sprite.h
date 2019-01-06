#pragma once
#include "Camera.h"
#include "Texture.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Game.h"


class Sprite {
public:
	Texture * _texture;

	int mStart;
	int mTimeAni;
	int mTimeLocal;
	int mEnd;
	int mIndex;
	
	float width, height;
	float GetWidth();
	float GetHeight();
	Sprite();
	
	Sprite(Texture* texture, int timeAni);
	Sprite(Texture* texture, int start, int end, int timeAni);

	int GetIndex();
	void Next();
	void PlayAnimation(int start, int end, int ellapseTime);
	void Reset();
	void SelectIndex(int index);
	void Update(int ellapseTime);
	void Draw(int x, int y);
	void DrawFlipX(int x, int y);
	int R, G, B, A;
	void SetRGBA(int r = 255, int g = 255, int b = 255, int a = 255);
	~Sprite();

	
};

