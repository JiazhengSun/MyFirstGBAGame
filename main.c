#include "myLib.h"
#include "myShip.h"
#include "myBug.h"
#include "levels.h"
#include "StartScreen.h"
#include "Ending.h"
#include "text.h"
#include "Win.h"
#include <stdlib.h>
#include <stdio.h>
int red = RED;

SHIP ship;
BUGS bugs[20];
char buffer[100];
enum GAMESTATE state;

void reset();

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	reset();
	while(1) {
		waitForVblank();
		switch (state) {
			case START:
				drawImage3(0, 0, 240, 160, StartScreen); //The start screen
				state = READY;
				break;
			case READY:
				if (KEY_DOWN_NOW(BUTTON_B)) {
					drawBg();
					state = PLAY;
				}
				break;
			case PLAY:
				if(KEY_DOWN_NOW(BUTTON_A)) {
					reset();
				}
				eraseImage3(150, 0, 240, 10);
				sprintf(buffer, "%d bugs left", bugsNum);
				drawString(150, 0, buffer, red);
				sprintf(buffer, "%d lives left", lives);
				drawString(150, 100, buffer, red);
				sprintf(buffer, "level %d", level);
				drawString(150, 190, buffer, red);
				updateShip(&ship);
				updateBugs(bugs, &ship, &state);
				if (bugsNum == 0 && lives > 0) {
					state = WON;
				}
				break;
			case WON:
				if (level == 1) {
					drawString(100, 10, "Almost there! Press enter to continue!", red);
					if(KEY_DOWN_NOW(BUTTON_A)) {
						reset();
					}
					if (KEY_DOWN_NOW(BUTTON_START)) {
						level++;
						drawBg();
						setShip(&ship);
						setBugs(bugs);
						state = PLAY;
					}
				} else {
					drawImage3(0, 0, 240, 160, Win); 
					if (KEY_DOWN_NOW(BUTTON_START) || KEY_DOWN_NOW(BUTTON_A)) {
						reset();
					}
				}
				break;
			case DIE:
				drawBg();
				sprintf(buffer, "%d lives left", lives);
				drawString(50, 75, buffer, red);
				if(KEY_DOWN_NOW(BUTTON_A)) {
					reset();
				}
				if (KEY_DOWN_NOW(BUTTON_START)) {
					drawBg();
					state = PLAY;
					ship.x = START_X;
					ship.y = START_Y;
					for (int i = 0; i < bugsNum; i++) {
						bugs[i].y = bugs[i].startY;
						bugs[i].charge = 0;
					}
				}
				break;
			case LOSE:
				drawImage3(0, 0, 240, 160, Ending);
				if(KEY_DOWN_NOW(BUTTON_A)) {
					reset();
				}
				if (KEY_DOWN_NOW(BUTTON_START)) {
					reset();
				}
				break;
		}
	}
	return 0;
}

void reset() {
	lives = START_LIVES;
	level = START_LEVEL;
	setShip(&ship);
	bugsNum = 0;
	setBugs(bugs);
	state = START;
}