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

void UI::init() {
	points = 0;
	lives = PLAYER_MAX_LIVES;
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
	glEndList();
}

void UI::Draw() {
	glCallList(id0);
	//pintar points lives i level
	glRasterPos2f(10,GAME_HEIGHT-height/2); 
	stringstream strs;
	strs << lives;
	string temp_str = strs.str();
	char* lvs = (char*) temp_str.c_str();
	render_string(GLUT_BITMAP_HELVETICA_10,lvs);
}

void UI::setLives(int l){
	lives =l;
}

void UI::render_string(void* font, const char* string)
{
	int i,len = strlen(string);
	for(i=0;i<len;i++)
		glutBitmapCharacter(font, string[i]);
}