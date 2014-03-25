#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "cObject.h"
#define PARTICLE_SIZE 128

class cParticle
{
public:
	cParticle(void);
	cParticle(int x,int y);
	~cParticle(void);

	void Draw(int text_id);

	void NextFrame(int max);
	int  GetFrame();
	bool Dead();

protected:
	int x,y;
	int seq;
	int delay;
	float alfa;
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
};
