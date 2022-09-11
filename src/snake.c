#include <stdlib.h>
#include <time.h>

#include "snake.h"

void game_init(Game *game) {
	int i;

	srand(time(NULL));
	game->length = START_LENGTH;
	game->snake.x = WIDTH / 2;
	game->snake.y = HEIGHT / 2;
	game->apple.x = rand() % WIDTH;
	game->apple.y = rand() % HEIGHT;
	game->direction = Up;

	for (i = 0; i < game->length; i++) {
		game->trail[i].x = game->snake.x;
		game->trail[i].y = game->snake.y;
	}
}

void game_loop(Game *game) {
	int ate = 0;
	int i;

	switch (game->direction) {
	case Left:
		game->snake.x--;
		break;
	case Right:
		game->snake.x++;
		break;
	case Up:
		game->snake.y--;
		break;
	case Down:
		game->snake.y++;
		break;
	}

	if (game->snake.x < 0) game->snake.x = WIDTH - 1;
	else if (game->snake.x >= WIDTH) game->snake.x = 0;
	if (game->snake.y < 0) game->snake.y = HEIGHT - 1;
	else if (game->snake.y >= HEIGHT) game->snake.y = 0;

	if (game->snake.x == game->apple.x
	 && game->snake.y == game->apple.y) {
		game->length++;
		// FIXME: first 2 calls of rand gives the same values
		rand(); rand();
		game->apple.x = rand() % WIDTH;
		game->apple.y = rand() % HEIGHT;
		ate = 1;
	}

	for (i = 0; i < game->length; i++) {
		if (game->snake.x == game->trail[i].x
		 && game->snake.y == game->trail[i].y) {
			game_init(game);
			continue;
		}
	}

	if (!ate) {
		for (i = 0; i < game->length - 1; i++) {
			game->trail[i].x = game->trail[i + 1].x;
			game->trail[i].y = game->trail[i + 1].y;
		}
		ate = 0;
	}
	game->trail[game->length - 1].x = game->snake.x;
	game->trail[game->length - 1].y = game->snake.y;
}
