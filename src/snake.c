#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
// for random number //
#include <stdlib.h>
#include <time.h>
// internal //
#include "./draw.h"
#include "./terminal.h"

bool isVecUsed(Vec new, Vec *oldArr, int foodSize, Vec *snake, int snakeSize) {
	for (int i = 0, n = foodSize; i < n; i++) {
		if (new.x == oldArr[i].x && new.y == oldArr[i].y) {
			return true;
		}
	}
	for (int i = 0, n = snakeSize; i < n; i++) {
		if (new.x == snake[i].x && new.y == snake[i].y) {
			return true;
		}
	}
	return false;
}

int main(void) {
	Vec gameSize;

	gameSize.x = 6;
	gameSize.y = 8;
	int foodQuantity = 3;
	int snakeSize = 2;
	int ammountOfBoxesInGrid = gameSize.x * gameSize.y;

	if (foodQuantity > (ammountOfBoxesInGrid) - 1) {
		printf("too big foodQuantity max is %i\n", (ammountOfBoxesInGrid) - 1);
		return 1;
	}

	Vec snake[ammountOfBoxesInGrid];
	snake[0].x = gameSize.x / 2;
	snake[0].y = gameSize.y / 2;
	for (int i = 1, n = ammountOfBoxesInGrid; i < n; i++) {
		snake[i] = snake[0];
	}
	Vec food[foodQuantity];
	srand(time(NULL));
	initTerm();
	for (int i = 0; i < foodQuantity; i++) {
		Vec new;
		do {
			new.x = rand() % gameSize.x;
			new.y = rand() % gameSize.y;
		} while (isVecUsed(new, food, foodQuantity, snake, snakeSize));
		food[i] = new;
		drawSquare(gameSize, food[i], 1);
	}
	fflush(stdout);

	char move = 'd';
	char key = ' ';
	bool win = false;
	while (1) {
		while (kbHit() > 0) {
			key = fgetc(stdin);
				if (key == 'w' && move != 's') { move = key; }
				if (key == 's' && move != 'w') { move = key; }
				if (key == 'a' && move != 'd') { move = key; }
				if (key == 'd' && move != 'a') { move = key; }
				if (key == 'q') { goto leave; }
		}

		switch (move) {
			case 'w': 
				snake[0].x = snake[0].x - 1;
				drawSquare(gameSize, snake[0], 2);
				break;
			case 's': 
				snake[0].x = snake[0].x + 1;
				drawSquare(gameSize, snake[0], 2);
				break;
			case 'a': 
				snake[0].y = snake[0].y - 1;
				drawSquare(gameSize, snake[0], 2);
				break;
			case 'd': 
				snake[0].y = snake[0].y + 1;
				drawSquare(gameSize, snake[0], 2);
				break;
		}
		
		for (int i = snakeSize + 1; i > 0; i--) {
			snake[i] = snake[i - 1];
		}

		drawSquare(gameSize, snake[2], 22);
		drawSquare(gameSize, snake[snakeSize + 1], 0);
		fflush(stdout);

		for (int i = 0; i < foodQuantity; i++) { 
			if (snake[0].x == food[i].x && snake[0].y == food[i].y) {
				// TODO change from repeating for new pos 
				// to acquaring new pos from arr with
				// avalibe positions
				Vec new;
				do {
					new.x = rand() % gameSize.x;
					new.y = rand() % gameSize.y;
				} while (isVecUsed(new, food, foodQuantity, snake, snakeSize));
				food[i] = new;
				drawSquare(gameSize, food[i], 1);
				snakeSize++;
			}
		}
		
		if (snakeSize > ammountOfBoxesInGrid - foodQuantity) {
			win = true;
			goto leave;
		}

		fflush(stdout);
		usleep(210000);
	}
	
	
	leave:
	stopTerm();
	fflush(stdout);
	if (win) {
		printf("\e[38;5;3m<===|win|===>\e[0m\n");
	} else {
		printf("\e[38;5;1m>----|lose|----<\n");
	}
	return 0;
}
