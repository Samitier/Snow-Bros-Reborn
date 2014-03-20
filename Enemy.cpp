#include "Enemy.h"
#include <stdlib.h> 

Enemy::Enemy() { 
}

Enemy::~Enemy(){}

void Enemy::init() {
	movsps =0;
	rnd = rand()%100; 
	life = 0;
	timecount =0;
}


void Enemy::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	
	switch(GetState())
	{
		case STATE_WALKLEFT:	xo = 0.125f*(1+GetFrame());	yo = 3*0.125f;
								xf =  0.125f*(2+GetFrame());	yf = 2*0.125; NextFrame(4);
								break;
		
		case STATE_WALKRIGHT:	xf = 0.125f*(1+GetFrame());	yo = 3*0.125f;
								xo =  0.125f*(2+GetFrame());	yf = 2*0.125; NextFrame(4);
								break;

		case STATE_JUMPLEFT:	xo = 0.125f*(GetFrame());	yo = 4*0.125f;
								xf =  0.125f*(1+GetFrame());	yf = 3*0.125; NextFrame(3);
								break;
		
		case STATE_JUMPRIGHT:	xf = 0.125f*(GetFrame());	 yo = 4*0.125f;
								xo =  0.125f*(1+GetFrame());	yf = 3*0.125; NextFrame(3);
								break;
		
		case STATE_LOOKLEFT:	xo = 0;	 yo = 3*0.125f;
								xf =  0.125f;	yf = 2*0.125; 
								break;
		
		case STATE_LOOKRIGHT:	xo = 0;	 yo = 3*0.125f;
								xf =  0.125f;	yf = 2*0.125; 
								break;
		case STATE_HIT:			xo=0.125*(life-1); xf=xo+0.125;
								yo=(GetFrame()+1)*0.125; yf = GetFrame()*0.125;
								NextFrame(2);
								break;
		case STATE_SNOWBALL:	xo=0.125*(life-1); xf=xo+0.125; yo=0.125; yf = 0;
								break;
        case STATE_STUNNED:	    xo = 0.125f*(GetFrame());	yo = 5*0.125f;
								xf =  0.125f*(1+GetFrame());	yf = 4*0.125; NextFrame(4);
								break;
	}
	DrawRect(tex_id,xo,yo,xf,yf);
}

void Enemy::GetTimecount(int* t){
	*t = timecount;
}

void Enemy::GetLife(int* l){
	*l = life;
}

bool Enemy::IsSnowball(){
	return GetState() == STATE_SNOWBALL;
}

void Enemy::Logic(int *map)
{	
	if(GetState() != STATE_HIT && GetState() != STATE_SNOWBALL && GetState() != STATE_STUNNED) {
		++movsps;
		if(movsps == 30) {
			movsps =0;
			rnd = rand()%100; 
		}
		if(rnd < 30) {
				MoveLeft(map);
			}
		else if(rnd<60) {
			MoveRight(map);
		}
		else if(rnd<90){
			SetState(STATE_LOOKLEFT);
		}
		else {
			Jump(map);
			rnd = rand()%100; 
		}
	}
	else {
		++timecount;
		if(GetState() == STATE_STUNNED) {
			if(timecount>=TIME_STUNNED) {
				timecount =0;
				SetState(STATE_LOOKLEFT);
			}
		}
		else if(timecount>=TIME_WITH_SNOW*life) {
			timecount =0;
			--life;
			SetState(STATE_HIT);
			if(life ==0) {
				SetState(STATE_STUNNED);
			}
		}
	}
	//else AI(map); <- este else no se de ke es else porque he cambado la condicion del if 
	cBicho::Logic(map);
}

void Enemy::AI(int *map){

}

bool Enemy::isHit() {
	return (GetState() == STATE_HIT || GetState() == STATE_SNOWBALL);
}

void Enemy::Hit() {
	++life;
	timecount =0;
	if(life>=TOTAL_HITS) {
		life =TOTAL_HITS;
		SetState(STATE_SNOWBALL);
	}
	else SetState(STATE_HIT);
}
