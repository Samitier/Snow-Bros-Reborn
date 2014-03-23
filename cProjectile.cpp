#include "cProjectile.h"



cProjectile::cProjectile(int xx, int yy, int ww, int hh, int dir,int typee)
{
	switch(typee) {
	case TYPE_1:
		if (dir == 1) {
			x = xx;
			state = STATE_GO_RIGHT;
		}
		else {
			x = xx;
			state = STATE_GO_LEFT;
		}
		y = yy + hh/2 - 5;
		type = typee;
		w = 16;
		h = 16;

		delay = 0;
		falling_y = yy + hh/2 -5;
		falling_alfa  = 80;
		timeAlive = 0;
		xor = xx;
		yor = yy+ww-10;
		break;
	case TYPE_2:
		if (dir == 1) {
			x = xx;
			state = STATE_GO_RIGHT;
		}
		else {
			x = xx;
			state = STATE_GO_LEFT;
		}
		y = yy;
		type = typee;
		w = 32;
		h = 32;
		delay = 0;
		falling_y = yy + hh/2 -5;
		falling_alfa  = 80;
		timeAlive = 0;
		xor = xx;
		yor = yy;
		break;
	}
}


cProjectile::~cProjectile(void)
{
}

void cProjectile::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	switch(type)
	{
		case TYPE_1 :
			switch(state)
			{
				case STATE_GO_LEFT  : xo = 5*0.0625f;	yo = 4*0.0625f;
									break;
				case STATE_GO_RIGHT : xo = 4*0.0625f;	yo = 4*0.0625f;;
									break;
			}
			xf = xo + 0.0625f;
			yf = yo - 0.0625f;
		break;

		case TYPE_2 :
			switch(state)
			{
				case STATE_GO_LEFT  :
					xo = 13*0.0625f+(seq*0.0625f);
					yo = 0.0625f;
					if (seq < 2) NextFrame(3);
				break;
				case STATE_GO_RIGHT : 
					xo = 13*0.0625f+(seq*0.0625f);
					yo = 2*0.0625f;
					if (seq < 2) NextFrame(3);
				break;
			}
			xf = xo + 0.0625f;
			yf = yo - 0.0625f;
		break;
	}
	DrawRect(tex_id,xo,yo,xf,yf);
}


void cProjectile::Logic(int *map)
{
	switch(type)
	{
		case TYPE_1 :
			float alfa;
			if (state== STATE_GO_RIGHT) x += 10;
			else x -= 10 ;
			falling_alfa  += HIGHT_STEP;
			alfa = ((float)falling_alfa) * 0.017453f;
			y = falling_y - 195 + (int)( ((float)MAX_HEIGHT) * sin(alfa) );
			//if (abs(x -xor) > 13) y = int(-1*pow(double((x-xor)/8),2)+yor);
		break;

		case TYPE_2 :
			if (state== STATE_GO_RIGHT) x += 3;
			else x -= 3;
		break;
	}
	++timeAlive;
}

bool cProjectile::Destroy(int* map)
{
	switch(type)
	{
		case TYPE_1 :
			return (CollidesMapFloor(map)	||
			CollidesMapWall(map, false)		||
			CollidesMapWall(map, true));
		break;

		case TYPE_2 :
			return (timeAlive == 50				|| 
					CollidesMapWall(map, false) ||
					CollidesMapWall(map, true));
		break;
	}
	return false;
}