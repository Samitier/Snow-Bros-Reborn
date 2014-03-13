#pragma once
#include "cBicho.h"

class cProjectile :	public cBicho
{
public:
	cProjectile(void);
	virtual ~cProjectile(void);

	void Draw(int tex_id);
	void Move(int *map);
};

