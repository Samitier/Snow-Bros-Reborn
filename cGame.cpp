#include "cGame.h"

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
	res = Data.LoadImage(IMG_PLAYER,"img/player.png",GL_RGBA);
	if(!res) return false;
	Player.init();
	int pnt;
	int liv;
	Player.GetCurrentPoints (&pnt);
	Player.GetCurrentLives (&liv);
	ui.init(pnt,liv);
	throwing = false;
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

	if(!Player.isDead()) { //if the player is dead we will not do anything until it revives
		//INPUT
		//ESC
		if (keys[27]) res=false; 

		//SPACEBAR
		if (keys[' '] && !throwing && Player.GetState()!=STATE_SNOWBALL_PLAYER)  {
			throwing = true;
			if(Player.GetState() == STATE_PUSH_LEFT) {
				enemies[Player.GetSnowballPushing()].ShootSnowballLeft(); 
			}
			else if(Player.GetState() == STATE_PUSH_RIGHT){
				enemies[Player.GetSnowballPushing()].ShootSnowballRight(); 
			}
			else Player.Throw(Scene.GetMap());	
		}
		else if(!keys[' ']) throwing = false;
		
		//W
		if (keys['w'] || keys['W']){
			if(Player.GetState()==STATE_SNOWBALL_PLAYER) 
				enemies[Player.GetSnowballPushing()].SetState(STATE_SNOWBALL_MOVING);
			Player.Jump(Scene.GetMap());
		}
		
		//A
		if ((keys['a'] || keys['A']) && Player.GetState()!=STATE_SNOWBALL_PLAYER)	{
			//if we aren't pushing a ball or standing on the top of the ball, we move normally
			if(Player.GetSnowballPushing() == -1 || Player.GetSnowballOnTopOf() != -1) {
				Player.MoveLeft(Scene.GetMap());
				Player.SetSnowballPushing(-1);
			}
			else if(Player.GetLeft()==enemies[Player.GetSnowballPushing()].GetRight()-SNOWBALL_LIMIT){
				if (Player.GetState()!=STATE_PUSH_LEFT) if(!Player.isJumping())Player.SetState(STATE_PUSH_LEFT);
				if(enemies[Player.GetSnowballPushing()].PushLeft(Scene.GetMap())) Player.PushLeft(Scene.GetMap());
			}
			else {
				Player.MoveLeft(Scene.GetMap());
				Player.SetSnowballPushing(-1);
			}
		}
		
		//D
		else if((keys['d'] || keys['D'])	&& Player.GetState()!=STATE_SNOWBALL_PLAYER)  {
			//if we aren't pushing a ball, jumping or standing on the top of the ball, we move normally
			if(Player.GetSnowballPushing() == -1 || Player.GetSnowballOnTopOf() != -1) {
				Player.MoveRight(Scene.GetMap());
				Player.SetSnowballPushing(-1);
			}
			else if(Player.GetRight()==enemies[Player.GetSnowballPushing()].GetLeft()+SNOWBALL_LIMIT){
				if (Player.GetState()!=STATE_PUSH_RIGHT)if(!Player.isJumping())Player.SetState(STATE_PUSH_RIGHT);
				if(enemies[Player.GetSnowballPushing()].PushRight(Scene.GetMap())) Player.PushRight(Scene.GetMap());
			}
			else {
				Player.MoveRight(Scene.GetMap());
				Player.SetSnowballPushing(-1);
			}
		}
		
		else if(Player.GetState()!=STATE_SNOWBALL_PLAYER) 	{
			Player.Stop();
			Player.SetSnowballPushing(-1);
		}
	}

	//PLAYER LOGIC
	if(Player.GetState() == STATE_SNOWBALL_PLAYER) {
		int x, y;
		enemies[Player.GetSnowballPushing()].GetPosition(&x,&y);
		Player.SetPosition(x,y); 
	}
	Player.Logic(Scene.GetMap());
	
	//ENEMY LOGIC
	for(int i=0;i<int(enemies.size());++i) enemies[i].Logic(Scene.GetMap());

	//COLLISIONS

	//Player 
	if(!Player.isDead()) { 
		cRect rec;
		//this checks wether you exit a collision with a snowball if you were standing on top of it
		if(Player.GetSnowballOnTopOf() != -1) {
		enemies[Player.GetSnowballOnTopOf()].GetArea(&rec);
		if(!enemies[Player.GetSnowballOnTopOf()].IsSnowball() ||!Player.Collides(&rec)) {
				Player.SetSnowballOnTopOf(-1);
			}
		}

		int l, p;
		Player.GetCurrentLives(&l);
		Player.GetCurrentPoints(&p);
		//if(enemies.size==0)LoadLevel(currentLevel+1);
		for(int i=0; i<int(enemies.size()); ++i) {
			enemies[i].GetArea(&rec);
			if(enemies[i].GetState()==STATE_SNOWBALL_MOVING || enemies[i].GetState()==STATE_SNOWBALL_PLAYER) {
				/*for(int j=0; j<int(enemies.size()); ++j) {
					if(i != j) {

				}*///mirar colisions amb altres enemics per matarlos si els toca
				int x, y;
				enemies[i].GetPosition(&x,&y);
				if(y <= BLOCK_SIZE+4 &&(enemies[i].CollidesMapWall(Scene.GetMap(),true)||enemies[i].CollidesMapWall(Scene.GetMap(),false))){
					//sumar punts per matar al enemic
					enemies.erase(enemies.begin()+i);
					if(Player.GetSnowballPushing() ==i ) {
						Player.SetSnowballPushing(-1);
						Player.SetState(STATE_LOOKRIGHT);
					}
					continue;
				}
			}
			if(Player.Collides(&rec)) {
				if(enemies[i].GetState()==STATE_SNOWBALL_MOVING && !Player.isJumping()) {
						Player.SetState(STATE_SNOWBALL_PLAYER);
						enemies[i].SetState(STATE_SNOWBALL_PLAYER);
						Player.SetSnowballPushing(i);
				}
				else if(enemies[i].IsSnowball()){
					if(Player.GetBottom() == rec.top) {
						Player.SetSnowballOnTopOf(i);
					}
					else if(Player.GetTop() == rec.bottom) {
						enemies[i].Jump(Scene.GetMap());
					}
					else if(Player.GetLeft() == rec.right) {
						Player.SetSnowballPushing(i);
					}
					else if(Player.GetRight()== rec.left) {
						Player.SetSnowballPushing(i);
					}
				}
				else if(!Player.isInvincible() && !enemies[i].isHit()) {
					Player.Die();
					if(l == 0) GameOver();
				}
			}
			//Player projectiles to  Enemy
			vector<cProjectile> p = Player.GetProjectiles();
			for(int j=0; j<int(p.size());++j) {
				if(p[j].Collides(&rec)){
					enemies[i].Hit();
					Player.EraseProjectile(j);
				}
			}
			//Enemy projectiles to Player
			if (!Player.isInvincible())
			{
				Player.GetArea(&rec);
				p = enemies[i].GetProjectiles();
				for(int j=0; j<int(p.size());++j) {
					if(p[j].Collides(&rec)){
						Player.Die();
						enemies[i].EraseProjectile(j);
					}
				}
			}
		}
	}
	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();

	Scene.Draw(Data.GetID(IMG_BLOCKS), Data.GetID(IMG_BACKGROUND));
	
	vector<cProjectile> proj;
	//DRAWENEMYS
	for(int i=0;i<int(enemies.size());++i) {
		enemies[i].Draw(IMG_ENEMY);
	}

	//DRAWPLAYER1
	Player.Draw(Data.GetID(IMG_PLAYER));
	proj = Player.GetProjectiles();
	for (int i = 0; i < int(proj.size()); ++i) 
		proj[i].Draw(Data.GetID(IMG_PLAYER));

	int l, p;
	Player.GetCurrentLives(&l);
	Player.GetCurrentPoints(&p);
	ui.Draw(l,p);

	glutSwapBuffers();
}

