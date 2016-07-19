#ifndef _MYBUG_H_
#define _MYBUG_H_
#include "myShip.h"
#include "myLib.h"

extern int bugsNum;
extern int lives;
typedef struct {
	int x;
	int y;
	int startX;
	int startY;
	int OldX;
	int OldY;
	int width;
	int height;
	int species;
	int hor;
	int charge;
} BUGS;

void setBugs(BUGS*);
void updateBugs(BUGS *, SHIP *, enum GAMESTATE *);

#endif