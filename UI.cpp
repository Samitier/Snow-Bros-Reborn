#include "UI.h"
#include "Globals.h"


UI::UI(void)
{
}


UI::~UI(void)
{
}

void UI::init() {
	points = 0;
	lives = 0;
	level =0;
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
}