#include <stdio.h>
#include <unistd.h>
// internal //
#include "./typedef.h"
#include "./terminal.h"

void drawSquare(Vec gameSize, Vec pos, int color) {

	Vec size = getTermSize();
	int xDiff = size.x / gameSize.x;
	int yDiff = size.y / gameSize.y;
	int xPos = xDiff * pos.x;
	int yPos = yDiff * pos.y;
	
	// todo: make size adjust for term size 
	// int xPlus = size.x % gameSize.x;
	// int yPlus = size.y % gameSize.y;

	for (int i = yPos, n = yPos + yDiff; i < n; i++) {
		for (int j = xPos, g = xPos + xDiff; j < g; j++) {
			printf("\e[%i;%iH\e[48;5;%im ",j , i, color);
		}
	}
	printf("\e[0m");

	// printf("\e[0;0HtermSize:\nx>%i\ny>%i\n",size.x, size.y);
	// printf("\e[4;0HgameSize:\nx>%i\ny>%i\n",gameSize.x, gameSize.y);
	// printf("\e[7;0Hspacing:\nx>%i\ny>%i\n",xDiff, yDiff);
	// printf("\e[10;0HPlus:\nx>%i\ny>%i\n",xPlus, yPlus);

}
