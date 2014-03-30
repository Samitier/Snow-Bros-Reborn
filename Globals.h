
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <gl/glut.h>
using namespace std;

//Game States
#define STATE_MENU			0
#define STATE_PLAYING		1
#define STATE_INTRO			2
#define STATE_PAUSE			3
#define STATE_GAMEOVER		4
#define STATE_WINING		5
#define STATE_TRANSITION	6
#define STATE_INSTRUCTIONS	7
#define STATE_CREDITS		8
#define STATE_GAME_END		9


//Number of pixels of the window//
#define GAME_WIDTH		576
#define GAME_HEIGHT		448

//Number of tiles of the levels//
#define SCENE_WIDTH		18
#define SCENE_HEIGHT	13

//Separation from window size to game size//
#define SCENE_Xo		0
#define SCENE_Yo		0

//Size of the tiles in px//
#define TILE_SIZE		32
#define BLOCK_SIZE		32

//Directory and extension of the level files//
#define FILENAME_DIR	"levels/"
#define FILENAME_EXT	".txt"

//Animations
#define FRAME_DELAY		5
#define TIME_TRANSITION	100

//Player defines//
#define PLAYER_WIDTH		32
#define PLAYER_HEIGHT		32
#define INIT_PLAYER_X_TILE	8
#define INIT_PLAYER_Y_TILE	1
#define PLAYER_MAX_LIVES	3
#define TIME_INVINCIBLE		200
#define TIME_DEATH			FRAME_DELAY*8
#define TIME_RESPAWN		FRAME_DELAY*6
#define STEP_LENGTH			2
#define TIME_THROWING		FRAME_DELAY*2
#define THROW_LOAD			FRAME_DELAY+FRAME_DELAY/2		//THROW_LOAD <= TIME_THROWING
#define MAX_BLOCKS			2		

//Enemy defines//
#define ENEMY_WIDTH			32
#define ENEMY_HEIGHT		32
#define TIME_WITH_SNOW		150
#define TOTAL_HITS			4
#define TIME_STUNNED        50
#define SNOWBALL_LIMIT		10
#define ENEMY_POINTS		500

#define MAX_LVL				3

//somos el grupo 07
//pctic0405.lsi.upc.edu
//port 22
//uservj07
//jesus.alonso@gmail.com