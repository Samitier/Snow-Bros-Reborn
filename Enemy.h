#pragma once

#include "cBicho.h"

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
	bool hit;
	bool isSnowball;
	int life;
	int timecount;
};
