#include "UI.h"

UI::UI()
{
	simonHP = NULL;
	simonHP = NULL;

}


UI::~UI()
{
}


bool UI::Initialize(Simon *simon, Boss *boss)
{
	this->boss = boss;
	this->simon = simon;

	tBlack = new Texture("Resource\\sprites\\UI\\black.png", 1, 1, 1);
	black = new Sprite(tBlack, 100);


	tredEdge = new Texture("Resource\\sprites\\UI\\redEdge.bmp", 1, 1, 1);
	redEdge = new Sprite(tredEdge, 100);


	tHeart = new Texture("Resource\\sprites\\UI\\Heart.png", 1, 1, 1);
	heart = new Sprite(tHeart, 100);



	tAxe = new Texture("Resource\\sprites\\UI\\AXE.png", 1, 1, 1);
	axe = new Sprite(tAxe, 100);



	tHolyWater = new Texture("Resource\\sprites\\UI\\HOLY_WATER.png", 1, 1, 1);
	holyWater = new Sprite(tHolyWater, 100);



	tCross = new Texture("Resource\\sprites\\UI\\CROSS.png", 1, 1, 1);
	cross = new Sprite(tCross, 100);



	tKnife = new Texture("Resource\\sprites\\UI\\KNIFE.png", 1, 1, 1);
	knife = new Sprite(tKnife, 100);





	tsimonHPList = new Texture("Resource\\sprites\\UI\\HP.png", 1, 1, 1);
	simonHPList = new Sprite(tsimonHPList, 100);

	tenemyHPList = new Texture("Resource\\sprites\\UI\\EnemyHP.png", 1, 1, 1);
	enemyHPList = new Sprite(tenemyHPList, 100);

	tnoHPList = new Texture("Resource\\sprites\\UI\\NoHP.png", 1, 1, 1);
	noHPList = new Sprite(tnoHPList, 100);


	LPDIRECT3DDEVICE9 G_Device = CGame::GetInstance()->GetDirect3DDevice();
	font = NULL;
	AddFontResourceEx(L"Resource\\font\\prstart.ttf", FR_PRIVATE, NULL);
	HRESULT result = D3DXCreateFont(
		G_Device, 20, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"Press Start", &font);

	if (!SUCCEEDED(result))
		return false;

	SetRect(&rect, 0, 10, SCREEN_WIDTH, SCREEN_HEIGHT);
	information = "SCORE_000000 TIME 0000 STAGE 00\n";
	information += "PLAYER                =62\n";
	information += "ENEMY                P=3\n";

}


void UI::Update(int time, int life, int stage, int bosshp)
{
	this->bossHP = bosshp;
#pragma region Calculate boss HP in UI

	/*if (bossHP <= 0)
		this->uiHP = 0;
	else {
		int x = bossHP / (this->bossHP / 16);
		int y = bossHP % (this->bossHP / 16);

		if (y == 0)
			this->uiHP = x;
		else
			this->uiHP = x + 1;
	}*/

#pragma endregion

	this->time = time;
	this->stage = stage;


	std::string scoreString = std::to_string(simon->scores + whip->score);
	while (scoreString.length() < 6)
		scoreString = "0" + scoreString;


	std::string timeString = std::to_string(this->time);
	while (timeString.length() < 4)
		timeString = "0" + timeString;


	std::string stageString = std::to_string(this->stage);
	while (stageString.length() < 2)
		stageString = "0" + stageString;


	information = "SCORE_" + scoreString + " TIME " + timeString + " STAGE " + stageString + "\n";
	information += "PLAYER                =" + std::to_string(simon->useableHeart) + "\n";
	information += "ENEMY                P=" + std::to_string(simon->life) + "\n";

}

void UI::Render()
{

	if (font)
		font->DrawTextA(NULL, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));



	for (int i = 0; i <= simon->health; i += 5)
	{
		simonHPList->Draw(i * 2 + 130, 37);
	}
	for (int i = 0; i <= 80 - simon->health; i += 5)
	{
		noHPList->Draw(290 - i * 2, 37);
	}


	for (int i = 0; i <= bossHP; i += 5)
	{
		enemyHPList->Draw(i * 2 + 130, 60);
	}
	for (int i = 0; i <= 80 - bossHP; i += 5)
	{
		noHPList->Draw(290 - i * 2, 60);
	}



	heart->Draw(420, 27);
	redEdge->Draw(320, 27);
	if (simon->isrenderKnife)
	{
		knife->Draw(345, 45);
	}
	if (simon->isrenderAxe)
	{
		axe->Draw(345, 45);
	}
	if (simon->isrenderHolyWater)
	{
		holyWater->Draw(345, 45);
	}


}