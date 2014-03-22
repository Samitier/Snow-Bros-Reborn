#include "EnemyOne.h"


EnemyOne::EnemyOne(void)
{
	movsps = 0;
	rnd = rand()%100;
	timeThrowing = 0;
}

void EnemyOne::Draw(int tex_id) { 
	int s = state;
	Enemy::Draw(tex_id);
}

EnemyOne::~EnemyOne(void)
{
}

void EnemyOne::Logic(int* map) 
{
		//PROJECTILES
	if (throwing)  {
		++timeThrowing;
		if (timeThrowing > TIME_THROWING) {
			timeThrowing = 0;
			throwing = false;
		}
		else if (timeThrowing == THROW_LOAD) {
			int aux = (state == STATE_THROWLEFT) ? 0 : 1;
			cProjectile p(x,y,w,h,aux,TYPE_2);
			projectiles.push_back(p);
		}
	}

	for (int i = 0; i < int(projectiles.size()); ++i) 
	{
		projectiles[i].Logic(map);
		if (projectiles[i].CollidesMapFloor(map) ||
			projectiles[i].CollidesMapWall(map, false) ||
			projectiles[i].CollidesMapWall(map, true)) 
		projectiles.erase(projectiles.begin() + i);
	}
	Enemy::Logic(map);
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
	if (rand()%1000 < 50) Throw(map);
}