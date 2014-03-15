#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	bool isDead; //must set to false in init function
	bool isInvincible;

	int currentLives; //must set to PLAYER_MAX_LIVES in init function

	void init();
	void Draw(int tex_id);
	
	void Die();
	
	bool checkIfPlayerDead(int time);

	bool checkIfPlayerInvincible(int time);

	int GetCurrentLives();

private: 
	int timecount;
	float alfa;
	float incAlfa;
};
