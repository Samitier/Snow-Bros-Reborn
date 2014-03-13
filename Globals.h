
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>

//Number of pixels of the window//
#define GAME_WIDTH 576
#define GAME_HEIGHT 448

//Number of tiles of the levels//
#define SCENE_WIDTH		18
#define SCENE_HEIGHT	13

//Size of the tiles in px//
#define TILE_SIZE		32
#define BLOCK_SIZE		32

//Directory and extension of the level files//
#define FILENAME_DIR	"levels/"
#define FILENAME_EXT	".txt"

#define PLAYER_MAX_LIVES 3