#pragma once
#include "enemy.h"
#include "cProjectile.h"

class EnemyOne :
	public Enemy
{
public:
	EnemyOne(void);
	~EnemyOne(void);
	virtual void AI(int *map);
	virtual void Draw(int tex_id);

private:
	int movsps;
	int rnd;
	vector<cProjectile> projectiles;
};

