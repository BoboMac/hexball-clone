// random nonsense

#include "game.hpp"

int main() {
	Game game;
	while (!game.should_quit) {
		game.Update();
	}
	return 0;
}