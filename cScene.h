#pragma once

#include "cTexture.h"

#define SCENE_Xo		0
#define SCENE_Yo		0


class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id, int tex_id0);
	int *GetMap();

private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int id_DL;								//actual level display list
	int id_DL0;
	
};
