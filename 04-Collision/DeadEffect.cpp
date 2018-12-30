#include "DeadEffect.h"


DeadEffect::~DeadEffect()
{
}

DeadEffect::DeadEffect()
{
	//_texture = new Texture("Resource\\sprites\\Effect\\DEAD.png", 3, 1, 3);
	//_sprite = new Sprite(_texture, 50);
	isVisible = false;
	isDoneRender = false;
}



void DeadEffect::Update(DWORD dt)
{
	if (isVisible)
	{
		remainingTime--;
		if (remainingTime < 0)
		{
			isVisible = false;
			isDoneRender = true;
		}
		_sprite->Update(dt);
	}

}

void DeadEffect::Render(Camera* camera)
{
	if (isVisible)
	{
		D3DXVECTOR2 pos = camera->Transform(x, y);
		_sprite->Draw(pos.x, pos.y);
	}

	//CGameObject::RenderBoundingBox();
}
