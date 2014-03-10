#pragma once

#define DEFAULT_UI_HEIGHT 32

class UI
{
public:
	UI(void);
	~UI(void);

	void init();
	void Draw();

	void setWidthHeight(int width, int height);
	void setPoints(int points);
	void setLives(int lives);
	void setLevel(int level);

private:
	int width, height;
	int lives;
	int points;
	int level;
	int id0;

	void GenerateCallList();
};

