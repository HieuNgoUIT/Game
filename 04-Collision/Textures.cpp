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

void Textures::LoadTexture(char * filename)
{
	std::ifstream input;
	input.open(filename, std::ifstream::in);

	int id;
	int col, row, count;
	char* link="";
	string checkEnd;

	while (input >> checkEnd)
	{
		if (checkEnd == "END")
		{
			break;
		}
		link = const_cast<char*>(checkEnd.c_str());
		input >>col>>row>>count >> id;
		Add(id, link, col, row,count);
	}
}

Textures * Textures::__instance = NULL;



Textures *Textures::GetInstance()
{
	if (__instance == NULL) __instance = new Textures();
	return __instance;
}
