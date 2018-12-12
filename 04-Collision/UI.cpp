#include "UI.h"

UI::UI()
{
	simonHP = NULL;
	simonHP = NULL;
	
}


UI::~UI()
{
//	delete[] simonHPList;
	//delete[] enemyHPList;
}


bool UI::Initialize( Simon *simon, int bossHP)
{
	this->bossHP = bossHP;
	this->simon = simon;

	/*black = new Sprite(0, 0);
	black->Initialize(gDevice, "Resource\\sprites\\UI\\black.png");*/

	tBlack = new Texture("Resource\\sprites\\UI\\black.png", 1, 1, 1);
	black = new Sprite(tBlack, 100);


	tredEdge = new Texture("Resource\\sprites\\UI\\redEdge.bmp", 1, 1, 1);
	redEdge = new Sprite(tredEdge, 100);
	/*simonHPLists = new std::vector<Sprite*>();
	for (int i = 0; i < 16; i++)
	{
		tsimonHPList = new Texture("Resource\\sprites\\UI\\HP.png", 1, 1, 1);
		simonHPList = new Sprite(tsimonHPList, 100);
		
		Sprite* sprite = new Sprite(120 + 12 * (i + 1), 43);
		sprite->Initialize(gDevice, "Resource\\sprites\\UI\\HP.png");

		simonHPList->push_back(sprite);
	}
	enemyHPList = new std::vector<Sprite*>();
	for (int i = 0; i < 16; i++)
	{
		Sprite* sprite = new Sprite(120 + 12 * (i + 1), 67);
		sprite->Initialize(gDevice, "Resource\\sprites\\UI\\EnemyHP.png");
		enemyHPList->push_back(sprite);
	}
	noHPList = new std::vector<Sprite*>();
	for (int i = 0; i < 16; i++)
	{
		Sprite* sprite = new Sprite(120 + 12 * (i + 1), 43);
		sprite->Initialize(gDevice, "Resource\\sprites\\UI\\NoHP.png");
		noHPList->push_back(sprite);
	}*/

	/*heart = new Sprite(420, 43);
	heart->Initialize(gDevice, "Resource\\sprites\\UI\\Heart.png");
*/

	tHeart = new Texture("Resource\\sprites\\UI\\Heart.png", 1, 1, 1);
	heart = new Sprite(tHeart, 100);

	/*axe = new Sprite(350, 55);
	axe->Initialize(gDevice, "Resource\\sprites\\UI\\AXE.png");*/

	tAxe = new Texture("Resource\\sprites\\UI\\AXE.png", 1, 1, 1);
	axe = new Sprite(tAxe, 100);

	/*holyWater = new Sprite(350, 55);
	holyWater->Initialize(gDevice, "Resource\\sprites\\UI\\HOLY_WATER.png");*/

	tHolyWater = new Texture("Resource\\sprites\\UI\\HOLY_WATER.png", 1, 1, 1);
	holyWater = new Sprite(tHolyWater, 100);

	/*cross = new Sprite(350, 55);
	cross->Initialize(gDevice, "Resource\\sprites\\UI\\CROSS.png");
*/
	tCross = new Texture("Resource\\sprites\\UI\\CROSS.png", 1, 1, 1);
	cross = new Sprite(tCross, 100);

	/*knife = new Sprite(350, 55);
	knife->Initialize(gDevice, "Resource\\sprites\\UI\\KNIFE.png");*/

	tKnife = new Texture("Resource\\sprites\\UI\\KNIFE.png", 1, 1, 1);
	knife = new Sprite(tKnife, 100);

	



	tsimonHPList = new Texture("Resource\\sprites\\UI\\HP.png", 1, 1, 1);
	simonHPList = new Sprite(tsimonHPList,100);

	tnoHPList = new Texture("Resource\\sprites\\UI\\NoHP.png", 1, 1, 1);
	noHPList = new Sprite(tnoHPList, 100);

	/*stopWatch = new Sprite(350, 55);
	stopWatch->Initialize(gDevice, "Resource\\sprites\\UI\\STOP_WATCH.png");

	tBlack = new Texture("Resource\\sprites\\UI\\black.png", 1, 1, 1);
	black = new Sprite(tBlack, 100);

	upgrade1 = new Sprite(500, 55);
	upgrade1->Initialize(gDevice, "Resource\\sprites\\UI\\DOUBLE_SHOOT_UI.png");

	tBlack = new Texture("Resource\\sprites\\UI\\black.png", 1, 1, 1);
	black = new Sprite(tBlack, 100);

	upgrade2 = new Sprite(500, 55);
	upgrade2->Initialize(gDevice, "Resource\\sprites\\UI\\TRIPLE_SHOOT_UI.png");

	tBlack = new Texture("Resource\\sprites\\UI\\black.png", 1, 1, 1);
	black = new Sprite(tBlack, 100);*/
	LPDIRECT3DDEVICE9 G_Device = CGame::GetInstance()->GetDirect3DDevice();
	font = NULL;
	AddFontResourceEx(L"Resource\\font\\prstart.ttf", FR_PRIVATE, NULL);
	HRESULT result = D3DXCreateFont(
		G_Device, 20, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, L"Press Start", &font);

	if (!SUCCEEDED(result))
		return false;

	SetRect(&rect, 0, 2, 640, 480);
	information = "SCORE_000000 TIME 0000 STAGE 00\n";
	information += "PLAYER                =62\n";
	information += "ENEMY                P=3\n";
	
}


