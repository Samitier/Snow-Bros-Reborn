
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::init() {
	SetWidthHeight(PLAYER_WIDTH,PLAYER_HEIGHT);
	//Player.SetWidthHeight(17,25);
	SetTile(INIT_PLAYER_X_TILE,INIT_PLAYER_Y_TILE);
	SetState(STATE_LOOKRIGHT);
	currentLives = PLAYER_MAX_LIVES;
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
	}
	xf = xo + 0.0283f;
	yf = yo - 0.0313f;

	DrawRect(tex_id,xo,yo,xf,yf);
}

void cPlayer::Die() {
	currentLives--;
	isDead = true;
	//Play the death animation
}

bool cPlayer::checkIfPlayerDead() {
	if(isDead) {
		//We have to check the time the player have been dead. If the time is > than a MAX_TIME_DEATH, 
		//then play the regeneration animation (if currentLives >0) & set the player x, y in the init position of the map
	}
	return false;
}

int cPlayer:: GetCurrentLives() {
	return currentLives;
}




