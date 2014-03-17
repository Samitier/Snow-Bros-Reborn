#include "Enemy.h"
#include <stdlib.h> 
Enemy::Enemy() { 
}

Enemy::~Enemy(){}

void Enemy::init() {
	movsps =0;
	hit = false;
	isSnowball = false;
	rnd = rand()%100; 
	life = 0;
	timecount =0;
}

void Enemy::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	xo=0.125*4; yo=0.125;
	xf = 0.125*5;
	yf = 0;

	if(hit) {
		xo=0.125*(life-1);
		xf=xo+0.125;
		if(!isSnowball) {
			yo=(GetFrame()+1)*0.125; yf = GetFrame()*0.125;
		}
		NextFrame(2);
	}

	DrawRect(tex_id,xo,yo,xf,yf);
}

void Enemy::Logic(int *map)
{	
	if(!hit) {
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
	if(hit) {
		++timecount;
		if(timecount>=TIME_WITH_SNOW*life) {
			timecount =0;
			--life;
			isSnowball = false;
			if(life ==0) hit = false;
		}
	}
	cBicho::Logic(map);
}

bool Enemy::isHit() {
	return hit;
}
void Enemy::Hit() {
	hit=true;
	++life;
	timecount =0;
	if(life>=TOTAL_HITS) {
		life =TOTAL_HITS;
		isSnowball = true;
	}
}
