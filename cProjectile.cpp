#include "cProjectile.h"



cProjectile::cProjectile(int xx, int yy, int ww, int hh, int statee)
{
		if (statee == STATE_THROWRIGHT) x = xx + ww - 5;
		else x = xx +10;
		y = yy + hh - 5;;
		w = 20;
		h = 20;
		state = statee;
		falling_y = yy;
		falling_alfa  = 80;
}


cProjectile::~cProjectile(void)
{
}

void cProjectile::Draw(int tex_id)
{	
	float xo,yo,xf,yf;

	switch(state)
	{
		case STATE_THROWLEFT  : xo = 5*0.0625f;	yo = 4*0.0625f;
							break;
		case STATE_THROWRIGHT :	xo = 4*0.0625f;	yo = 4*0.0625f;;
							break;
	}
	xf = xo + 0.0625f;
	yf = yo - 0.0625f;

	DrawRect(tex_id,xo,yo,xf,yf);
}


void cProjectile::Logic(int *map)
{
	float alfa;
	int x, y;
	GetPosition(&x,&y);
	if (GetState() == STATE_THROWRIGHT) x += 10;
	else x -= 10;
	falling_alfa  += HIGHT_STEP;
	alfa = ((float)falling_alfa) * 0.017453f;
	y = falling_y - 195 + (int)( ((float)MAX_HEIGHT) * sin(alfa) );
	SetPosition(x,y);
}