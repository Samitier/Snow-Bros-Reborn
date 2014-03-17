#include "Enemy.h"
#include <stdlib.h> 
Enemy::Enemy() { 
}

Enemy::~Enemy(){}

void Enemy::init() {
	hit = false;
	isSnowball = false;
	life = 0;
	timecount =0;
}

void Enemy::GetTimecount(int* t){
	*t = timecount;
}

void Enemy::GetLife(int* l){
	*l = life;
}

void Enemy::IsSnowball(bool* b){
	*b = isSnowball;
}

void Enemy::Logic(int *map)
{	
	if(isHit()) {
		++timecount;
		if(timecount>=TIME_WITH_SNOW*life) {
			timecount =0;
			--life;
			isSnowball = false;
			if(life ==0) hit = false;
		}
	}
	else AI(map);
	cBicho::Logic(map);
}

void Enemy::AI(int *map){

}

void Enemy::Draw(int tex_id){
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
