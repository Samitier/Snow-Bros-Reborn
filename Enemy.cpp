#include "Enemy.h"
#include <stdlib.h> 

Enemy::Enemy(int type) { 
	enemyType = type;
}

Enemy::~Enemy(){}

void Enemy::init() {
	movsps =0;
	rnd = rand()%100; 
	life = 0;
	timeThrowing = 0;
	SetWidthHeight(ENEMY_WIDTH, ENEMY_HEIGHT);
	state = STATE_LOOKRIGHT;
	timecount =0;
	direction =0;
}


void Enemy::Draw(int tex_id, bool pause)
{	
	float xo,yo,xf,yf;
	
switch(state)
	{
		case STATE_WALKLEFT:	xo = 0.125f*(1+GetFrame());	yo = 3*0.125f;
								xf =  0.125f*(2+GetFrame());	yf = 2*0.125; if(!pause)NextFrame(4);
								break;

		case STATE_WALKRIGHT:	xf = 0.125f*(1+GetFrame());	yo = 3*0.125f;
								xo =  0.125f*(2+GetFrame());	yf = 2*0.125; if(!pause)NextFrame(4);
								break;

		case STATE_JUMPLEFT:	xo = 0.125f*(GetFrame());	yo = 4*0.125f;
								xf =  0.125f*(1+GetFrame());	yf = 3*0.125; if(!pause)NextFrame(3);
								break;
		
		case STATE_JUMPRIGHT:	xf = 0.125f*(GetFrame());	 yo = 4*0.125f;
								xo =  0.125f*(1+GetFrame());	yf = 3*0.125; if(!pause)NextFrame(3);
								break;
		
		case STATE_LOOKLEFT:	xo = 0;	 yo = 3*0.125f;
								xf =  0.125f;	yf = 2*0.125; 
								break;
		
		case STATE_LOOKRIGHT:	xo = 0;	 yo = 3*0.125f;
								xf =  0.125f;	yf = 2*0.125; 
								break;
		case STATE_HIT:			xo=0.125*(life-1); xf=xo+0.125;
								yo=(GetFrame()+1)*0.125; yf = GetFrame()*0.125;
								if(!pause) NextFrame(2);
								break;
		case STATE_SNOWBALL:	xo=0.125*(life-1); xf=xo+0.125; yo=0.125; yf = 0;
								break;
        case STATE_STUNNED:	    xo = 0.125f*(GetFrame());	yo = 5*0.125f;
								xf =  0.125f*(1+GetFrame());	yf = 4*0.125; if(!pause) NextFrame(4);
								break;
		case STATE_THROWLEFT:	xo = 14*0.0625f+(seq*0.0625f); yo = 3*0.0625f;
								xf = xo + 0.0625f;		yf = yo - 0.0625f; 
								if(!pause) NextFrame(1);
								break;
		case STATE_THROWRIGHT:	xo = 14*0.0625f+(seq*0.0625f); yo = 4*0.0625f;
								xf = xo + 0.0625f;		yf = yo - 0.0625f; 
								if(!pause) NextFrame(1);
								break;
		case STATE_SNOWBALL_MOVING:	xo=0.125*(life-1); xf=xo+0.125; yo=0.125; yf = 0;
								break;
		case STATE_SNOWBALL_PLAYER:	xo=0.125*(life-1); xf=xo+0.125; yo=0.125*2; yf = 0.125;
								break;
	}

	if(enemyType==ENEMY_ONE) {
		for (int i = 0; i < int(projectiles.size()); ++i) 
		projectiles[i].Draw(tex_id);
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
	if(enemyType == ENEMY_ONE) {
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
	}
	if(state != STATE_HIT && state != STATE_SNOWBALL && state != STATE_STUNNED && state != STATE_SNOWBALL_MOVING && state != STATE_SNOWBALL_PLAYER) {
		AI(map); 
	}
	else if(state != STATE_SNOWBALL_MOVING && state != STATE_SNOWBALL_PLAYER){
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
	else {
		if( (x % TILE_SIZE) == 0) {
			x += (STEP_LENGTH*direction);
			if(CollidesMapWall(map,(direction ==1))) {
				direction *=-1;
			}
		}
		else x += STEP_LENGTH*direction;
	}

	cBicho::Logic(map);
}

void Enemy::AI(int *map){
	switch(enemyType) {
		case ENEMY_ONE:
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
			break;

		case ENEMY_TWO:
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
			break;
	}
}

bool Enemy::isHit() {
	return (GetState() == STATE_HIT || GetState() == STATE_SNOWBALL|| GetState()==STATE_SNOWBALL_MOVING||GetState()==STATE_SNOWBALL_PLAYER);
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
	if(state != STATE_SNOWBALL && state != STATE_SNOWBALL_MOVING) {
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

void Enemy:: ShootSnowballLeft(){
	SetState(STATE_SNOWBALL_MOVING);
	direction = -1;
}
void Enemy::ShootSnowballRight(){
	SetState(STATE_SNOWBALL_MOVING);
	direction =1;
}
int Enemy::getType(){
	return enemyType;
}

int Enemy::getDirection(){
	return direction;
}

void Enemy::SetDirection(int dir) {
	direction = dir;
}