void UI::Update(int bossHP, int time, int life, int stage)
{

#pragma region Calculate boss HP in UI

	if (bossHP <= 0)
		this->uiHP = 0;
	else {
		int x = bossHP / (this->bossHP / 16);
		int y = bossHP % (this->bossHP / 16);

		if (y == 0)
			this->uiHP = x;
		else
			this->uiHP = x + 1;
	}

#pragma endregion

	this->time = time;
	this->stage = stage;


	std::string scoreString = std::to_string(simon->scores+whip->score);
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
	information += "x:" + std::to_string(simon->x) + "y:" + std::to_string(simon->y);
	

	/*switch (simon->currentWeapon)
	{
	case ITEM_AXE:
		weapon = nullptr;
		weapon = axe;
		break;
	case ITEM_HOLY_WATER:
		weapon = nullptr;
		weapon = holyWater;
		break;
	case ITEM_CROSS:
		weapon = nullptr;
		weapon = cross;
		break;
	case ITEM_KNIFE:
		weapon = nullptr;
		weapon = knife;
		break;
	case ITEM_STOP_WATCH:
		weapon = nullptr;
		weapon = stopWatch;
		break;
	default:
		break;
	}*/
}

void UI::Render()
{
	/*RECT newRect;
	SetRect(&newRect, 0, 0, 640, 116);*/
	//black->Draw(black->GetPosition(), newRect);
	if (font)
		font->DrawTextA(NULL, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));


	//for (std::vector<Sprite*>::iterator i = noHPList->begin(); i != noHPList->end(); i++)
	//{
	//	SetRect(&newRect, 0, 0, 8, 15);
	//	(*i)->Render((*i)->GetPosition(), newRect);
	//	D3DXVECTOR3 newPosition = (*i)->GetPosition();
	//	newPosition.y = 67;
	//	(*i)->Render(newPosition, newRect);
	//}


	int count = 0;
	/*for (std::vector<Sprite*>::iterator i = simonHPList->begin(); i != simonHPList->end(); i++)
	{
		if (count < simon->GetHP())
		{
			SetRect(&newRect, 0, 0, 8, 15);
			(*i)->Render((*i)->GetPosition(), newRect);
		}
		count++;
	}*/


	count = 0;
	/*for (std::vector<Sprite*>::iterator i = enemyHPList->begin(); i != enemyHPList->end(); i++)
	{
		if (count < uiHP)
		{
			SetRect(&newRect, 0, 0, 8, 15);
			(*i)->Render((*i)->GetPosition(), newRect);
		}
		count++;
	}*/


	//D3DXVECTOR3 newPosition = { 330, 45, 0 };
	//SetRect(&newRect, 0, 0, 70, 45);
	//(*enemyHPList)[0]->Render(newPosition, newRect);

	//SetRect(&newRect, 0, 0, 16, 16);
	for (int i = 0; i <= simon->health; i+=5)
	{
		simonHPList->Draw(i*2+130, 27);
	}
	for (int i = 0; i <=80- simon->health; i += 5)
	{
		noHPList->Draw(290-i*2, 27);
	}
	heart->Draw(420,27);
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
	
	/*weapon->Render(weapon->GetPosition());

	switch (simon->GetNoSubWeapon()) {
	case 2: upgrade1->Render(upgrade1->GetPosition()); break;
	case 3: upgrade2->Render(upgrade2->GetPosition()); break;
	}*/
}