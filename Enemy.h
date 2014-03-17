#pragma once

#include "cBicho.h"

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
	bool hit;
	bool isSnowball;
	int life;
	int timecount;
};
