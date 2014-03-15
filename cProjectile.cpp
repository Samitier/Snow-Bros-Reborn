#include "cProjectile.h"



cProjectile::cProjectile(cBicho b)
{
		
		int x, y, w, h, aux;
		b.GetPosition(&x,&y);
		b.GetWidthHeight(&w, &h);
		if (b.GetState() == STATE_THROWLEFT) 
		{
			aux = STATE_WALKLEFT;
			x -= 10; //15;
		}
		else 
		{
			aux = STATE_WALKRIGHT;
			x += w - 5;//w;
		}
		y += h/2 - 5;
		SetWidthHeight(15,10);
		SetPosition(x, y); 
		SetState(aux);
		falling_y = y;
		falling_alfa  = 80;
}


cProjectile::~cProjectile(void)
{
}

void cProjectile::Draw(int tex_id)
{	
	float xo,yo,xf,yf;

	switch(GetState())
	{
		case STATE_WALKLEFT :	xo = 0.0f;	yo = 0.0313f;
							break;
		case STATE_WALKRIGHT:	xo = 0.0283f;	yo = 0.0313f;
							break;
	}
	xf = xo + 0.0283f;
	yf = yo - 0.0313f;

	DrawRect(tex_id,xo,yo,xf,yf);
}


bool cProjectile::Logic(int *map)
{
	float alfa;
	int x, y;
	GetPosition(&x,&y);
	if (GetState() == STATE_WALKRIGHT) 
	{
		x += 5;
	}
	else 
	{
		x -= 5;
	}
	falling_alfa  += HIGHT_STEP;
	alfa = ((float)falling_alfa) * 0.017453f;
	y = falling_y - 195 + (int)( ((float)MAX_HEIGHT) * sin(alfa) );
	SetPosition(x,y);
	if (CollidesMapFloor(map)) return true;
	if (CollidesMapWall(map, false)) return true;
	if (CollidesMapWall(map, true)) return true;
	return false;
}