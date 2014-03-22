#include "EnemyOne.h"


EnemyOne::EnemyOne(void)
{
	movsps = 0;
	rnd = rand()%100;
}

void EnemyOne::Draw(int tex_id) { 
	int s = state;
	Enemy::Draw(tex_id);
}

EnemyOne::~EnemyOne(void)
{
}


void EnemyOne::AI(int *map)
{	
	++movsps;
	if(movsps == 30) {
		movsps =0;
		rnd = rand()%100; 
	}
	else {
		if(rand()%1000 <= 5) {
			Jump(map);
		}
		if(rnd < 50) {
			MoveLeft(map);
		}
		else if (rnd > 50) {
			MoveRight(map);
		}
	}
	if (rand()%1000 < 500) Throw(map);
}