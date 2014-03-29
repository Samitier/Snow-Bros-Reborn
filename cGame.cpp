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
	Data.init();
	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	state = STATE_MENU;

	//Scene initialization
	res = Data.LoadImage(IMG_BLOCKS,"img/tileset.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_BACKGROUND,"img/background.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_ENEMY,"img/enemy.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_ENEMY2,"img/enemy2.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_PLAYER,"img/player.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_MENU,"img/menu.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_PARTICLE,"img/particle.png",GL_RGBA);
	if(!res) return false;

	//Sounds init
	res = Data.LoadSound(SOUND_SELECT,"sounds/select.wav");
	if(!res) return false;
	res = Data.LoadSound(SOUND_JUMP,"sounds/jump.wav");
	if(!res) return false;
	res = Data.LoadSound(SOUND_ENEMY_DEATH,"sounds/enemyDeath.wav");
	if(!res) return false;
	res = Data.LoadSound(SOUND_PLAYER_SHOT,"sounds/playerShot.wav");
	if(!res) return false;
	res = Data.LoadSound(SOUND_ENEMY_SHOT,"sounds/enemyShot.wav");
	if(!res) return false;
	res = Data.LoadSound(SOUND_PLAYER_DEATH,"sounds/playerDeath.wav");
	if(!res) return false;
	res = Data.LoadSound(SOUND_SNOWBALL_SHOT,"sounds/snowballShot.wav");
	if(!res) return false;
	res = Data.LoadSound(SOUND_ACCEPT,"sounds/accept.wav");
	if(!res) return false;

	keyboard_enabled = true;
	numPlayers = 0;
	currentLevel=1;
	timer =0;
	alfa=0;
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
	Data.Release();
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;

}

void cGame::ReadMouse(int button, int state, int x, int y)
{
	if (state == STATE_PLAYING) {
		Player.PutBlock(x,-1*(y-GAME_HEIGHT), Scene.GetMap());
	}
}

bool cGame::startGame() {
	bool res = true;
	enemies = vector<Enemy>();
	Player.lvlUp(Scene.GetMap());
	particles = vector<cParticle>();
	res = Scene.LoadLevel(1);
	if(!res) return false;
	res = LoadEnemies(1);
	if(!res) return false;
	Player.init();
	ui.init(Player.GetCurrentPoints(),Player.GetCurrentLives());
	throwing = false;
	currentLevel =1;
	state=STATE_TRANSITION;
	return res;
}

bool cGame::ProcessMenu() {
	bool res = true;
	if (keys['w'] && keyboard_enabled)  {
		ui.stateUp(3);
		Data.PlaySound(SOUND_SELECT);
		keyboard_enabled = false;
	}
	else if (keys['s'] && keyboard_enabled)  {
		ui.stateDown(3);		
		Data.PlaySound(SOUND_SELECT);
		keyboard_enabled = false;
	}
	if (keys[' '] && keyboard_enabled) {
		int s = ui.getMenuState();
		Data.PlaySound(SOUND_ACCEPT);
		switch(s) {
			case 0:	
				numPlayers = 1;
				state = STATE_PLAYING;
				startGame();
				break;
			case 1:
				state = STATE_INSTRUCTIONS;
				break;
			case 2:
				state = STATE_CREDITS;
				break;
			case 3: 
				return false;
				break;
		}
	}
	if ((!keys['s'] && !keys['w'] && !keys[' ']) && !keyboard_enabled)  {
		keyboard_enabled = true;
	}
	return res;
}

