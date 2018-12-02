#pragma once
#include "GameObject.h"
#define HEART_PATH "Resource\\sprites\\Items\\BIG_HEART.png"
#define BALL_PATH "Resource\\sprites\\Items\\13.png"
#define DOUBLE_PATH "Resource\\sprites\\Items\\DOUBLE_SHOT.png"
#define INVI_PATH "Resource\\sprites\\Items\\INVICIBILITY_ITEM.png"
#define BLUEBLAG_PATH "Resource\\sprites\\Items\\Money_bag_blue.png"
#define REDBAG_PATH "Resource\\sprites\\Items\\Money_bag_red.png"
#define WHITEBAG_PATH "Resource\\sprites\\Items\\Money_bag_white.png"
#define WHIP_PATH "Resource\\sprites\\Items\\MORNING_STAR.png"
#define ROAST_PATH  "Resource\\sprites\\Items\\ROAST.png"
#define ROSARY_PATH  "Resource\\sprites\\Items\\ROSARY.png"
#define SHEART_PATH "Resource\\sprites\\Items\\SMALL_HEART.png"
#define STOPWATCH_PATH "Resource\\sprites\\Items\\STOP_WATCH.png"
#define TRIPLE_PATH  "Resource\\sprites\\Items\\TRIPLE_SHOT.png"

//ITEM TAG 
#define HEART_TAG 69
#define BALL_TAG 102
#define DOUBLE_TAG 103
#define INVI_TAG 104
#define BLUEBLAG_TAG 105
#define REDBAG_TAG 106
#define WHITEBAG_TAG 107
#define WHIP_TAG 108
#define ROAST_TAG  109
#define ROSARY_TAG  110
#define SHEART_TAG 111
#define STOPWATCH_TAG 112
#define TRIPLE_TAG  113
class Item :public CGameObject
{
public:
	
	Item(int X, int Y);
	Item(char* link,int X,int Y);
	Item();
	~Item();
	char* PathRandom();
	float remainingTime;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);
	int GetIsCreated();
	void RenderBoundingBox(Camera* camera);
};
