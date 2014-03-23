#include "Enemy.h"
#include <stdlib.h> 

Enemy::Enemy(void) { 
}

Enemy::~Enemy(){}

void Enemy::init() {
	movsps =0;
	rnd = rand()%100; 
	life = 0;
	state = STATE_LOOKLEFT;
	timecount =0;
}


void Enemy::Draw(int tex_id)
{	
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
	if(state != STATE_HIT && state != STATE_SNOWBALL && state != STATE_STUNNED) {
		AI(map); 
	}
	else {
		++timecount;
		if(state == STATE_STUNNED) {
			if(timecount>=TIME_STUNNED) {
				timecount =0;
				state = STATE_LOOKLEFT;
			}
		}
		else if(timecount>=TIME_WITH_SNOW*life) {
			timecount =0;
			--life;
			state = STATE_HIT;
			if(life ==0) {
				state = STATE_STUNNED;
			}
		}
	}
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

void Enemy::GetArea(cRect *rc)
{
	if(state != STATE_SNOWBALL) {
		rc->left   = x;
		rc->right  = x+w;
		rc->bottom = y;
		rc->top    = y+h;
	}
	else {
		rc->left   = x+SNOWBALL_LIMIT;
		rc->right  = x+w-SNOWBALL_LIMIT;
		rc->bottom = y;
		rc->top    = y+h;
	}
}