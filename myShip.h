#ifndef _MYSHIP_H_
#define _MYSHIP_H_
extern int lives;
typedef struct {
	int x;
	int y;
	int OldX;
	int OldY;
	int width;
	int height;
} SHIP;

void setShip(SHIP*);
void updateShip(SHIP*);
#endif