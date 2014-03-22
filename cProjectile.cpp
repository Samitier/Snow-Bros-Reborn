#include "cProjectile.h"



cProjectile::cProjectile(int xx, int yy, int ww, int hh, int dir,int typee)
{
		if (dir == 1) {
			x = xx + ww - 5;
			state = STATE_GO_RIGHT;
		}
		else {
			x = xx +10;
			state = STATE_GO_LEFT;
		}
		y = yy + hh/2 - 5;
		type = typee;
		w = 20;
		h = 20;
		falling_y = yy + hh/2 -5;
		falling_alfa  = 80;
		timeAlive = 0;
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
				case STATE_GO_LEFT  : xo = 0.1250f;	yo = 6*0.1250f;
									break;
				case STATE_GO_RIGHT : xo = 0.1250f;	yo = 7*0.1250f;;
									break;
			}
			xf = xo + 0.1250f;
			yf = yo - 0.1250f;
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
			else x -= 10;
			falling_alfa  += HIGHT_STEP;
			alfa = ((float)falling_alfa) * 0.017453f;
			y = falling_y - 195 + (int)( ((float)MAX_HEIGHT) * sin(alfa) );
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
			return (CollidesMapFloor(map) ||
			CollidesMapWall(map, false) ||
			CollidesMapWall(map, true));
		break;

		case TYPE_2 :
			return (timeAlive == 50);
		break;
	}
	return false;
}