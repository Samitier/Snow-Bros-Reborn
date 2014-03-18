#pragma once

#define DEFAULT_UI_HEIGHT 32

class UI
{
public:
	UI(void);
	~UI(void);

	void init(int pnt, int liv);
	void Draw(int lives, int points);

	void setWidthHeight(int width, int height);
	void setLevel(int level);

private:
	int width, height;
	

	int level;
	int id0;

	void GenerateCallList();
	void render_string(void* font, const char* string);
};

