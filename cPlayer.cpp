
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::init() {
	SetWidthHeight(PLAYER_WIDTH,PLAYER_HEIGHT);
	//Player.SetWidthHeight(17,25);
	SetTile(INIT_PLAYER_X_TILE,INIT_PLAYER_Y_TILE);
	SetState(STATE_LOOKRIGHT);
	currentLives = PLAYER_MAX_LIVES;
	timecount =0;
	alfa = 1.0;
	lastThrow = -TIME_BETWEEN_PROJ;
	canThrow = true;
	incAlfa = 0.05;
}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;

	switch(GetState())
	{
		//1
		case STATE_LOOKLEFT:	//xo = 0.0f;	yo = 0.25f;
								xo = 0.0f;	yo = 0.0313f;
								break;
		//4
		case STATE_LOOKRIGHT:	//xo = 0.25f;	yo = 0.25f;
								xo = 0.0283f;	yo = 0.0313f;
								break;
		//1..3
		case STATE_WALKLEFT:	xo = 0.0f;	yo = 2*0.0313f + (GetFrame()*0.0313f);
								NextFrame(3);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo = 0.0283f; yo = 2*0.0313f + (GetFrame()*0.0313f);
								NextFrame(3);
								break;
		case STATE_JUMPLEFT:	xo = 2*0.0283f; yo = 0.0313f + (GetFrame()*0.0313f);
								NextFrame(4);
								break;
		case STATE_JUMPRIGHT:	xo = 3*0.0283f; yo = 0.0313f + (GetFrame()*0.0313f);
								NextFrame(4);
								break;
		case STATE_THROWRIGHT:	xo = 6*0.0283f; yo = 0.0313f + (GetFrame()*0.0313f);
								NextFrame(2);
								break;
		case STATE_THROWLEFT:	xo = 5*0.0283f; yo = 0.0313f + (GetFrame()*0.0313f);
								NextFrame(2);
								break;
		case STATE_DIE:			xo = 8*0.0283f; yo = 0.0313f + (GetFrame()*0.0313f);
								NextFrame(2);
								break;
	}

	if(isInvincible) {
		alfa-=incAlfa;
		if(alfa <= 0.0){
			alfa=0.0;
			incAlfa *=-1.0;
		}
		else if(alfa >= 1.0){
			alfa=1.0;
			incAlfa *=-1.0;
		}
		glColor4f(alfa,alfa,alfa,1.0);
	}
	else glColor4f(1.0,1.0,1.0,1.0);

	xf = xo + 0.0283f;
	yf = yo - 0.0313f;

	DrawRect(tex_id,xo,yo,xf,yf);
	glColor4f(1.0,1.0,1.0,1.0);
}

void cPlayer::Die() {
	currentLives--;
	isDead = true;
	SetState(STATE_DIE);
}

bool cPlayer::checkCanThrow() 
{
	if(canThrow) 
	{
		canThrow = false;
		lastThrow = glutGet(GLUT_ELAPSED_TIME);
		return true;
	}
	else
	{
		if (glutGet(GLUT_ELAPSED_TIME) > lastThrow + TIME_BETWEEN_PROJ)
		{
			canThrow = true;
		}
	}
	return false;
}

bool cPlayer::checkIfPlayerDead(int time) {
	if(isDead) {
		timecount+= time;
		if(timecount >= TIME_DEATH) {
			timecount =0;
			isDead = false;
			SetTile(INIT_PLAYER_X_TILE,INIT_PLAYER_Y_TILE);
			isInvincible=true;
			jumping= false;
			SetState(STATE_LOOKRIGHT);
			return false;
		}
		else return true;
	}
	return false;
}

bool cPlayer::checkIfPlayerInvincible(int time) {
	if(isInvincible) {
		timecount+= time;
		if(timecount >= TIME_INVINCIBLE) {
			timecount =0;
			isInvincible = false;
			return false;
		}
		else return true;
	}
	return false;
}

int cPlayer:: GetCurrentLives() {
	return currentLives;
}




