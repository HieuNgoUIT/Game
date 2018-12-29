#include "Textures.h"

Textures::Textures()
{
}
void Textures::Add(int id, char* filePath, int cols, int rows, int count)
{
	Texture *_texture = new Texture(filePath, cols, rows, count);
	textures[id] = _texture;
}

Texture * Textures::Get(int id)
{
	return textures[id];
}

Textures * Textures::__instance = NULL;



Textures *Textures::GetInstance()
{
	if (__instance == NULL) __instance = new Textures();
	return __instance;
}
