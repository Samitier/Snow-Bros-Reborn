#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG			5

//Image identifiers
#define IMG_BLOCKS		0
#define IMG_PLAYER		1
#define IMG_BACKGROUND	2
#define IMG_ENEMY		3
#define IMG_ENEMY2      4


class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
