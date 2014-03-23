#include "EnemyOne.h"


EnemyOne::EnemyOne(void)
{
	movsps = 0;
	rnd = rand()%100;
	timeThrowing = 0;
}

void EnemyOne::Draw(int tex_id) {
	for (int i = 0; i < int(projectiles.size()); ++i) 
		projectiles[i].Draw(tex_id);
	float xo,yo,xf,yf;
	
	switch(state)
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
		case STATE_THROWLEFT:	xo = 14*0.0625f+(seq*0.0625f); yo = 3*0.0625f;
								xf = xo + 0.0625f;		yf = yo - 0.0625f; 
								NextFrame(1);
								break;
		case STATE_THROWRIGHT:	xo = 14*0.0625f+(seq*0.0625f); yo = 4*0.0625f;
								xf = xo + 0.0625f;		yf = yo - 0.0625f; 
								NextFrame(1);
								break;
		case STATE_SNOWBALL_MOVING:	xo=0.125*(life-1); xf=xo+0.125; yo=0.125; yf = 0;
								break;
		case STATE_SNOWBALL_PLAYER:	xo=0.125*(life-1); xf=xo+0.125; yo=0.125*2; yf = 0.125;
								break;
	}
	DrawRect(tex_id,xo,yo,xf,yf);
}

EnemyOne::~EnemyOne(void)
{
}

void EnemyOne::Logic(int* map) 
{
	//PROJECTILES
	if (throwing)  {
		++timeThrowing;
		if (timeThrowing > 25) {
			timeThrowing = 0;
			throwing = false;
		}
		else if (timeThrowing == 20) {
			int aux = (state == STATE_THROWLEFT) ? 0 : 1;
			cProjectile p(x,y,w,h,aux,TYPE_2);
			projectiles.push_back(p);
		}
	}

	for (int i = 0; i < int(projectiles.size()); ++i) 
	{
		projectiles[i].Logic(map);
		//Destroy condition
		if (projectiles[i].Destroy(map))
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
	else if (!throwing){
		if(rand()%1000 <= 5) {
			Jump(map);
		}
		if(rnd < 68) {
			MoveLeft(map);
		}
		else if (rnd > 42) {
			MoveRight(map);
		}
	}
	if (rand()%1000 < 18) Throw(map);
}