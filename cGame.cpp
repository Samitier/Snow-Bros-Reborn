#include "cGame.h"
#include "Globals.h"

cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.LoadImage(IMG_BLOCKS,"img/tileset.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BACKGROUND,"img/background.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);
	if(!res) return false;

	res = LoadEnemies(1);
	if(!res) return false;
	res = Data.LoadImage(IMG_ENEMY,"img/enemy.png",GL_RGBA);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"img/SnowBrosSheet.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(32,32);
	//Player.SetWidthHeight(17,25);
	Player.SetTile(4,5);
	Player.SetWidthHeight(32,32);
	Player.SetState(STATE_LOOKRIGHT);

	return res;
}

bool cGame::Loop()
{
	bool res=true;

	res = Process();
	if(res) Render();

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if (	keys[27])						res=false;
	if (	keys['c'] || keys['C'])			Player.Throw(Scene.GetMap());
	if (	keys['w'] || keys['W'])			Player.Jump(Scene.GetMap());
	if (	keys['a'] || keys['A'])			Player.MoveLeft(Scene.GetMap());
	else if(keys['d'] || keys['D'])			Player.MoveRight(Scene.GetMap());
	else 									Player.Stop();
	
	
	//Game Logic
	Player.Logic(Scene.GetMap());
	
	for(int i=0;i<enemies.size();++i) {
		enemies[i].Move(Scene.GetMap());
		enemies[i].Logic(Scene.GetMap());
	}
	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();

	Scene.Draw(Data.GetID(IMG_BLOCKS), Data.GetID(IMG_BACKGROUND));
	Player.Draw(Data.GetID(IMG_PLAYER));

	for(int i=0;i<enemies.size();++i) enemies[i].Draw(IMG_ENEMY);

	glutSwapBuffers();
}

bool cGame::LoadEnemies(int level) {

	bool res;
	FILE *fd;
	char file[16];
	char tile;

	res=true;

	if(level<10) sprintf(file,"%s0%d%s",(char *)"enemy",level,(char *)".txt");
	else		 sprintf(file,"%s%d%s",(char *)"enemy",level,(char *)".txt");

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	fscanf(fd,"%c",&tile);
	int numEnemies = tile-48;
	enemies = vector<Enemy>(numEnemies);

	fscanf(fd,"%c",&tile);
	int k =0;
	for(int i=SCENE_HEIGHT-1;i>=0;i--){
		for(int j=0; j<SCENE_WIDTH; ++j) {
			fscanf(fd,"%c",&tile);
			if(tile ==',') fscanf(fd,"%c",&tile);
			if(tile=='7') {
				Enemy en;
				en.init();
				en.SetWidthHeight(32,32);
				en.SetTile(j,i);
				en.SetState(STATE_LOOKRIGHT);
				enemies[k] = en;
				k++;
			}
		}
		fscanf(fd,"%c",&tile); //pass enter
	}
	fclose(fd);
	return res;
}