bool cGame::LoadEnemies(int level) {

	bool res;
	FILE *fd;
	char file[16];
	char tile;

	res=true;

	if(level<10) sprintf(file,"%s0%d%s",(char *)FILENAME_DIR,level,(char *)FILENAME_EXT);
	else		 sprintf(file,"%s%d%s",(char *)FILENAME_DIR,level,(char *)FILENAME_EXT);

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	fscanf(fd,"%c",&tile);

	enemies = vector<EnemyOne>();

	fscanf(fd,"%c",&tile);
	for(int i=SCENE_HEIGHT-1;i>=0;i--){
		for(int j=0; j<SCENE_WIDTH; ++j) {
			fscanf(fd,"%c",&tile);
			if(tile ==',') fscanf(fd,"%c",&tile);
			if(tile=='e') {
				EnemyOne en;
				en.init();
				en.SetWidthHeight(32,32);
				en.SetTile(j,i);
				en.SetState(STATE_LOOKRIGHT);
				enemies.push_back(en);
			}

		}
		fscanf(fd,"%c",&tile); //pass enter
	}
	fclose(fd);
	return res;
}

void cGame::GameOver() {
	//Game stops. Points set to 0. Lives set to PLAYER_MAX_LIVES. Show a "continue" message. If user presses yes, 
	//then the level resets and we keep playing. If not, the game starts again at level 1 or it returns to the main menu (if any). 
}