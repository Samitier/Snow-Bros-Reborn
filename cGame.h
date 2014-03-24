#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "Enemy.h"
#include "cData.h"
#include "cProjectile.h"
#include "UI.h"
#include "cObject.h"
#include "Globals.h"
using namespace std;


class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	void GameOver();

	bool LoadEnemies(int level);

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	bool ProcessMenu();
	bool ProcessPlaying();
	bool ProcessPause();
	//Output
	void Render();
	void RenderPlaying();

private:
	bool startGame();

	unsigned char keys[256];
	void  projectileInit();
	void KillEnemy(int index);
	cScene Scene;
	int state;
	UI ui;
	cPlayer Player;
	int numPlayers;
	cData Data;
	vector<Enemy> enemies;
	bool throwing;
	bool keyboard_enabled;
};
