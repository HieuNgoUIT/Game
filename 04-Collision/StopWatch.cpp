#include "StopWatch.h"

StopWatch::~StopWatch()
{
}
StopWatch::StopWatch()
{
}
void StopWatch::Update(DWORD dt, float left, float right, vector<LPGAMEOBJECT>* coObjects)
{
	remainingTime--;
	if (remainingTime < 0)
	{
		this->isFinish = true;
	}
	else
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			coObjects->at(i)->SetSpeed(0, 0);
		}
	}
	

}
void StopWatch::Create(float simonX, float simonY, int simondirection)
{
	this->remainingTime = 300;//set thoi gian ton tai vu khi
	this->isFinish = false;
	
}
