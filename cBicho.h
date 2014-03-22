#pragma once

#include "cObject.h"
#include "cProjectile.h"

#define JUMP_HEIGHT		96
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3
#define STATE_JUMPLEFT		4
#define STATE_JUMPRIGHT		5
#define STATE_THROWLEFT		6
#define STATE_THROWRIGHT	7
#define STATE_DIE			8
#define STATE_PUSH_LEFT     9
#define STATE_PUSH_RIGHT   10

using namespace std;


class cBicho :	public cObject
{
public:

	cBicho(void);
	cBicho(int x,int y,int w,int h);
	~cBicho(void);


	void MoveRight(int *map);
	void MoveLeft(int *map);
	bool PushRight(int *map);
	bool PushLeft(int *map);
	void Jump(int *map);
	void Throw(int *map);
	void Stop();
	virtual void Logic(int *map);
	vector<cProjectile> GetProjectiles();
	bool isJumping();

protected:
	bool jumping;
	bool throwing;
	vector<cProjectile> projectiles;

private:
	int jump_alfa;
	int jump_y;
};
