#include "Camera.h"





Camera::Camera(int w, int h/*, int b_left, int b_right*/)
{
	_width = w;
	_height = h;
	
	SetPosition(0, 0);
}

Camera::~Camera()
{
}

void Camera::Go(DWORD dt)
{
	float vx = 0.15f;
	float	dx = vx * dt;
	_viewport.x += dx;

}

//void Camera::StairGo(DWORD dt, int stairDirection)
//{
//	if (stairDirection)
//	{
//		vx = 0.05f;
//	}
//	else
//	{
//		vx = -0.05f;
//	}
//	float	dx = vx * dt;
//	_viewport.x += dx;
//}

void Camera::Update()
{
	if (_viewport.x < _borderLeft)
	{
		_viewport.x = _borderLeft;
	}
	if (_viewport.x >_borderRight)
	{
		_viewport.x = _borderRight;
	}
}

void Camera::UpdateMap2()
{
	if (_viewport.x < 60)
	{
		_viewport.x =60;
	}
	if (_viewport.x > 2500)
	{
		_viewport.x = 2500;
	}
}

void Camera::UpdateMap21()
{
	if (_viewport.x < 3150)
	{
		_viewport.x = 3150;
	}
	if (_viewport.x > 3532)
	{
		_viewport.x = 3532;
	}
}

void Camera::UpdateMap22()
{
	if (_viewport.x < 4154)
	{
		_viewport.x = 4154;
	}
	if (_viewport.x > 5069)
	{
		_viewport.x = 5069;
	}
}

void Camera::UpdateWater()
{
	if (_viewport.x < 3250)
	{
		_viewport.x = 3250;
	}
	if (_viewport.x > 3642)
	{
		_viewport.x = 3642;
	}
}

D3DXVECTOR2 Camera::Transform(int x, int y)
{

	return D3DXVECTOR2(x - _viewport.x, y - _viewport.y);
}

void Camera::SetPosition(int x, int y)
{
	_viewport.x = x;
	_viewport.y = y;
}


D3DXVECTOR2 Camera::GetViewport()
{
	return _viewport;
}

int Camera::GetWidth()
{
	return _width;
}

int Camera::GetHeight()
{
	return _height;
}


