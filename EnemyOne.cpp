#include "EnemyOne.h"


EnemyOne::EnemyOne(void)
{
	movsps = 0;
	rnd = rand()%100;
	projectiles = vector<cProjectile>();
}

void EnemyOne::Draw(int tex_id) { 
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
	//PROJECTILES
	if (rand()%1000 < 500) {
		cProjectile p(x,y,w,h,STATE_THROWRIGHT);
		projectiles.push_back(p);

  	}

	for (int i = 0; i < int(projectiles.size()); ++i) 
	{
		if (projectiles[i].CollidesMapFloor(map)		||
			projectiles[i].CollidesMapWall(map, false)	||
			projectiles[i].CollidesMapWall(map, true))		projectiles.erase(projectiles.begin() + i);
	}
}