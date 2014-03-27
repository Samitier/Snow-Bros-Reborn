#pragma once

#include "cProjectile.h"
#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

#define STATE_WINING_LEVEL 15

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	bool dead; 
	bool invincible;

	void init();
	void Draw(int tex_id, bool pause);
	
	void Die();

	bool isDead();
	bool isInvincible();
	bool checkCanThrow();


	virtual void Logic(int *map);
	virtual bool CollidesMapFloor (int *map);
	int GetCurrentPoints();
	int GetCurrentLives();
	int GetSnowballPushing();
	void SetSnowballPushing(int snowball);
	int GetSnowballOnTopOf();
	void SetSnowballOnTopOf(int snowball);
	void ResetPosition();
	void SetCurrentPoints(int pts);

private: 
	int timecount;
	float alfa;
	int points;
	float incAlfa;
	int lives;
	int snowballPushing;
	int snowballOnTopOf;

	int timeThrowing;
};
