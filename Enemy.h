#pragma once

#include "cBicho.h"

class Enemy: public cBicho
{
public:
	Enemy();
	~Enemy();

	void init();
	void Draw(int tex_id);
	void Move(int *map);

private:
	int amountOfSnow;
	int points;
	int movsps;
	int rnd;
};