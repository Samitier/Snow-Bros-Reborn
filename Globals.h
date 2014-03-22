
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <gl/glut.h>

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


//Player defines//
#define PLAYER_WIDTH		32
#define PLAYER_HEIGHT		32
#define INIT_PLAYER_X_TILE	8
#define INIT_PLAYER_Y_TILE	1
#define PLAYER_MAX_LIVES	3
#define TIME_INVINCIBLE		180
#define TIME_DEATH			50
#define STEP_LENGTH			2

//Enemy defines//
#define TIME_WITH_SNOW		20
#define TOTAL_HITS			4
#define TIME_STUNNED        45
#define SNOWBALL_LIMIT		10
