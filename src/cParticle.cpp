#include "cParticle.h"

cParticle::cParticle(void)
{
	seq=0;
	delay=0;
	alfa =1.0;
}

cParticle::~cParticle(void){}

cParticle::cParticle(int posx,int posy)
{
	x = posx+ENEMY_WIDTH/2 - PARTICLE_SIZE/2;
	y = posy+ENEMY_HEIGHT/2 - PARTICLE_SIZE/2;
	seq=0;
	delay=0;
	alfa =1.0;
}

void cParticle:: Draw(int tex_id, bool pause) {
	float xo, yo, xf, yf;
	if(GetFrame() < 4) {
		xo =0.25*GetFrame();
		yo=0;
	}
	else if(GetFrame()<6){
		xo = 0.25*(GetFrame()-4);
		yo = 0.25;
	}
	else {
		xo=0.25;
		yo=0.25;
		if(!pause) {
			alfa -=0.09;
			glColor4f(1.0,1.0,1.0,alfa);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}
	xf=xo+0.25;
 	yf=yo+0.25;
	if(!pause)NextFrame(12);
	DrawRect(tex_id, xo,yo,xf,yf);
	glDisable(GL_BLEND);
	glColor4f(1.0,1.0,1.0,1.0);
}

void cParticle::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY+1)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cParticle::GetFrame()
{
	return seq;
}

void cParticle::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+PARTICLE_SIZE,screen_y);
		glTexCoord2f(xf,yf);	glVertex2i(screen_x+PARTICLE_SIZE,screen_y+PARTICLE_SIZE);
		glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y+PARTICLE_SIZE);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

bool cParticle::Dead() {
	return (GetFrame()>=11);
}