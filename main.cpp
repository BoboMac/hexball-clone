#include "game.hpp"

int main() {
	Game game;
	game.Init();
	while (!game.should_quit) {
		game.Update();
	}
	return 0;
}