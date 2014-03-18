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
	virtual void Draw(int tex_id);
	virtual void Logic(int *map);
	void Hit();
	virtual void AI(int *map);
	bool isHit();
	void IsSnowball(bool* b);
	void GetLife(int* l);
	void GetTimecount(int* t);

private:
	int amountOfSnow;
	int points;
	int movsps;
	int rnd;
	int life;
	int timecount;
};
