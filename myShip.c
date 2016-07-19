#include "myShip.h"
#include "myLib.h"
#include "Player.h"

const int shipWidth = PLAYER_WIDTH;
const int shipHeight = PLAYER_HEIGHT;
int lives;

void setShip(SHIP* ship) {
	ship->x = START_X;
	ship->y = START_Y;
	ship->OldX = ship->x;
	ship->OldY = ship->y;
	ship->width = shipWidth;
	ship->height = shipHeight;
}

void updateShip(SHIP* ship) {
	ship->OldX = ship->x;
	ship->OldY = ship->y;
	if (KEY_DOWN_NOW(BUTTON_LEFT)) {
		ship->x -= 3;
	} else if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
		ship->x += 3;
	} else if (KEY_DOWN_NOW(BUTTON_UP)) {
		ship->y -= 3;
	} else if (KEY_DOWN_NOW(BUTTON_DOWN)) {
		ship->y += 3;
	}
	if (ship->y < 0) {
		ship->y = 0;
	}
	if (ship->x < 0) {
		ship->x = 0;
	}
	if (ship->y + ship->width > 150) {
		ship->y = 150 - ship->width;
	}
	if (ship->x + ship->height > 240) {
		ship->x = 240 - ship->height;
	}
	eraseImage3(ship->OldY, ship->OldX, ship->width, ship->height);
	drawImage3(ship->y, ship->x, ship->width, ship->height, Player);
}
