#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "fmod.hpp"


//Array size
#define NUM_IMG			7
#define NUM_AUDIO		11

//Image identifiers
#define IMG_BLOCKS		0
#define IMG_PLAYER		1
#define IMG_BACKGROUND	2
#define IMG_ENEMY		3
#define IMG_ENEMY2      4
#define IMG_MENU		5
#define IMG_PARTICLE	6

//Sound identifiers
#define SOUND_SELECT		0
#define SOUND_JUMP		    1
#define SOUND_ENEMY_DEATH	2
#define SOUND_PLAYER_DEATH	3
#define SOUND_PLAYER_SHOT	4
#define SOUND_ENEMY_SHOT	5
#define SOUND_SNOWBALL_SHOT 6
#define SOUND_GAME_OVER     7
#define SOUND_VICTORY       8
#define SOUND_ACCEPT        9
#define MUSIC_MAIN			10

class cData
{
public:
	cData(void);
	~cData(void);
	void init();

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

	
	bool LoadSound(int id, char *filename);
	bool LoadMusic(int id, char *filename);

	void PlayMusic(int id);
	void PlaySound(int id);

	void StopMusic();
	void PauseMusic();

	void Update();
	void Release();

private:
	cTexture texture[NUM_IMG];
	FMOD::Sound  *sound[NUM_AUDIO];

	//FMod Stuff
	FMOD::System     *system; //handle to FMOD engine
	FMOD::Channel *channelMusic;
};


