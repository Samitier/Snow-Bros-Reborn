#include "cBlock.h"


cBlock::cBlock(void)
{}

cBlock::cBlock(int xx, int yy)
{
	x = (xx/TILE_SIZE)*TILE_SIZE;
	y = (yy/TILE_SIZE)*TILE_SIZE;
	w = TILE_SIZE;
	h = TILE_SIZE;
}

cBlock::~cBlock(void)
{}

void cBlock::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	xo =  0.0625f+(GetFrame()*0.0625f);	yo = 5*0.0625f;
	xf = xo + 0.0625f;					yf = yo - 0.0625f;
	if (seq < 3) NextFram(5);
	DrawRect(tex_id,xo,yo,xf,yf);
}

void cBlock::NextFram(int max)
{
	delay++;
	if(delay == 12)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
void cBlock::Logic(int* map) {
}
