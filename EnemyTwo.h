#pragma once
#include "enemy.h"

class EnemyTwo :
	public Enemy
{
public:
	EnemyTwo(void);
	~EnemyTwo(void);
	virtual void AI(int *map);
	virtual void Draw(int tex_id);

private:
	int movsps;
	int rnd;
};



