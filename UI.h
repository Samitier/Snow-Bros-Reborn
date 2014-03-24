#pragma once

#define DEFAULT_UI_HEIGHT 32

class UI
{
public:
	UI(void);
	~UI(void);

	void init(int pnt, int liv);
	void initMenu();

	void DrawPlaying(int lives, int points);
	void DrawMenu(int tex_id);
	void DrawPause(int tex_id);
	void stateUp();
	void stateDown();
	void setWidthHeight(int width, int height);
	void setLevel(int level);
	int getMenuState();

private:
	void NextFrame(int max);
	
	int width, height;
	int level;
	int id0;
	int menuState;
	int delay;
	int seq;
	void GenerateCallList();
	void render_string(void* font, const char* string);
};

