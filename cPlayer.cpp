
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::init() {
	SetWidthHeight(PLAYER_WIDTH,PLAYER_HEIGHT);
	//Player.SetWidthHeight(17,25);
	SetTile(INIT_PLAYER_X_TILE,INIT_PLAYER_Y_TILE);
	SetState(STATE_LOOKRIGHT);
	lives = PLAYER_MAX_LIVES;
	points = 0;
	timecount =0;
	alfa = 1.0;
	incAlfa = 0.1;
	dead = false;
	invincible = false;
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
	xf = xo + 0.0283f;
	yf = yo - 0.0313f;
	if(invincible) {
		alfa-=incAlfa;
		if(alfa <= 0){
			alfa=0;
			incAlfa *=-1.0;
		}
		else if(alfa >= 1.0){
			alfa=1.0;
			incAlfa *=-1.0;
		}
		glColor4f(1.0,1.0,1.0,alfa);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		DrawRect(tex_id,xo,yo,xf,yf);
		glDisable(GL_BLEND);
		glColor4f(1.0,1.0,1.0,1.0);
	}
	else {
		DrawRect(tex_id,xo,yo,xf,yf);
	}
}

void cPlayer::GetCurrentPoints(int* p)
{
	*p = points; 
}

void cPlayer::Die() {
	lives--;
	dead = true;
	SetState(STATE_DIE);
}

bool cPlayer::isDead() {
	return dead;
}

bool cPlayer::isInvincible() {
	return invincible;
}

void cPlayer:: GetCurrentLives(int* l) {
	*l = lives;
}

void cPlayer::Logic(int *map) {
	if(dead) {
		timecount++;
		if(timecount >= TIME_DEATH) {
			timecount =0;
			dead = false;
			SetTile(INIT_PLAYER_X_TILE,INIT_PLAYER_Y_TILE);
			invincible=true;
			jumping= false;
			SetState(STATE_LOOKRIGHT);
		}
	}
	else if (invincible) {
		timecount++;
		if(timecount >= TIME_INVINCIBLE) {
			timecount =0;
			alfa = 1.0;
			invincible = false;
		}
	}
	cBicho::Logic(map);
}



