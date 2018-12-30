#include "HitEffect.h"


HitEffect::~HitEffect()
{
}

HitEffect::HitEffect()
{
	//_texture = new Texture("Resource\\sprites\\Effect\\0.png", 1, 1, 1);
	//_sprite = new Sprite(_texture, 1000);
	isVisible = false;
	isDoneRender = false;
}



void HitEffect::Update(DWORD dt)
{
	if (isVisible)
	{
		remainingTime--;
		if (remainingTime < 0)
		{
			isVisible = false;
			isDoneRender = true;
		}
	}

}

void HitEffect::Render(Camera* camera)
{
	if (isVisible)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		_sprite->Draw(pos.x, pos.y);
	}
	
	//CGameObject::RenderBoundingBox();
}
