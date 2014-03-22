#pragma once
#include "cObject.h"

#define MAX_HEIGHT		200
#define HIGHT_STEP		4
#define STATE_GO_RIGHT	0
#define STATE_GO_LEFT	1

class cProjectile :	public cObject
{

public:
	cProjectile(int x, int y, int w, int h, int state);
	~cProjectile(void);

	void Draw(int tex_id);
	void Logic(int *map);

private:
	int falling_alfa;
	int falling_y;
};

