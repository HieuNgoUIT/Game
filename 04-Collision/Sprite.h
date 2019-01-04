#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Camera.h"
#include "Texture.h"
#include "Game.h"


class Sprite {
public:
	Texture * _texture;

	int _start;
	int _end;
	int _index;
	int _timeAni;
	int _timeLocal;
	float width, height;
	float GetWidth();
	float GetHeight();
	Sprite();
	Sprite(const Sprite &sprite);
	Sprite(Texture* texture, int timeAnimation);
	Sprite(Texture* texture, int start, int end, int timeAnimation);


	void Next();

	void PlayAnimation(int start, int end, int ellapseTime);

	void Reset();


	void SelectIndex(int index);


	void Update(int ellapseTime);


	void Draw(int x, int y);


	void DrawFlipX(int x, int y);

	int GetIndex();


	~Sprite();


	int R, G, B, A;
	void SetARGB(int r = 255, int g = 255, int b = 255, int a = 255);
};

