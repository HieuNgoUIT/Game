#include "WaterEffect.h"


WaterEffect::~WaterEffect()
{
}

WaterEffect::WaterEffect()
{
	_texture = new Texture("Resource\\sprites\\Effect\\2.png", 1, 1, 1);
	_sprite = new Sprite(_texture, 100);
	isVisible = false;
	isDoneRender = false;

}



void WaterEffect::Update(DWORD dt)
{
	y++;

}

void WaterEffect::Render(Camera* camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	_sprite->Draw(pos.x, pos.y);
	//CGameObject::RenderBoundingBox();
}
