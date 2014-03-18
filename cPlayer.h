#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	bool dead; 
	bool invincible;

	void init();
	void Draw(int tex_id);
	
	void Die();

	bool isDead();
	bool isInvincible();
	bool checkCanThrow();

	virtual void Logic(int *map);

	void GetCurrentPoints(int* p);
	void GetCurrentLives(int* l);

private: 
	int timecount;
	float alfa;
	int points;
	float incAlfa;
	int lives;
};
