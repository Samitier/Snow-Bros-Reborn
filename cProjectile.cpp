#include "cProjectile.h"



cProjectile::cProjectile(cBicho b)
{
		
		int x, y;
		int *ax, *ay;
		ax = &x;
		ay = &y;
		b.GetPosition(ax,ay);
		SetWidthHeight(15,10);
		SetPosition(*ax,*ay);
		SetWidthHeight(15,10);
		int aux = (b.GetState() == STATE_THROWLEFT)
			? aux = STATE_WALKLEFT 
			: aux = STATE_WALKRIGHT;
		SetState(aux);
		falling_y = *ay;
		falling_alfa  = 0;
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

void cProjectile::Move(int *map)
{
	if (GetState() == STATE_WALKRIGHT) MoveRight(map);
	else MoveLeft(map);

}

void cProjectile::Logic(int *map)
{
	float alfa;
	int auxx, auxy;
	int *x = &auxx;
	int *y = &auxy;
	GetPosition(x, y);
	falling_alfa += 6; //
	if(falling_alfa == 180) *y = falling_y;
	else
	{
		alfa = ((float)falling_alfa) * 0.017453f;
		*y = falling_y + (int)( ((float)96) * sin(alfa) );//
		if(falling_alfa > 90)
		{
			//Over floor?
			if(CollidesMapFloor(map)) 
			{

			}
		}
	}
	alfa = ((float)falling_alfa) * 0.017453f;
	SetPosition(*x,*y);
}