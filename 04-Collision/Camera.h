#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
protected:
	
	D3DXVECTOR2 _viewport;
	int _width;
	int _height;

	/*int _borderLeft;
	int _borderRight;*/

public:
	
	Camera(int w, int h/*, int b_left, int b_right*/);
	~Camera();

	void Update();
	void UpdateMap2();
	D3DXVECTOR2 Transform(int x, int y);

	void SetPosition(int x, int y);

	D3DXVECTOR2 GetViewport();

	int GetWidth();
	int GetHeight();
	
};

#endif




