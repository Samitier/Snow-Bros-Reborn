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
	level =1;
	width = GAME_WIDTH;
	height = DEFAULT_UI_HEIGHT;
	GenerateCallList();
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

void UI::Draw(int lives, int points) {
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