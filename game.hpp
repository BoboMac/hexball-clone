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
		renderer.Init();
		renderer.CreateBrush(&brush_red, 1, 0, 0);
		renderer.CreateBrush(&brush_blue, 0, 0, 1);
		renderer.CreateBrush(&brush_green, 0, 1, 0);
		renderer.CreateBrush(&brush_grey, 0.4f, 0.4f, 0.4f);

		player1.position.x = 100;
		player1.position.y = 100;
		player1.radius = 50;
		player1.speed = 2.0f;

		player2.position.x = 200;
		player2.position.y = 200;
		player2.radius = 50;
		player2.speed = 2.0f;

	}
	void Update() {
		renderer.PullMessages();
		UpdatePhysics();
		Render();
	}
private:
	Renderer renderer;
	RendererBrush brush_red;
	RendererBrush brush_blue;
	RendererBrush brush_green;
	RendererBrush brush_grey;

	Physics::Entity player1;
	Physics::Entity player2;

	void UpdatePhysics() {
		if (GetAsyncKeyState('W'))
			player1.position.y -= player1.speed;
		else if (GetAsyncKeyState('S'))
			player1.position.y += player1.speed;
		if (GetAsyncKeyState('A'))
			player1.position.x -= player1.speed;
		else if (GetAsyncKeyState('D'))
			player1.position.x += player1.speed;

		if (GetAsyncKeyState(VK_UP))
			player2.position.y -= player2.speed;
		else if (GetAsyncKeyState(VK_DOWN))
			player2.position.y += player2.speed;
		if (GetAsyncKeyState(VK_LEFT))
			player2.position.x -= player2.speed;
		else if (GetAsyncKeyState(VK_RIGHT))
			player2.position.x += player2.speed;

	}
	void Render() {
		renderer.Begin();
		renderer.Clear();
		if (Physics::IsColliding(player1, player2))
			renderer.Ellipse(player1.position.x, player1.position.y, player1.radius, brush_green);
		else
			renderer.Ellipse(player1.position.x, player1.position.y, player1.radius, brush_red);

		renderer.Ellipse(player2.position.x, player2.position.y, player2.radius, brush_blue);
		renderer.End();
	}
};
