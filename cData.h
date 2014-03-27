#pragma once

#include <SFML/Audio.hpp>
#include "cTexture.h"
#include "Globals.h"

//Array size
#define NUM_IMG			7
#define NUM_AUDIO		1

//Image identifiers
#define IMG_BLOCKS		0
#define IMG_PLAYER		1
#define IMG_BACKGROUND	2
#define IMG_ENEMY		3
#define IMG_ENEMY2      4
#define IMG_MENU		5
#define IMG_PARTICLE	6

//Sound identifiers
#define SOUND_SELECT	0

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);
	
	bool LoadSound(int id, string filename);
	void PlaySound(int id);

private:
	cTexture texture[NUM_IMG];
	
	sf::SoundBuffer buffer;
	string audiofiles[NUM_AUDIO];
};
