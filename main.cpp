#include "game.hpp"
#include "physics.hpp"
#include <vector>

int main() {
	Game game;
	while (!game.should_quit) {
		game.Update();
	}
	return 0;
}