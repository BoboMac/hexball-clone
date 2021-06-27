/*
game.h will use the functions from the rest of the headers in
a fairly modular way. For convenience' sake, the headers will
use as few libraries as possible, so that there is no compiler
mash up between them (?).

Finally, in main.cpp there only have to be called the Update and
Init functions (as of now).
*/

#include "physics.hpp"
#include "renderer.hpp"
#include "networking.hpp"

struct Game {
	bool should_quit = 0;
	void Init() {
		
	}
	void UpdatePhysics() {

	}
	void Render() {

	}
	void Update() {

	}
};

