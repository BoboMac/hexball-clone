/*
game.h will use the functions from the rest of the headers in
a fairly modular way. For convenience' sake, the headers will
use as few libraries as possible, so that there is no compiler
mash up between them (?).
*/

#include "physics.hpp"
#include "renderer.hpp"
#include "networking.hpp"

struct Game {
	bool should_quit = 0;
	void UpdatePhysics() {

	}
	void Render() {

	}
	void Update() {

	}
};

