#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, 240)] = color;
}

void delay(int n)
{
	volatile int x = 0;
	for(int i=0; i<5000*n; i++)
	{
		x = x + 1;
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER<160);
}

/* drawimage3
 * A function that will draw an arbitrary sized image
 * onto the screen (with DMA).
 * @param r row to draw the image
 * @param c column to draw the image
 * @param width width of the image
 * @param height height of the image
 * @param image Pointer to the first element of the
image.
 */
void drawImage3(int r, int c, int width, int height, const u16* image) {
	for (int i = 0; i < height; i++) {
		DMA[3].src = image + width * i;
        DMA[3].dst = videoBuffer + OFFSET(r + i, c, 240);
        DMA[3].cnt = width | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
	}
}

void eraseImage3(int r, int c, int width, int height) {
	volatile int black = BLACK;
	for (int i = 0; i < height; i++) {
		DMA[3].src = &black;
        DMA[3].dst = videoBuffer + OFFSET(r + i, c, 240);
        DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
	}
}

void drawBg() {
	volatile int black = BLACK;
	DMA[3].src = &black;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = 38400 | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT | DMA_ON;
}

void drawRect(int x, int y, int width, int height, u16 color) {
	for (int h = 0; h <= height; h++)
		for (int w = 0; w <= width; w++)
			setPixel(x + h, y + w, color);
}
