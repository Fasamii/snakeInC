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

void maintainFood(Vec *food, int size, Vec gameSize, Vec *snake, int snakeSize) {
	for (int i = 0, n = size; i < n; i++) {
		if ((food[i].x == -1 || food[i].y == -1) && (gameSize.x * gameSize.y) >= snakeSize + size) {
			//printf("\e[38;5;3m<food is used>\e[0m\n");
			Vec new;
			do {
				new.x = rand() % gameSize.x;
				new.y = rand() % gameSize.y;
			} while (isVecUsed(new, food, size, snake, snakeSize));
			food[i] = new;
			drawSquare(gameSize, food[i], 1);
			//printf("|\nrandom pos: x=>%i ; y=>%i\n", new.x, new.y);
		}
	}
}

bool eatFood(Vec *snake, Vec *food, int foodQuantity, int *points) {
	for (int i = 0; i < foodQuantity; i++) { 
		if (snake[0].x == food[i].x && snake[0].y == food[i].y) {
			food[i].x = -1;
			food[i].y = -1;
			*points = *points + 1;
			printf("%i", *points);
			return true;
		}
	}
	return false;
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
	gameSize.x = 5;
	gameSize.y = 5;
	int foodQuantity = 8;
	if (foodQuantity > (gameSize.x * gameSize.y) - 1) {
		printf("too big foodQuantity max is %i\n", (gameSize.x * gameSize.y) - 1);
		return 1;
	}
	int points = 2;
	Vec snake[gameSize.x * gameSize.y];
	snake[0].x = gameSize.x / 2;
	snake[0].y = gameSize.y / 2;
	for (int i = 1, n = gameSize.x * gameSize.y; i < n; i++) {
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
	maintainFood(&food[0], foodQuantity, gameSize, &snake[0], points);
	fflush(stdout);

	char move = 'd';
	char key;
	bool won = false;
	while (1) {
		// key fetching logic //
		//usleep(210000);
		sleep(1);
		while (kbHit() == 1) {
			key = fgetc(stdin);
			if (key == 'w' || key == 's' || key == 'a' || key == 'd' || key == 'q') {
				if (key == 'w' && move == 's') {
					points++;
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
		if (eatFood(&snake[0], &food[0], foodQuantity, &points)) {
			maintainFood(&food[0], foodQuantity, gameSize, &snake[0], points);
		}
		if (points >= gameSize.x * gameSize.y) {
			won = true;
			goto leave;
		}
		fflush(stdout);
	}
	
	
	leave:
	stopTerm();
	fflush(stdout);
	if (won) {
		printf("\e[38;5;3m===\nwon\n===\e[0m\n");
	} else {
		printf("\e[38;5;1m----\nlose\n----\n");
	}
	return 0;
}
