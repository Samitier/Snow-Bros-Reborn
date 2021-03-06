#include "UI.h"
#include "Globals.h"
#include<string>
#include <sstream>
using namespace std;

UI::UI(void)
{
}


UI::~UI(void)
{
}

void UI::init(int pnt, int liv) {
	pnt = 0;
	liv = PLAYER_MAX_LIVES;
	width = GAME_WIDTH;
	height = DEFAULT_UI_HEIGHT;
	GenerateCallList();
	delay = 0;
	seq = 0;
}

void UI::initMenu() {
	menuState = 0;
}

void UI::GenerateCallList() {
	id0=glGenLists(1);
	glNewList(id0,GL_COMPILE);
		glColor4f(0,0,0,1);
		glBegin(GL_QUADS);
			glVertex2i(0, GAME_HEIGHT);
			glVertex2i(0, GAME_HEIGHT-height);
			glVertex2i(width,GAME_HEIGHT-height);
			glVertex2i(width,GAME_HEIGHT);
		glEnd();
		glColor4f(1,1,1,1);
		char *text[] = {"LIVES", "POINTS", "LEVEL"};
		for(int i=0; i<3;++i) {
			glRasterPos2f(5+(GAME_WIDTH/3)*i,GAME_HEIGHT-20); 
			render_string(GLUT_BITMAP_HELVETICA_10,text[i]);
		}
	glEndList();
}

void UI::NextFrame(int max)
{
	delay++;
	if(delay == 17)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
void UI::stateDown(int max) {
	++menuState;
	if (menuState > max) menuState = 0;
}

void UI::stateUp(int max) {
	--menuState;
	if (menuState < 0) menuState = max;
}

int UI::getMenuState() {
	return menuState;
}

void UI::DrawMenu(int tex_id) {
		float xo, yo, xf, yf;

	switch(menuState) {
		case 0:
			xo = seq*0.25f;	yo = 0.25f;
			NextFrame(2);
		break;
		case 1:
			xo = seq*0.25f;	yo = 2*0.25f;
			NextFrame(2);
		break;
		case 2:
			xo = seq*0.25f;	yo = 3*0.25f;
			NextFrame(2);
		break;
		case 3:
			xo = 2*0.25f+seq*0.25f;	yo = 2*0.25f;
			NextFrame(2);
		break;
	}
	xf = xo + 0.25f;	yf = yo - 0.25f;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(0  ,0);
		glTexCoord2f(xf,yo);	glVertex2i(GAME_WIDTH,0);
		glTexCoord2f(xf,yf);	glVertex2i(GAME_WIDTH,GAME_HEIGHT);
		glTexCoord2f(xo,yf);	glVertex2i(0  ,GAME_HEIGHT);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void UI::DrawPause(int tex_id) {
	float xo, yo, xf, yf;
	xo = seq*0.25f;		yo = 4*0.25f;
	NextFrame(2);
	xf = xo + 0.25f;	yf = yo - 0.25f;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(0  ,0);
		glTexCoord2f(xf,yo);	glVertex2i(GAME_WIDTH,0);
		glTexCoord2f(xf,yf);	glVertex2i(GAME_WIDTH,GAME_HEIGHT);
		glTexCoord2f(xo,yf);	glVertex2i(0  ,GAME_HEIGHT);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void UI::DrawCredits(int tex_id) {
	float xo, yo, xf, yf;
	xo = 0.75f;		yo = 0.25f;
	xf = xo + 0.25f;	yf = yo - 0.25f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(0  ,0);
		glTexCoord2f(xf,yo);	glVertex2i(GAME_WIDTH,0);
		glTexCoord2f(xf,yf);	glVertex2i(GAME_WIDTH,GAME_HEIGHT);
		glTexCoord2f(xo,yf);	glVertex2i(0  ,GAME_HEIGHT);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}



void UI::DrawInstructions(int tex_id) {
	float xo, yo, xf, yf;
	xo = 0.50f;		yo = 0.25f;
	xf = xo + 0.25f;	yf = yo - 0.25f;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(0  ,0);
		glTexCoord2f(xf,yo);	glVertex2i(GAME_WIDTH,0);
		glTexCoord2f(xf,yf);	glVertex2i(GAME_WIDTH,GAME_HEIGHT);
		glTexCoord2f(xo,yf);	glVertex2i(0  ,GAME_HEIGHT);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void UI::DrawGameEnd(int tex_id,int liv, int score,int lvl) {
	DrawCredits(tex_id);
	DrawPlaying(liv,score,lvl);
}

void UI::DrawPlaying(int lives, int points, int level) {
	glCallList(id0);
	//pintar points lives i level
	stringstream strs;
	
	//char s[32];
	//sprintf(s,"vida %d %.2f",points,time);

	strs << lives;
	string temp_str = strs.str();
	char* lvs = (char*) temp_str.c_str();
	glRasterPos2f(GAME_WIDTH/6,GAME_HEIGHT-20); 
	render_string(GLUT_BITMAP_HELVETICA_10,lvs);
	strs.str("");
	strs << points;
	temp_str = strs.str();
	lvs = (char*) temp_str.c_str();
	glRasterPos2f(3*(GAME_WIDTH/6),GAME_HEIGHT-20); 
	render_string(GLUT_BITMAP_HELVETICA_10,lvs);
	strs.str("");
	strs << level;
	temp_str = strs.str();
	lvs = (char*) temp_str.c_str();
	glRasterPos2f(5*(GAME_WIDTH/6),GAME_HEIGHT-20); 
	render_string(GLUT_BITMAP_HELVETICA_10,lvs);
}


void UI::render_string(void* font, const char* string)
{
	int i,len = strlen(string);
	for(i=0;i<len;i++)
		glutBitmapCharacter(font, string[i]);
}
void UI::resetMenuState() {
	menuState = 0;
}
void UI::DrawGameOver(int tex_id) {
	float xo, yo, xf, yf;
	switch(menuState) {
		case 0:
			xo = 0.50f+seq*0.25f;	yo = 0.75f;
			NextFrame(2);
		break;
		case 1:
			xo = 0.50f+seq*0.25f;	yo = 1.0f;
			NextFrame(2);
		break;
	}
	xf = xo + 0.25f;	yf = yo - 0.25f;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(0  ,0);
		glTexCoord2f(xf,yo);	glVertex2i(GAME_WIDTH,0);
		glTexCoord2f(xf,yf);	glVertex2i(GAME_WIDTH,GAME_HEIGHT);
		glTexCoord2f(xo,yf);	glVertex2i(0  ,GAME_HEIGHT);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
