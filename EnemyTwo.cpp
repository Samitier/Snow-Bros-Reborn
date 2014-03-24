#include "EnemyTwo.h"


EnemyTwo::EnemyTwo(void)
{
	movsps = 0;
	rnd = rand()%100;
	timeThrowing = 0;
}

void EnemyTwo::Draw(int tex_id) {

	float xo,yo,xf,yf;
	
	switch(state)
	{
		case STATE_WALKLEFT:	xo = 0.0625f+(seq*0.0625f);
								yo = 16*0.0625f;
								xf =  xo + 0.0625f; 
								yf = yo - 0.0625f;
								NextFrame(3);
								break;

		case STATE_WALKRIGHT:	xf = 0.0625f+(seq*0.0625f);
								yo = 16*0.0625f;
								xo =  xf + 0.0625f; 
								yf = yo - 0.0625f;
								NextFrame(3);
								break;

		case STATE_JUMPLEFT:	xo = 4*0.0625f+(seq*0.0625f);
								yo = 16*0.0625f;
								xf =  xo + 0.0625f; 
								yf = yo - 0.0625f;
								if (seq < 2) NextFrame(3);
								break;
		
		case STATE_JUMPRIGHT:	xf = 4*0.0625f+(seq*0.0625f);;
								yo = 16*0.0625f;
								xo =  xf + 0.0625f; 
								yf = yo - 0.0625f;
								if (seq < 2)NextFrame(3);
								break;
		
		case STATE_LOOKLEFT:	xo = 3*0.0625f;
								yo = 16*0.0625f;
								xf =  xo + 0.0625f; 
								yf = yo - 0.0625f;
								break;
		
		case STATE_LOOKRIGHT:	xf = 3*0.0625f;
								yo = 16*0.0625f;
								xo =  xf + 0.0625f; 
								yf = yo - 0.0625f;
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

	}
	DrawRect(tex_id,xo,yo,xf,yf);
}

EnemyTwo::~EnemyTwo(void)
{
}

void EnemyTwo::Logic(int* map) 
{
	Enemy::Logic(map);
}

void EnemyTwo::AI(int *map)
{	
	++movsps;
	if(movsps == 60) {
		movsps =0;
		rnd = rand()%100; 
	}
	if(rand()%1000 <= 6 && !jumping) {
		Jump(map);
	}
	if(rnd < 50) {
		MoveLeft(map);
	}
	else if (rnd > 50) {
		MoveRight(map);
	}
}