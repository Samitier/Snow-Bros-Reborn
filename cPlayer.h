#pragma once

#include "cProjectile.h"
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
	virtual bool CollidesMapFloor (int *map);
	void EraseProjectile(int i);
	vector<cProjectile> GetProjectiles();
	void GetCurrentPoints(int* p);
	void GetCurrentLives(int* l);
	int GetSnowballPushing();
	void SetSnowballPushing(int snowball);
	int GetSnowballOnTopOf();
	void SetSnowballOnTopOf(int snowball);
private: 
	int timecount;
	float alfa;
	int points;
	float incAlfa;
	int lives;
	int snowballPushing;
	int snowballOnTopOf;
	vector<cProjectile> projectiles;

};
