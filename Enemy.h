#pragma once

#include "cBicho.h"

#define STATE_HIT 25
#define STATE_SNOWBALL 26
#define STATE_STUNNED 27
#define STATE_SNOWBALL_MOVING 28

#define ENEMY_ONE 0
#define ENEMY_TWO 1

class Enemy: public cBicho
{
public:
	Enemy(int type);
	~Enemy();

	void init();
	void Draw(int tex_id, bool pause);
	void Logic(int *map);
	void GetArea(cRect *rc);
	void Hit();
	void AI(int *map);
	bool isHit();
	bool IsSnowball();
	void GetLife(int* l);
	void GetTimecount(int* t);
	void ShootSnowballLeft();
	void ShootSnowballRight();
	void Die();
	int getType();
	int getDirection();
	void SetDirection(int dir);


protected:
	int amountOfSnow;
	int points;
	int movsps;
	int rnd;
	int life;
	int timecount;
	int direction;
	int timeThrowing;
	int enemyType;
};
