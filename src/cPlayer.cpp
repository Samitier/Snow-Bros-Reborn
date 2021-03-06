
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::init() {
	SetWidthHeight(PLAYER_WIDTH,PLAYER_HEIGHT);
	SetTile(INIT_PLAYER_X_TILE,INIT_PLAYER_Y_TILE);
	projectiles = vector<cProjectile>();
	lives = PLAYER_MAX_LIVES;
	points = 0;
	timecount =0;
	alfa = 1.0;
	incAlfa = 0.1;
	dead = false;
	invincible = false;
	snowballPushing = -1;
	snowballOnTopOf = -1;
	blocks = vector<cBlock>();
	seq=0;
	delay=0;
	timeThrowing =0;
	state = STATE_LOOKLEFT;
}

void cPlayer::Draw(int tex_id, bool pause)
{	
	float xo,yo,xf,yf;

	switch(GetState())
	{
		//1
		case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.0625f;
								break;
		//4
		case STATE_LOOKRIGHT:	xo = 0.0f;	yo = 3*0.0625f;
								break;
		//1..3
		case STATE_WALKLEFT:	xo =  0.0625f+(GetFrame()*0.0625f);	yo = 0.0625f;
								if(!pause)NextFrame(2);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo =  0.0625f+(GetFrame()*0.0625f);	yo = 3*0.0625f;
								if(!pause)NextFrame(2);
								break;
		case STATE_JUMPLEFT:	xo = 9*0.0625f+(GetFrame()*0.0625f); yo = 0.0625f;
								if (seq < 7) if(!pause)NextFrame(8);
								break;
		case STATE_JUMPRIGHT:	xo = 9*0.0625f+(GetFrame()*0.0625f); yo = 3*0.0625f;//falta
								if (seq < 7) if(!pause)NextFrame(8);
								break;
		case STATE_THROWRIGHT:	xo = 6*0.0625f+(GetFrame()*0.0625f); yo = 3*0.0625f;//??
								if(!pause)NextFrame(2);
								break;
		case STATE_THROWLEFT:	xo = 6*0.0625f+(GetFrame()*0.0625f); yo = 0.0625f;//??
								if(!pause)NextFrame(2);
								break;
		case STATE_DIE:			xo = 2*0.0625f+(GetFrame()*0.0625f); yo = 2*0.0625f;
								if(!pause)NextFrame(9);
								break;
		case STATE_PUSH_LEFT:   xo = (GetFrame()*0.0625f); yo = 2*0.0625f;
								if(!pause)NextFrame(2);
								break;
		case STATE_PUSH_RIGHT:  xo = (GetFrame()*0.0625f); yo = 4*0.0625f;
								if(!pause)NextFrame(2);
								break;
		case STATE_SNOWBALL_PLAYER:	xo =0; yo = 0;  break;

		case STATE_RESPAWN:		 xo = 6*0.0625f+(GetFrame()*0.0625f); yo = 4*0.0625f;
								if(!pause)NextFrame(7);
								break;
		case STATE_WINING_LEVEL: xo =1-0.0625f; yo = 0.0625;  break;
	}
	xf = xo + 0.0625f;
	yf = yo - 0.0625f;
	if(invincible&&!pause) {
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
	for (int i = 0; i < int(blocks.size()); ++i) 
		blocks[i].Draw(tex_id);
	for (int i = 0; i < int(projectiles.size()); ++i) 
		projectiles[i].Draw(tex_id);
}

int cPlayer::GetCurrentPoints()
{
	return points; 
}

void cPlayer::lvlUp(int* map) {
	for (int i = 0; i < blocks.size(); ++i) {
		int xaux, yaux;
		blocks[i].GetPosition(&xaux, &yaux);
		if (map[((yaux/TILE_SIZE)*SCENE_WIDTH)+xaux/TILE_SIZE] == 10) {
			map[((yaux/TILE_SIZE)*SCENE_WIDTH)+xaux/TILE_SIZE] = 0;
		}
	}
	projectiles = vector<cProjectile>();
	blocks = vector<cBlock>();
	lives = 3;
}

void cPlayer::Die() {
	lives--;
	dead = true;
	SetState(STATE_DIE);
}

bool cPlayer::isDead() {
	return (dead || state == STATE_RESPAWN);
}

void cPlayer::PutBlock(int xx,int yy,int* map) {
	if (map[((yy/TILE_SIZE)*SCENE_WIDTH)+xx/TILE_SIZE] == 0 &&
		int(blocks.size()) < MAX_BLOCKS) {
		bool bb = true;
		for (int i = 0; i < int(blocks.size()); ++i)
		{
			int xaux, yaux;
			blocks[i].GetPosition(&xaux, &yaux);
			if ((xx/TILE_SIZE)*TILE_SIZE == xaux && 
				(yy/TILE_SIZE)*TILE_SIZE == yaux) {
				bb = false;
				break;
			}
		}
		if (bb) {
			cBlock b(xx,yy);
			blocks.push_back(b);
			map[((yy/TILE_SIZE)*SCENE_WIDTH)+xx/TILE_SIZE] = 10;
		}
	}
	else if (map[((yy/TILE_SIZE)*SCENE_WIDTH)+xx/TILE_SIZE] == 10) {
		map[((yy/TILE_SIZE)*SCENE_WIDTH)+xx/TILE_SIZE] = 0;
		for (int i = 0; i < blocks.size(); ++i) {
			int xaux, yaux;
			blocks[i].GetPosition(&xaux, &yaux);
			if ((xx/TILE_SIZE)*TILE_SIZE == xaux && 
				(yy/TILE_SIZE)*TILE_SIZE == yaux) {
					blocks.erase(blocks.begin() + i);
			}
		}
	}
}


bool cPlayer::isInvincible() {
	return invincible;
}

int cPlayer:: GetCurrentLives() {
	return lives;
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
			state = STATE_RESPAWN;
		}
	}
	else if(state == STATE_RESPAWN) {
		timecount++;
		if(timecount >= TIME_RESPAWN) {
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
	//PROJECTILES
	if (throwing)  {
		++timeThrowing;
		if (timeThrowing > TIME_THROWING) {
			timeThrowing = 0;
			throwing = false;
		}
		else if (timeThrowing == THROW_LOAD) {
			int aux = (state == STATE_THROWLEFT) ? 0 : 1;
			cProjectile p(x,y,w,h,aux,TYPE_1);
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

	//BLOCKS
	for (int i = 0; i < int(blocks.size()); ++i) 
	{
		blocks[i].Logic(map);
	}

	cBicho::Logic(map);
}

bool cPlayer::CollidesMapFloor (int *map) {
	if(snowballOnTopOf != -1) return true;
	else return cBicho::CollidesMapFloor(map);
}

int cPlayer::GetSnowballPushing() {
	return snowballPushing;
}

void cPlayer::SetSnowballPushing(int snowball) {
	snowballPushing = snowball;
}

int cPlayer::GetSnowballOnTopOf() {
	return snowballOnTopOf;
}

void cPlayer::SetSnowballOnTopOf(int snowball) {
	snowballOnTopOf = snowball;
}

void cPlayer::ResetPosition() {
	SetTile(INIT_PLAYER_X_TILE,INIT_PLAYER_Y_TILE);
	timecount =0;
	alfa = 1.0;
	incAlfa = 0.1;
	dead = false;
	invincible = false;
	snowballPushing = -1;
	snowballOnTopOf = -1;
	seq=0;
	delay=0;
	timeThrowing =0;
	state = STATE_LOOKLEFT;
}

void cPlayer::SetCurrentPoints(int pts) {
	points =pts;
}