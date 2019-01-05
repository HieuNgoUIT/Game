#include "Texture.h"

Texture::Texture(char* fileName, int cols, int rows, int count)
{
	Cols = cols;
	Rows = rows;
	Count = count;
	FileName = fileName;
	this->Load();
}

Texture::Texture(char* fileName, int cols, int rows, int count, int R, int G, int B)
{
	Cols = cols;
	Rows = rows;
	Count = count;
	FileName = fileName;
	this->Load(R, G, B);
}



void Texture::Draw(int x, int y)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXVECTOR3 position((float)x, (float)y, 0);
	spriteHandler->Draw(texture, &Size, NULL, &position, 0xFFFFFFFF);
}



void Texture::Load()
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	LPDIRECT3DDEVICE9 G_Device = CGame::GetInstance()->GetDirect3DDevice();


	result = D3DXGetImageInfoFromFileA(FileName, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	this->Size = s;

	FrameWidth = info.Width / Cols;//160 68
	FrameHeight = info.Height / Rows;

	if (result != D3D_OK)
	{
		OutputDebugStringA(FileName);
		return;
	}

	result = D3DXCreateTextureFromFileExA(
		G_Device,
		FileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), 
		&info,
		0,
		&texture
	);

	if (result != D3D_OK)
	{
		return;
	}
}

void Texture::Load(int R, int G, int B)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	LPDIRECT3DDEVICE9 G_Device = CGame::GetInstance()->GetDirect3DDevice();



	result = D3DXGetImageInfoFromFileA(FileName, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	this->Size = s;

	FrameWidth = info.Width / Cols;
	FrameHeight = info.Height / Rows;

	if (result != D3D_OK)
	{
		OutputDebugStringA(FileName);
		return;
	}

	result = D3DXCreateTextureFromFileExA(
		G_Device,
		FileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(R, G, B), 
		&info,
		0,
		&texture
	);

	if (result != D3D_OK)
	{
		
		return;
	}
}

Texture::~Texture()
{
	if (this->texture != NULL)
		this->texture->Release();
}