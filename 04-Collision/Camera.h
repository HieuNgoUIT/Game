#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
public:
	D3DXVECTOR2 _viewport;

	int _width;
	int _height;
	float vx;
	int _borderLeft;
	int _borderRight;

	Camera(int w, int h);
	~Camera();

	void SetBorder(int bleft, int bright) { this->_borderLeft = bleft, this->_borderRight = bright; }
	void Go(DWORD dt);
	void SetBoundaries();
	void SetBoundariesWater();
	void SetPosition(int x, int y);
	D3DXVECTOR2 GetViewport();
	D3DXVECTOR2 Transform(int x, int y);
	int GetWidth();
	int GetHeight();
	
};






