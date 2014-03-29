#pragma once
#include "cobject.h"
class cBlock :
	public cObject
{
public:
	cBlock(void);
	cBlock(int x,int y);
	~cBlock(void);

	void Draw(int text_id);
	void Logic(int *map);
	void NextFram(int max);

protected:
};

