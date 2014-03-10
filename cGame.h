#pragma once

#include <vector>
#include "cScene.h"
#include "cPlayer.h"
#include "Enemy.h"
#include "cData.h"
#include "UI.h"

using namespace std;


class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	bool LoadEnemies(int level);

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	cScene Scene;
	UI ui;
	cPlayer Player;
	cData Data;
	vector<Enemy> enemies;
};
