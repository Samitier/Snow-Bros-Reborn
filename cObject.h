#pragma once

#include "cTexture.h"
#include "Globals.h"

using namespace std;

class cRect
{
public:
	int left,top,
		right,bottom;
};

class cObject
{
public:
	cObject(void);
	cObject(int x,int y,int w,int h);
	~cObject(void);

	void SetPosition(int x,int y);
	void GetPosition(int *x,int *y);
	void SetTile(int tx,int ty);
	void GetTile(int *tx,int *ty);
	void SetWidthHeight(int w,int h);
	void GetWidthHeight(int *w,int *h);

	bool Collides(cRect *rc);
	bool CollidesMapWall(int *map,bool right);
	virtual bool CollidesMapFloor(int *map);
	virtual void GetArea(cRect *rc);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);

	virtual void Logic(int *map);

	int  GetState();
	void SetState(int s);
	
	int GetLeft();
	int GetRight();
	int GetBottom();
	int GetTop();

	void NextFrame(int max);
	int  GetFrame();

protected:
	int x,y;
	int w,h;
	int state;
	int seq,delay;

private:

};
