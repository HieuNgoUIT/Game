#include "Sprite.h" 


Sprite::Sprite()
{	
	mStart = 0;	
	mTimeAni = 0;
	mTimeLocal = 0;
	mEnd = 0;
	mIndex = 0;
	SetRGBA();
	_texture = NULL;
}



Sprite::Sprite(Texture* texture, int start, int end, int timeAni)
	: _texture(texture)
{
	mStart = start;
	mTimeLocal = 0;
	mTimeAni = timeAni;
	mEnd = end;
	mIndex = start;	
	SetRGBA();
}

Sprite::Sprite(Texture* texture, int timeAni)
	: _texture(texture)
{
	mStart = 0;
	mTimeLocal = 0;
	mTimeAni = timeAni;
	mEnd = _texture->mcount - 1;
	mIndex = 0;	
	SetRGBA();
}

Sprite::~Sprite()
{
	if (_texture != NULL)
		delete _texture;
}

void Sprite::SetRGBA(int r, int g, int b, int a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

void Sprite::Next()
{
	mIndex++;
	if (mIndex > mEnd)
		mIndex = mStart;
}
void Sprite::Reset()
{
	mIndex = mStart;
	mTimeLocal = 0;
}
void Sprite::PlayAnimation(int start, int end, int ellapseTime)
{
	if (mIndex < start || mIndex > end)
	{
		SelectIndex(start);
	}
	Update(ellapseTime);
	
}



void Sprite::SelectIndex(int index)
{
	mIndex = index;
}

void Sprite::Update(int ellapseTime)
{
	mTimeLocal += ellapseTime;

	if (mTimeLocal >= mTimeAni)
	{
		mTimeLocal = 0;
		this->Next();
	}
}

void Sprite::Draw(int X, int Y)
{
	RECT srect;

	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();



	srect.left = (mIndex % _texture->mcols)*(_texture->FrameWidth);
	srect.top = (mIndex / _texture->mcols)*(_texture->FrameHeight);
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;

	//D3DXVECTOR3 position(0, 0, 0);
	//D3DXVECTOR3 center(0, 0, 0);
	//position.x = X - _texture->FrameWidth / 2;
	//position.y = Y - _texture->FrameHeight / 2;

	D3DXVECTOR3 p(X, Y, 0);
	spriteHandler->Draw(
		_texture->texture,
		&srect,
		NULL,
		&p,
		D3DCOLOR_ARGB(R, G, B, A)
	);


}

void Sprite::DrawFlipX(int x, int y)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;

	D3DXVECTOR2 top_left = D3DXVECTOR2(x, y);

	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= _texture->FrameWidth;
	this->Draw(x, y);

	spriteHandler->SetTransform(&oldMt);
}


int Sprite::GetIndex()
{
	return mIndex;
}
//bool Sprite::Initialize(const char *file)
//{
//
//	if (LoadTexture(device, file) == NULL)
//	{
//		LPCSTR file_ = file;
//		MessageBox(NULL, file_, "Error", MB_OK);
//		return initialized;
//	}
//
//	HRESULT result;
//
//	//create sprite
//	result = D3DXCreateSprite(device, &spriteHandle);
//	if (FAILED(result))
//	{
//		MessageBox(NULL, "Error creating Direct 3D sprite", "Error", MB_OK);
//		return initialized;
//	}
//
//	initialized = true;
//	return initialized;
//}
float Sprite::GetWidth()
{
	return width;
}

float Sprite::GetHeight()
{
	return height;
}

