#include "Enemy.h"
#include <stdlib.h> 
Enemy::Enemy() { 
}

Enemy::~Enemy(){}

void Enemy::init() {
	movsps =0;
	rnd = rand()%100; 
}

void Enemy::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	xo=0; yo=1;
	xf = 1;
	yf = 0;

	DrawRect(tex_id,xo,yo,xf,yf);
}

void Enemy::Move(int *map)
{	
	++movsps;
	if(movsps == 30) {
		movsps =0;
		rnd = rand()%100; 
	}
	if(rnd < 45) {
			MoveLeft(map);
		}
	else if(rnd<90) {
		MoveRight(map);
	}
	else {
		Jump(map);
		rnd = rand()%100; 
	}
}
