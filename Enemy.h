#pragma once

#include "cBicho.h"

#define STATE_HIT 25
#define STATE_SNOWBALL 26
#define STATE_STUNNED 27

class Enemy: public cBicho
{
public:
	Enemy();
	~Enemy();

	void init();
	void Draw(int tex_id);
	void Logic(int *map);
	void Hit();
	bool isHit();

private:
	int amountOfSnow;
	int points;
	int movsps;
	int rnd;
	int life;
	int timecount;
};
