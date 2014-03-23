#include "cObject.h"

cObject::cObject(void)
{
	seq=0;
	delay=0;
}
cObject::~cObject(void){}

cObject::cObject(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}
void cObject::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cObject::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cObject::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cObject::GetTile(int *tx,int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cObject::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cObject::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}

bool cObject::Collides(cRect *rc)
{
	return ! (
		(y+h< rc->bottom) ||
		(y > rc->top) ||
		(x > rc->right) ||
		(x+w < rc->left) );
	//return ((x >= rc->left) && (x+w <= rc->right) && (y >= rc->bottom) && (y+h <= rc->top));
}

bool cObject::CollidesMapWall(int *map,bool right)
{
	int tile_x,tile_y;
	int j;
	int width_tiles,height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles  = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if(right)	tile_x += width_tiles;
	
	for(j=0;j<height_tiles;j++)
	{
		if(map[ tile_x + ((tile_y+j)*SCENE_WIDTH) ] != 0)	return true;
	}
	
	return false;
}

bool cObject::CollidesMapFloor(int *map)
{
	if(y>=TILE_SIZE*SCENE_HEIGHT) return false;
	int tile_x,tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE;
	if( (x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i=0;
	while((i<width_tiles) && !on_base)
	{
		if( (y % TILE_SIZE) == 0 )
		{
			if(map[ (tile_x + i) + ((tile_y - 1) * SCENE_WIDTH) ] != 0)
				on_base = true;
		}
		else
		{
			if(map[ (tile_x + i) + (tile_y * SCENE_WIDTH) ] != 0)
			{
				y = (tile_y + 1) * TILE_SIZE;
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
}

void cObject::GetArea(cRect *rc)
{
	rc->left   = x;
	rc->right  = x+w;
	rc->bottom = y;
	rc->top    = y+h;
}
void cObject::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+w,screen_y);
		glTexCoord2f(xf,yf);	glVertex2i(screen_x+w,screen_y+h);
		glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y+h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cObject::Logic(int *map)
{
}

void cObject::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cObject::GetFrame()
{
	return seq;
}
int cObject::GetState()
{
	return state;
}
void cObject::SetState(int s)
{
	state = s;
	seq=0;
	delay=0;
}

int cObject::GetLeft() {
	return x;
}

int cObject::GetRight() {
	return x+w;
}

int cObject::GetTop() {
	return y+h;
}

int cObject::GetBottom() {
	return y;
}
