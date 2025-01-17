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
	int ammountOfBoxesInGrid = gameSize.x * gameSize.y;
	int foodQuantity = 33;
	if (foodQuantity > (ammountOfBoxesInGrid) - 1) {
		printf("too big foodQuantity max is %i\n", (ammountOfBoxesInGrid) - 1);
		return 1;
	}
	int snakeSize = 2;
	Vec snake[ammountOfBoxesInGrid];
	snake[0].x = gameSize.x / 2;
	snake[0].y = gameSize.y / 2;
	for (int i = 1, n = ammountOfBoxesInGrid; i < n; i++) {
		snake[i].x = 0;
		snake[i].y = 0;
	}
	Vec food[foodQuantity];
	for (int i = 0, n = foodQuantity; i < n; i++) {
		food[i].x = -1;
		food[i].y = -1;
	}

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
	char key;
	bool won = false;
	while (1) {
		// key fetching logic //
		// NOTE : for some reason "kbHit() == 1" fells soother thab "kbHit() > 0"
		while (kbHit() == 1) {
			key = fgetc(stdin);
			if (key == 'w' || key == 's' || key == 'a' || key == 'd' || key == 'q') {
				// TODO make some sor of reverse datatype for keys
				// TODO change from leave to just ignore input
				if (key == 'w' && move == 's') {
					goto leave;
				}
				if (key == 's' && move == 'w') {
					goto leave;
				}
				if (key == 'a' && move == 'd') {
					goto leave;
				}
				if (key == 'd' && move == 'a') {
					goto leave;
				}
				move = key;
			}
		}
		if (move == 'q') { break; }

		for (int i = snakeSize; i > 0; i--) {
			snake[i] = snake[i - 1];
			drawSquare(gameSize, snake[i], 22);
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

		drawSquare(gameSize, snake[snakeSize], 0);
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
		
		// TODO check why substracting from game grid boxes doest work
		if (snakeSize > ammountOfBoxesInGrid - foodQuantity) {
			won = true;
			goto leave;
		}

		fflush(stdout);
		usleep(210000);
	}
	
	
	leave:
	stopTerm();
	fflush(stdout);
	if (won) {
		printf("\e[38;5;3m<===|won|===>\e[0m\n");
	} else {
		printf("\e[38;5;1m>----|lose|----<\n");
	}
	return 0;
}
