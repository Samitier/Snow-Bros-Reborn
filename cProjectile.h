#pragma once
#include "cBicho.h"

class cProjectile :	public cBicho
{
public:
	cProjectile(cBicho b);
	virtual ~cProjectile(void);

	void Draw(int tex_id);
	void Move(int *map);
	void Logic(int *map);

private:
	int falling_alfa;
	int falling_y;
};

