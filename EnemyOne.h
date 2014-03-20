#pragma once
#include "enemy.h"
class EnemyOne :
	public Enemy
{
public:
	EnemyOne(void);
	~EnemyOne(void);
	virtual void AI(int *map);
	virtual void Draw(int tex_id);
	void fire();

private:
	int movsps;
	int rnd;
};

