#include "EnemyTwo.h"


EnemyTwo::EnemyTwo(void)
{
	movsps = 0;
	rnd = rand()%100;
}

void EnemyTwo::Draw(int tex_id) { 
	Enemy::Draw(tex_id);
}

EnemyTwo::~EnemyTwo(void)
{
}


void EnemyTwo::AI(int *map)
{	
	++movsps;
	if(movsps == 30) {
		movsps =0;
		rnd = rand()%100; 
	}
	else if(rnd <= 80 && CanJump(map)) {
		Jump(map);
	}
	else if(rnd < 50) {
		MoveLeft(map);
	}
	else if (rnd > 50) {
		MoveRight(map);
	}
}