#pragma once
#include "Camera.h"
#include "Texture.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Game.h"


class Sprite {
public:
	Texture * _texture;

	int _start;
	int _timeAni;
	int _timeLocal;
	int _end;
	int _index;
	
	float width, height;
	float GetWidth();
	float GetHeight();
	Sprite();
	Sprite(const Sprite &sprite);
	Sprite(Texture* texture, int timeAni);
	Sprite(Texture* texture, int start, int end, int timeAni);


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

