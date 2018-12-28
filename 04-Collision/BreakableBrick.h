

#define BRICK_FRAME_WIDTH 32
#define BRICK_FRAME_HEIGHT 32

#include "GameObject.h"
#include "Camera.h"
#include "BrickEffect.h"
class BreakableBrick : public CGameObject
{
protected:
	int width;
	int height;
	int type;
	BrickEffect *be1;
	BrickEffect *be2;
	BrickEffect *be3;
	BrickEffect *be4;
public:
	BreakableBrick(int TYPE, int X, int Y, int W, int H);
	void Render(Camera *camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Update(DWORD dt, float simonx = 0, vector<LPGAMEOBJECT> *coObjects = NULL);

};


