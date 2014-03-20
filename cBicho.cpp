#include "cBicho.h"
#include "Globals.h"

cBicho::cBicho(void)
{
	seq=0;
	delay=0;
	jumping = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}
void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cBicho::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}

bool cBicho::Collides(cRect *rc)
{
	return ! (
		(y+h< rc->bottom) ||
		(y > rc->top) ||
		(x > rc->right) ||
		(x+w < rc->left) );
	//return ((x >= rc->left) && (x+w <= rc->right) && (y >= rc->bottom) && (y+h <= rc->top));
}

bool cBicho::CollidesMapWall(int *map,bool right)
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

bool cBicho::CollidesMapFloor(int *map)
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

void cBicho::GetArea(cRect *rc)
{
	rc->left   = x;
	rc->right  = x+w;
	rc->bottom = y;
	rc->top    = y+h;
}
void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
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
void cBicho::Stop()
{
	switch(state)
	{
		case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
		case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
	}
	if (!jumping) 
	{
		switch(state)
		{
			case STATE_JUMPLEFT:	state = STATE_LOOKLEFT;		break;
			case STATE_JUMPRIGHT:	state = STATE_LOOKRIGHT;	break;
		}
	}
	if (!throwing) 
	{
		switch(state)
		{
			case STATE_THROWLEFT:	state = STATE_LOOKLEFT;		break;
			case STATE_THROWRIGHT:	state = STATE_LOOKRIGHT;	break;
		}
	}


}
void cBicho::Jump(int *map)
{
	if(!jumping)
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
	//PROGRAMAR LANZAMIENTO
	if (throwing)  throwing = false;
}
void cBicho::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cBicho::GetFrame()
{
	return seq;
}
int cBicho::GetState()
{
	return state;
}
void cBicho::SetState(int s)
{
	state = s;
}

int cBicho::GetLeft() {
	return x;
}

int cBicho::GetRight() {
	return x+w;
}

int cBicho::GetTop() {
	return y+h;
}

int cBicho::GetBottom() {
	return y;
}
