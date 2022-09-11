#include <stdio.h>

#include "SDL2/SDL.h"
#include "queue.h"
#include "gfx.h"

#define KEY_QUEUE_LENGTH 10

SDL_Window *gfx_create_window(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
	SDL_Window *win = SDL_CreateWindow(
		"Snake",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
        SDL_WINDOW_SHOWN
	);
	return win;
}

void gfx_start(Game *game, SDL_Window *win, int fps) {
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Rect rect;
	Queue *queue;
	char title[50];
	int paused;
	int close;
	int i;

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	rect.w = BLOCK_LENGTH;
	rect.h = BLOCK_LENGTH;
	queue = create_queue(KEY_QUEUE_LENGTH);
	paused = 0;
	close = 0;

	while (!close) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				close = 1;
				break;
			case SDL_KEYDOWN:
				enqueue(queue, event.key.keysym.scancode);
				break;
			default:
				break;
			}
		}
		if (!is_queue_empty(queue)) {
			switch (dequeue(queue)) {
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				if (game->direction != Down)
					game->direction = Up;
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				if (game->direction != Right)
					game->direction = Left;
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				if (game->direction != Up)
					game->direction = Down;
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				if (game->direction != Left)
					game->direction = Right;
				break;
			case SDL_SCANCODE_ESCAPE:
				close = 1;
				break;
			case SDL_SCANCODE_P:
				paused = !paused;
				break;
			default:
				break;
			}
		}
		if (paused) continue;
		game_loop(game);
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		rect.x = game->apple.x * BLOCK_LENGTH;
		rect.y = game->apple.y * BLOCK_LENGTH;
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		rect.x = game->snake.x * BLOCK_LENGTH;
		rect.y = game->snake.y * BLOCK_LENGTH;
		SDL_RenderFillRect(renderer, &rect);

		for (i = 0; i < game->length - 1; i++) {
			rect.x = game->trail[i].x * BLOCK_LENGTH;
			rect.y = game->trail[i].y * BLOCK_LENGTH;
			SDL_RenderFillRect(renderer, &rect);
		}

		SDL_RenderPresent(renderer);
		sprintf(title, "Score: %d", game->length - START_LENGTH);
		SDL_SetWindowTitle(win, title);
		SDL_Delay(1000 / fps);
	}
	free_queue(queue);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