bool cGame::ProcessPlaying() {
	bool res = true;
	if (keys[27]) {
			state = STATE_MENU; 
	}
	if ((keys['p'] || keys['P']) && keyboard_enabled) {
			state = STATE_PAUSE;
			Data.PlaySound(SOUND_ACCEPT);
			keyboard_enabled = false;
	}
	if ((!keys['p'] && !keys['P']) && !keyboard_enabled)  {
		keyboard_enabled = true;
	}
	if(!Player.isDead()) { //if the player is dead we will not do anything until it revives
		//INPUT
		//SPACEBAR
		if (keys[' '] && !throwing && Player.GetState()!=STATE_SNOWBALL_PLAYER)  {
			throwing = true;
			//If we are touching a snowball, we'll shoot it
			if(Player.GetState() == STATE_PUSH_LEFT) {
				Data.PlaySound(SOUND_SNOWBALL_SHOT);
				enemies[Player.GetSnowballPushing()].ShootSnowballLeft(); 
			}
			else if(Player.GetState() == STATE_PUSH_RIGHT){
				Data.PlaySound(SOUND_SNOWBALL_SHOT);
				enemies[Player.GetSnowballPushing()].ShootSnowballRight(); 
			}
			//if not, we shoot projectiles
			else {
			    Data.PlaySound(SOUND_PLAYER_SHOT);
				Player.Throw(Scene.GetMap());	
			}
		}
		else if(!keys[' ']) throwing = false;
		
		//W
		if (keys['w'] || keys['W']){
			//If we are being dragged for a snowball, we'll exit it
			if(Player.GetState()==STATE_SNOWBALL_PLAYER) {
				enemies[Player.GetSnowballPushing()].SetState(STATE_SNOWBALL_MOVING);
			}
			if(Player.CollidesMapFloor(Scene.GetMap())&&!Player.isJumping()&&Player.GetState()!=STATE_THROWLEFT &&Player.GetState()!=STATE_THROWRIGHT)Data.PlaySound(SOUND_JUMP);
			Player.Jump(Scene.GetMap());
		}
		
		//S
		if (keys['s'] || keys['S']) Player.SetSnowballOnTopOf(-1);

		//A
		if ((keys['a'] || keys['A']) && Player.GetState()!=STATE_SNOWBALL_PLAYER)	{
			//if we aren't pushing a ball or standing on the top of the ball, we move normally
			if(Player.GetSnowballPushing() == -1 || Player.GetSnowballOnTopOf() != -1) {
				Player.MoveLeft(Scene.GetMap());
				Player.SetSnowballPushing(-1);
			}
			//if not, we push the ball
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
			//if not, we push the ball
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
	for(int i=0;i<int(enemies.size());++i) 
		enemies[i].Logic(Scene.GetMap());

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

		//if(enemies.size==0)LoadLevel(currentLevel+1);
		for(int i=0; i<int(enemies.size()); ++i) {
			enemies[i].GetArea(&rec);
			
			//Logic for the moving snowball collisions
			if(enemies[i].GetState()==STATE_SNOWBALL_MOVING || enemies[i].GetState()==STATE_SNOWBALL_PLAYER) {
				//Check if it collides with another enemy, and kill it if it does
				for(int j=0; j<int(enemies.size()); ++j) {
					if(i != j && enemies[j].Collides(&rec)) {
						if(enemies[j].IsSnowball()) {
							if(enemies[i].getDirection() ==-1) enemies[j].ShootSnowballLeft();
							else enemies[j].ShootSnowballRight();
							enemies[i].SetDirection(enemies[i].getDirection()*-1);
						}
						else if(enemies[j].GetState() != STATE_SNOWBALL_MOVING){
							if(j<i) i--;
							KillEnemy(j);
							continue;
						}
					}
				}	
				//Check if enemy is a moving snowball and reached the end of level
				int x, y;
				enemies[i].GetPosition(&x,&y);
				if(y <= BLOCK_SIZE+4 &&(enemies[i].CollidesMapWall(Scene.GetMap(),true)||enemies[i].CollidesMapWall(Scene.GetMap(),false))){
					KillEnemy(i);
					continue;
				}
			}
			if(Player.Collides(&rec)) {
				//If the enemy is a moving snowball, it drags the player if he is not in another snowball
				if(enemies[i].GetState()==STATE_SNOWBALL_MOVING && !Player.isJumping() && Player.GetState() != STATE_SNOWBALL_PLAYER) {
						Player.SetState(STATE_SNOWBALL_PLAYER);
						enemies[i].SetState(STATE_SNOWBALL_PLAYER);
						Player.SetSnowballPushing(i);
				}
				//If the enemy is a non moving snowball, the player can move it or stand on top of it
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
				//If the enemy has no snow and the player is not on a moving snowball, the player dies
				else if(!Player.isInvincible() && !enemies[i].isHit()&& enemies[i].GetState() != STATE_STUNNED && Player.GetState()!=STATE_SNOWBALL_PLAYER) {
					Player.Die();
					Data.PlaySound(SOUND_PLAYER_DEATH);
					if(Player.GetCurrentLives() <= 0) {
						state = STATE_GAMEOVER;
						Player.SetCurrentPoints(Player.GetCurrentPoints()/2);
					}
				}
			}
			//Player projectiles to  Enemy
			if(Player.CheckProjectileCollisions(&rec) && enemies[i].GetState() != STATE_SNOWBALL_MOVING) enemies[i].Hit();

			//Enemy projectiles to Player
			if (!Player.isInvincible() && Player.GetState()!=STATE_SNOWBALL_PLAYER) {
				Player.GetArea(&rec);
				if(enemies[i].CheckProjectileCollisions(&rec)) {
					Player.Die();
					Data.PlaySound(SOUND_PLAYER_DEATH);
					if(Player.GetCurrentLives() <= 0) {
						state = STATE_GAMEOVER;
						Player.SetCurrentPoints(Player.GetCurrentPoints()/2);
					}
				}
				for(int j=0; j<enemies.size();++j){
					enemies[j].GetArea(&rec);
					if(enemies[j].isHit()){
						enemies[i].CheckProjectileCollisions(&rec); //para petar proyectiles si el enemigo es bola de nieve
					}
				}
			}
		}
		if(enemies.size()==0) {
			state = STATE_WINING;
		}
	}
	return res;
}

bool cGame::ProcessPause() 
{
	if ((keys['p'] || keys['P']) && keyboard_enabled) {
		state = STATE_PLAYING;
		keyboard_enabled = false;
	}
	if ((!keys['p'] && !keys['P']) && !keyboard_enabled)  keyboard_enabled = true;
	else if (keys[27])  {
		state = STATE_MENU;
	}
	return true;
}

bool cGame::ProcessWining() {
	if (keys[27]) {
		alfa =0;
		timer =0;
		state = STATE_MENU; 
	}
	
	Player.SetState(STATE_WINING_LEVEL);
	Player.Logic(Scene.GetMap());
	if(alfa ==0) alfa =1;

	if(particles.empty()) {
		++timer;
		alfa -=0.01;
		if (alfa<0) alfa =0;
	}
	if(timer >= TIME_TRANSITION) {
		timer =0;
		alfa=0;
		++currentLevel;
		Player.lvlUp(Scene.GetMap());
		LoadLevel(currentLevel);
	}
	return true;
}

bool cGame::ProcessTransition() {
	if (keys[27]) {
		alfa =0;
		timer =0;
		state = STATE_MENU; 
	}
	++timer;
	alfa +=0.01;
	if (alfa>1) alfa =1;
	if(timer >= TIME_TRANSITION) {
		state=STATE_PLAYING;
		timer =0;
		alfa =0;
	}
	return true;
}

bool cGame::ProcessGameOver() {
	bool res = true;
	if (keys['a'] && keyboard_enabled)  {
		ui.stateUp(1);
		Data.PlaySound(SOUND_SELECT);
		keyboard_enabled = false;
	}
	else if (keys['d'] && keyboard_enabled)  {
		ui.stateDown(1);		
		Data.PlaySound(SOUND_SELECT);
		keyboard_enabled = false;
	}
	if (keys[' ']) {
		int s = ui.getMenuState();
		Data.PlaySound(SOUND_ACCEPT);
		switch(s) {
			case 0:	
				state = STATE_PLAYING;
				LoadLevel(currentLevel);
				break;
			case 1:
				state = STATE_MENU;
				ui.resetMenuState();
				break;
		}
		keyboard_enabled = false;
	}
	if ((!keys['a'] && !keys['d'] && !keys[' ']) && !keyboard_enabled)  {
		keyboard_enabled = true;
	}
	return res;
	//LoadLevel(currentLevel)
	return true;
}
bool cGame::ProcessInstructions() {
	if (keys[27])  {
		keyboard_enabled = false;
		state = STATE_MENU;
	} 
	if ((!keys[27] && !keyboard_enabled))
		keyboard_enabled = true;
	return true;
}
bool cGame::ProcessCredits() {
	if (keys[27])  {
		state = STATE_MENU;
	}
	if ((!keys[27] && !keyboard_enabled))
		keyboard_enabled = true;
	return true;
}
//Process
bool cGame::Process()
{
	bool res=true;
	switch (state) {
		case STATE_MENU:
			res = ProcessMenu();
			break;
		case STATE_PLAYING:
			res = ProcessPlaying();
			break;
		case STATE_PAUSE:
			res = ProcessPause();
			break;
		case STATE_WINING:
			res = ProcessWining();
			break;
		case STATE_GAMEOVER:
			res = ProcessGameOver();
			break;
			case STATE_TRANSITION:
			res = ProcessTransition();
			break;
		case STATE_INSTRUCTIONS:
			res = ProcessInstructions();
			break;
		case STATE_CREDITS:
			res = ProcessCredits();
			break;
	}
	Data.Update();
	return res;
}

void cGame::RenderPlaying()
{
	Scene.Draw(Data.GetID(IMG_BLOCKS), Data.GetID(IMG_BACKGROUND));

	//DRAWENEMYS
	for(int i=0;i<int(enemies.size());++i) {
		switch(enemies[i].getType()) {
			case ENEMY_ONE: enemies[i].Draw(Data.GetID(IMG_ENEMY), state==STATE_PAUSE); break;
			case ENEMY_TWO:  enemies[i].Draw(Data.GetID(IMG_ENEMY2), state==STATE_PAUSE); break;
		}
	}

	//DRAWPLAYER1
	Player.Draw(Data.GetID(IMG_PLAYER), state==STATE_PAUSE);
	
	//DRAW PARTICLES
	for(int i=0; i<particles.size();++i) {
		if(particles[i].Dead()) particles.erase(particles.begin()+i);
		else particles[i].Draw(Data.GetID(IMG_PARTICLE),state==STATE_PAUSE);
	}

	ui.DrawPlaying(Player.GetCurrentLives(),Player.GetCurrentPoints(), currentLevel);
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	switch(state) {
		case STATE_PLAYING:
			RenderPlaying();
		break;
		case STATE_MENU:
			ui.DrawMenu(Data.GetID(IMG_MENU));
		break;
		case STATE_PAUSE:
			RenderPlaying();
			ui.DrawPause(Data.GetID(IMG_MENU));
		break;
		case STATE_WINING:
			if (particles.empty()) RenderTransition();
			else RenderPlaying();
		break;
		case STATE_GAMEOVER:
			ui.DrawGameOver(Data.GetID(IMG_MENU));
		break;
		case STATE_INSTRUCTIONS:
			ui.DrawInstructions(Data.GetID(IMG_MENU));
		break;
		case STATE_CREDITS:
			ui.DrawCredits(Data.GetID(IMG_MENU));
		break;
		case STATE_TRANSITION:
			RenderTransition();
		break;
	}
	glutSwapBuffers();
}

void cGame::RenderTransition() {
	glColor4f(alfa,alfa,alfa,1.0);
	RenderPlaying();
	glColor4f(1.0,1.0,1.0,1.0);
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

	for(int i=SCENE_HEIGHT-1;i>=0;i--){
		for(int j=0; j<SCENE_WIDTH; ++j) {
			fscanf(fd,"%c",&tile);
			if(tile ==',') fscanf(fd,"%c",&tile);
			if(tile=='e') {
				Enemy en(ENEMY_ONE);
				en.init();
				en.SetTile(j,i);
				enemies.push_back(en);
			}
			else if(tile=='a') {
				Enemy en(ENEMY_TWO);
				en.init();
				en.SetTile(j,i);
				enemies.push_back(en);
			}
		}
		fscanf(fd,"%c",&tile); //pass enter
	}
	fclose(fd);
	return res;
}

void cGame::KillEnemy(int i) {
	Data.PlaySound(SOUND_ENEMY_DEATH);
	int x,y;
	Player.SetCurrentPoints(Player.GetCurrentPoints()+enemies[i].GetPoints());
	enemies[i].GetPosition(&x,&y);
	cParticle prt(x,y);
	particles.push_back(prt);
	enemies.erase(enemies.begin()+i);
	if(Player.GetSnowballPushing() ==i ) {
		Player.SetSnowballPushing(-1);
		Player.SetState(STATE_LOOKRIGHT);
	}
	else if(Player.GetSnowballPushing()>i){
		Player.SetSnowballPushing(Player.GetSnowballPushing()-1);
	}
}

void cGame::LoadLevel(int level) {
	Scene.LoadLevel(level);
	Player.ResetPosition();
	enemies = vector<Enemy>();
	Player.lvlUp(Scene.GetMap());
	LoadEnemies(level);
	state = STATE_TRANSITION;
}