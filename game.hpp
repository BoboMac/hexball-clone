/*
game.h will use the functions from the rest of the headers in
a fairly modular way. For convenience' sake, the headers will
use as few libraries as possible, so that there is no compiler
mash up between them (?).

Finally, in main.cpp there only have to be called the Update and
Init functions (as of now).
*/

#include "physics.hpp"
#include "networking.hpp"
#include "renderer.hpp"

struct Game {
	std::string name;
	bool should_quit = 0;
	void Init() {
		// Name input
		std::cout << "sup wanna enter ur name? : ";
		std::cin >> name;

		// Networking testing
		net.ConnectToServer();

		renderer.Init();
		renderer.CreateBrush(&brush_red, 1, 0, 0);
		renderer.CreateBrush(&brush_blue, 0, 0, 1);
		renderer.CreateBrush(&brush_green, 0, 1, 0);
		renderer.CreateBrush(&brush_grey, 0.4f, 0.4f, 0.4f);

		player.position.x = 100;
		player.position.y = 100;
		player.radius = 50;
		player.speed = 2.0f;
	}
	void Update() {
		renderer.PullMessages();
		UpdatePhysics();
		std::thread t ( [this] { this->UpdateNetworking(); } );
		t.detach();
		Render();
	}
private:
	Networking net;

	Renderer renderer;
	RendererBrush brush_red;
	RendererBrush brush_blue;
	RendererBrush brush_green;
	RendererBrush brush_grey;

	Physics::Entity player;

	void UpdatePhysics() {
		if (GetAsyncKeyState('W'))
			player.position.y -= player.speed;
		else if (GetAsyncKeyState('S'))
			player.position.y += player.speed;
		if (GetAsyncKeyState('A'))
			player.position.x -= player.speed;
		else if (GetAsyncKeyState('D'))
			player.position.x += player.speed;
	}
	void UpdateNetworking() {
		net.SendPlayerData(name, PlayerColorRed, player.position.x, player.position.y);
		net.ReadServerData();
	}
	void Render() {
		bool is_colliding = 0;
		renderer.Begin();
		renderer.Clear();
		for(int i = 0; i < net.entities_num && !is_colliding; i++) {
			if (net.entities[i].name != name) {
				Physics::Entity e;
				e.position = { net.entities[i].x, net.entities[i].y };
				e.radius = 50; // Standard radius
				if (Physics::IsColliding(player, e)) {
					is_colliding = 1;
				}
				renderer.Ellipse(e.position.x, e.position.y, e.radius, brush_red);
				std::cout << "\n" << e.position.x << " " << e.position.y;
			}
		}
		if (is_colliding)
			renderer.Ellipse(player.position.x, player.position.y, player.radius, brush_green);
		else
			renderer.Ellipse(player.position.x, player.position.y, player.radius, brush_blue);

		renderer.End();
	}
};
