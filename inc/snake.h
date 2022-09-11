#ifndef _SNAKE_H
#define _SNAKE_H

#include <stdint.h>

#define BLOCK_LENGTH 40
#define WIDTH 20
#define HEIGHT 20
#define START_LENGTH 4
#define FPS 10

typedef enum {
	Left,
	Right,
	Up,
	Down
} Direction;

typedef struct {
	int x;
	int y;
} Pos;

typedef struct {
	int length;
	Pos trail[WIDTH * HEIGHT];
	Pos snake;
	Pos apple;
	Direction direction;
} Game;

void game_init(Game *);
void game_loop(Game *);

#endif
