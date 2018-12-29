#pragma once
#include "Texture.h"
#include <unordered_map>

using namespace std;
class Textures {
	static Textures * __instance;
	unordered_map<int, Texture*> textures;

public:
	Textures();
	void Add(int id, char* filePath,int cols,int rows,int count);
	Texture* Get( int id);

	static Textures * GetInstance();
};