#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
// for random number //
#include <stdlib.h>
#include <time.h>
// internal //
#include "./draw.h"
#include "./terminal.h"

bool isVecUsed(Vec new, Vec *oldArr, int size, Vec *snake) {
	for (int i = 0, n = size; i < n; i++) {
		if (new.x == oldArr[i].x && new.y == oldArr[i].y) {
			return true;
		} else if (new.x == snake[i].x && new.y == snake[i].y) {
			return false;
		}
	}
	return false;
}

void maintainFood(Vec *food, int size, Vec gameSize, Vec *snake) {
	for (int i = 0, n = size; i < n; i++) {
		if (food[i].x == -1 || food[i].y == -1) {
			//printf("\e[38;5;3m<food is used>\e[0m\n");
			Vec new;
			do {
				new.x = rand() % gameSize.x;
				new.y = rand() % gameSize.y;
			} while (isVecUsed(new, food, size, snake));
			food[i] = new;
			drawSquare(gameSize, food[i], 1);
			//printf("|\nrandom pos: x=>%i ; y=>%i\n", new.x, new.y);
		}
	}
}

void moveSnake(Vec *snake, Vec *food, Vec gameSize, int foodSize, char move, int points) {
	for (int i = points; i > 0; i--) {
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
	drawSquare(gameSize, snake[points], 0);
	fflush(stdout);
}

int main(void) {
	Vec gameSize;
	gameSize.x = 20;
	gameSize.y = 20;
	int foodQuantity = 10;
	if (foodQuantity > (gameSize.x * gameSize.y) - 1) {
		printf("too big foodQuantity max is %i\n", (gameSize.x * gameSize.y) - 1);
		return 1;
	}
	int points = 3;
	Vec snake[gameSize.x * gameSize.y];
	snake[0].x = gameSize.x / 2;
	snake[0].y = gameSize.y / 2;
	snake[1].x = gameSize.x / 2 - 1;
	snake[1].y = gameSize.y / 2;
	snake[2].x = gameSize.x / 2 - 2;
	snake[2].y = gameSize.y / 2;
	snake[3].x = gameSize.x / 2 - 3;
	snake[3].y = gameSize.y / 2;
	Vec food[foodQuantity];
	for (int i = 0, n = foodQuantity; i < n; i++) {
		food[i].x = -1;
		food[i].y = -1;
	}
	srand(time(NULL));
	initTerm();
	maintainFood(&food[0], foodQuantity, gameSize, &snake[0]);
	fflush(stdout);

	char move = 'd';
	char key;
	while (1) {
		// key fetching logic //
		usleep(210000);
		while (kbHit() == 1) {
			key = fgetc(stdin);
			if (key == 'w' || key == 's' || key == 'a' || key == 'd' || key == 'q') {
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
		// snake game logic //
		moveSnake(&snake[0], &food[0], gameSize, foodQuantity, move, points);
		maintainFood(&food[0], foodQuantity, gameSize, &snake[0]);
		fflush(stdout);
	}
	leave:
	fflush(stdout);
		
	stopTerm();
	return 0;
}
