#include "myBug.h"
#include "myLib.h"
#include "levels.h"
#include "myShip.h"
#include "Bug1.h"
#include "Bug2.h"
#include "text.h"
#include <stdlib.h>
#include <stdio.h>

const int bugWidth = BUG1_WIDTH;
const int bugHeight = BUG1_HEIGHT;
const int easy = sizeof(levelEasy) / sizeof(int);
const int hard = sizeof (levelHard)/ sizeof(int);
int bugsNum;

void setBugs(BUGS* bugs) {
	if (level == 1) { //only one type of eneyme in this level
		for (int i = 0; i < easy/4; i++) {
			BUGS newBug;
			newBug.x = levelEasy[0 + i * 4];
			newBug.y = levelEasy[1 + i * 4];
			newBug.hor = levelEasy[2 + i * 4];
			newBug.species = 1;
			newBug.startX = newBug.x;
			newBug.startY = newBug.y;
			newBug.OldX = newBug.x;
			newBug.OldY = newBug.y;
			newBug.width = bugWidth;
			newBug.height = bugHeight;
			newBug.charge = 0;
			bugs[bugsNum] = newBug;
			bugsNum += 1;
		}
	} else if (level == 2) {
		for (int i = 0; i < hard/4; i++) {
			BUGS newBug;
			newBug.x = levelHard[0 + i * 4];
			newBug.y = levelHard[1 + i * 4];
			newBug.hor = levelHard[2 + i * 4];
			newBug.species = levelHard[3 + i * 4];
			newBug.startX = newBug.x;
			newBug.startY = newBug.y;
			newBug.OldX = newBug.x;
			newBug.OldY = newBug.y;
			newBug.width = bugWidth;
			newBug.height = bugHeight;
			newBug.charge = 0;
			bugs[bugsNum] = newBug;
			bugsNum += 1;
		}
	}
}

void updateBugs(BUGS *bugs, SHIP *ship, enum GAMESTATE *state) {
	for (int i = 0; i < bugsNum; i++) {
		int collision = 0;
		if (bugs[i].charge == 0 && rand()%500 < 2) {
			bugs[i].charge = 2;
		}
		if (bugs[i].species == 2) {
			int shake = 5;
			int r = rand() % 50;
			if (r < 25) {
				bugs[i].x += shake;
			} else {
				bugs[i].x -= shake;
			}
		}
		bugs[i].y += bugs[i].charge;
		
		if (bugs[i].x + bugs[i].height >= 240 || bugs[i].x <= 0
			|| bugs[i].y + bugs[i].width >= 170 || bugs[i].y <= 0) {
			collision = 1; //bugs hit the wall
		}
		if ((ship->x <= bugs[i].x + bugs[i].height && ship->x >= bugs[i].x &&ship->y <= bugs[i].y + bugs[i].width && ship->y >= bugs[i].y)
		|| (bugs[i].x <= ship->x + ship->height &&bugs[i].x >= ship->x &&bugs[i].y <= ship->y + ship->width && bugs[i].y >= ship->y)) {
			collision = 2; //bugs hit the ship
		}
		eraseImage3(bugs[i].OldY, bugs[i].OldX, bugs[i].width, bugs[i].height);
		if (bugs[i].species == 1) {
			drawImage3(bugs[i].y, bugs[i].x, bugs[i].width, bugs[i].height, Bug1);
		} else if (bugs[i].species == 2) {
			drawImage3(bugs[i].y, bugs[i].x, bugs[i].width, bugs[i].height, Bug2);
		}
		if (collision != 0) {
			if (collision == 2) {
				eraseImage3(ship->y, ship->x, ship->width, ship->height);
				lives--;
				if (lives > 0) {
					*state = DIE;
				} else if (lives == 0) {
					*state = LOSE;
				}
			}
			eraseImage3(bugs[i].OldY, bugs[i].OldX, bugs[i].width, bugs[i].height);
			for (int j = i; j < bugsNum - 1; j++) {
				bugs[j] = bugs[1 + j];
			}
			bugsNum--;
		}
		bugs[i].OldX = bugs[i].x;
		bugs[i].OldY = bugs[i].y;
	}
}
