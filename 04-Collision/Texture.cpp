#include "Texture.h"

Texture::Texture(char* fileName, int cols, int rows, int count)
{
	mfile = fileName;
	mcols = cols;
	mrows = rows;
	mcount = count;
	this->Load();
}

Texture::Texture(char* fileName, int cols, int rows, int count, int R, int G, int B)
{
	mfile = fileName;
	mcols = cols;
	mrows = rows;
	mcount = count;	
	this->Load(R, G, B);
}



void Texture::Draw(int x, int y)
{
	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXVECTOR3 position((float)x, (float)y, 0);
	spriteHandler->Draw(texture, &rect, NULL, &position, 0xFFFFFFFF);
}



void Texture::Load()
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	LPDIRECT3DDEVICE9 G_Device = CGame::GetInstance()->GetDirect3DDevice();


	result = D3DXGetImageInfoFromFileA(mfile, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	this->rect = s;

	FrameWidth = info.Width / mcols;//160 68
	FrameHeight = info.Height / mrows;

	if (result != D3D_OK)
	{
		OutputDebugStringA(mfile);
		return;
	}

	result = D3DXCreateTextureFromFileExA(
		G_Device,
		mfile,
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



	result = D3DXGetImageInfoFromFileA(mfile, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	this->rect = s;

	FrameWidth = info.Width / mcols;
	FrameHeight = info.Height / mrows;

	if (result != D3D_OK)
	{
		OutputDebugStringA(mfile);
		return;
	}

	result = D3DXCreateTextureFromFileExA(
		G_Device,
		mfile,
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