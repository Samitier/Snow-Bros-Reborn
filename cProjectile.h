#pragma once
#include "cObject.h"

#define MAX_HEIGHT		200
#define HIGHT_STEP		4
#define STATE_GO_RIGHT	0
#define STATE_GO_LEFT	1
#define TYPE_1			0
#define TYPE_2			1
class cProjectile :	public cObject
{

public:
	cProjectile(int x, int y, int w, int h, int state,int type);
	~cProjectile(void);
	bool Destroy(int* map);
	void Draw(int tex_id);
	void Logic(int *map);

private:
	int falling_alfa;
	int falling_y;
	int type;
	int timeAlive;
};

