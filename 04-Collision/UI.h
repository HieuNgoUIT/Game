#pragma once
#include "d3dx9.h"
#include "Camera.h"
#include <string>
#include "Sprite.h"
#include <vector>
#include "Simon.h"

class UI
{
private:
	ID3DXFont *font;
	RECT rect;
	Simon *simon;

	std::string information;

	Texture * tredEdge;
	Sprite* redEdge;

	Texture * tsimonHPList;
	Sprite* simonHPList;

	
	Texture * tenemyHPList;
	Sprite* enemyHPList;

	
	Texture * tnoHPList;
	Sprite* noHPList;

	Sprite* heart;
	Texture * tHeart;
	Sprite* weapon;
	Texture * tWeapon;
	Sprite* black;
	Texture * tBlack;
	Sprite* axe;
	Texture * tAxe;
	Sprite* holyWater;
	Texture * tHolyWater;
	Sprite* cross;
	Texture * tCross;
	Sprite* knife;
	Texture * tKnife;
	Sprite* stopWatch;
	Texture * tStopWatch;
	
	Sprite* upgrade1;
	Texture * tUpGrade1;
	Sprite* upgrade2;
	Texture * tUpGrade2;

	int simonHP;
	int bossHP;
	int uiHP;

	int score;
	int time;
	int item;
	int energy;
	int life;
	int stage;
	int subWeapon;

public:
	UI();
	~UI();
	bool Initialize( Simon *simon, int bossHP);
	void Update(int bossHP, int time, int life, int stage);
	void Render();
};