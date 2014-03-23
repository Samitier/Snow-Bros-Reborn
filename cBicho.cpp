#include "cBicho.h"
#include "Globals.h"

cBicho::cBicho(void)
{
	throwing = false;
	state = STATE_LOOKLEFT;
	jumping = false;
	projectiles = vector<cProjectile>();
	jump_alfa = 0;
	jump_y = y;
}

cBicho::cBicho(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}


cBicho::~cBicho(void){}

bool cBicho::isJumping(){
	return jumping;
}

vector<cProjectile> cBicho::GetProjectiles() {
	return projectiles;
}

void cBicho::MoveLeft(int *map)
{
	int xaux;
	
	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if(CollidesMapWall(map,false))
		{
			x = xaux;
			if (!jumping) state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH;
		if(state != STATE_WALKLEFT)
		{
			if (!jumping && !throwing) 
			{
				state = STATE_WALKLEFT;
				seq = 0;
				delay = 0;
			}
			switch(state)
			{
				case STATE_THROWRIGHT:	state = STATE_THROWLEFT;	break;
				case STATE_JUMPRIGHT:	state = STATE_JUMPLEFT;	break;
			}
		}
	}
}

bool cBicho::PushLeft(int *map)
{
	int xaux;
	
	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if(CollidesMapWall(map,false))
		{
			x = xaux;
			return false;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH;
		return true;
	}
}
void cBicho::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH;

		if(CollidesMapWall(map,true))
		{
			x = xaux;
			if (!jumping) state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;

		if(state != STATE_WALKRIGHT)
		{
			if (!jumping && !throwing) 
			{
				state = STATE_WALKRIGHT;
				seq = 0;
				delay = 0;
			}
			switch(state)
			{
				case STATE_THROWLEFT:	state = STATE_THROWRIGHT;	break;
				case STATE_JUMPLEFT:	state = STATE_JUMPRIGHT;	break;
			}
		}
	}
}

bool cBicho::PushRight(int *map)
{
	int xaux;
	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH;

		if(CollidesMapWall(map,true))
		{
			x = xaux;
			return false;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;
		return true;
	}
}

void cBicho::Stop()
{
	switch(state)
	{
		case STATE_WALKLEFT:	
			state = STATE_LOOKLEFT;		break;
		case STATE_WALKRIGHT:	
			state = STATE_LOOKRIGHT;	break;		
	}

	if (!jumping) 
	{
		switch(state)
		{
			case STATE_JUMPLEFT:	
				state = STATE_LOOKLEFT;		break;
			case STATE_JUMPRIGHT:	
state = STATE_LOOKRIGHT;	break;
		}
	}
	if (!throwing)
	{
		switch(state)
		{
		case STATE_THROWLEFT:	
			state = STATE_LOOKLEFT;		break;
		case STATE_THROWRIGHT:	
			state = STATE_LOOKRIGHT;	break;
		}
	}
}
void cBicho::Jump(int *map)
{	
	if(!jumping && !throwing)
	{
		if(CollidesMapFloor(map))
		{
			switch(state)
			{
				case STATE_LOOKLEFT:
					state = STATE_JUMPLEFT;		break;
				case STATE_LOOKRIGHT:
					state = STATE_JUMPRIGHT;	break;
				case STATE_WALKLEFT:
					state = STATE_JUMPLEFT;		break;
				case STATE_WALKRIGHT:
					state = STATE_JUMPRIGHT;	break;
				case STATE_PUSH_LEFT:
					state = STATE_JUMPLEFT;		break;
				case STATE_PUSH_RIGHT:
					state = STATE_JUMPRIGHT;	break;
			}
			seq = 0;
			delay = 0;				 
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
		}
	}
}
void cBicho::EraseProjectile(int i){
	projectiles.erase(projectiles.begin()+i);
}

void cBicho::Throw(int *map)
{
	throwing = true;
	switch(state)
	{
		case STATE_LOOKLEFT:
			state = STATE_THROWLEFT;	break;
		case STATE_LOOKRIGHT:
			state = STATE_THROWRIGHT;	break;
		case STATE_WALKLEFT:
			state = STATE_THROWLEFT;	break;
		case STATE_WALKRIGHT:
			state = STATE_THROWRIGHT;	break;
		case STATE_JUMPLEFT:
			state = STATE_THROWLEFT;	break;
		case STATE_JUMPRIGHT:
			state = STATE_THROWRIGHT;	break;
	}
}

void cBicho::Logic(int *map)
{
	float alfa;

	if(jumping)
	{
		jump_alfa += JUMP_STEP;
		if(jump_alfa == 180)
		{
			jumping = false;
			y = jump_y;

		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)( ((float)JUMP_HEIGHT) * sin(alfa) );
		
			if(jump_alfa > 90)
			{
				//Over floor?
				jumping = !CollidesMapFloor(map);
			}
		}
	}
	else
	{
		//Over floor?
		if(!CollidesMapFloor(map))
			y -= (2*STEP_LENGTH);
	}


}