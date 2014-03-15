#include "cProjectile.h"



cProjectile::cProjectile(void)
{
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
	/*float alfa;
	alfa = ((float)falling_alfa) * 0.017453f;
	y = falling_y + (int)( ((float)JUMP_HEIGHT) * sin(alfa) );*/
}