#pragma once
#include "enemy.h"
#include "cProjectile.h"
#include "cData.h"

class EnemyTwo :
	public Enemy
{
public:
	EnemyTwo(void);
	~EnemyTwo(void);
	virtual void AI(int *map);
	virtual void Draw(int tex_id);
	virtual void Logic(int *map);

private:
	int movsps;
	int rnd;
	int timeThrowing;
};



