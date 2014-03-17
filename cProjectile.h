#pragma once
#include "cBicho.h"

#define MAX_HEIGHT		200
#define HIGHT_STEP		4

class cProjectile :	public cBicho
{
public:
	cProjectile(cBicho b);
	virtual ~cProjectile(void);

	void Draw(int tex_id);
	void Logic(int *map);

private:
	int falling_alfa;
	int falling_y;
};

