#include "EnemyOne.h"

int movsps;
int rnd;
EnemyOne::EnemyOne(void)
{
	movsps = 0;
	rnd = rand()%100;
}

void EnemyOne::Draw(int tex_id) {
	float xo,yo,xf,yf;
	xo=0.125*4; yo=0.125;
	xf = 0.125*5;
	yf = 0;


	if(isHit()) {
		int l;
		GetLife(&l);
		xo=0.125*(l-1);
		xf=xo+0.125;
		bool b;
		IsSnowball(&b);
		if(!b) {
			yo=(GetFrame()+1)*0.125; yf = GetFrame()*0.125;
		}
		NextFrame(2);
	}

	DrawRect(tex_id,xo,yo,xf,yf);
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
