#include "snake.h"
#include "gfx.h"

int main() {
	Game game;
	game_init(&game);
	gfx_start(&game, gfx_create_window(WIDTH * BLOCK_LENGTH, HEIGHT * BLOCK_LENGTH), FPS);
	return 0;
}
