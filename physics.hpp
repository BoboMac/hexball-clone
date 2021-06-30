#include <vector>

/*
Only spheres will be used, so collision will be fairly
trivial. We can either use a system of 2D vectors and
compute the velocity, acceleration and position manually,
or we can use a Box2D setup with no gravity.

There will be a function that will return the position of
each entity, which will then be sent to the server. Even
though this approach is easily hackable, who gives a shit.

bivol vezi ce drq faci
*/

#define MAX_VELOCITY 3.0f

namespace Physics {

	struct Float2 {
		float x;
		float y;
	};
	struct World {

	};
	struct Entity {
		float mass;
		Float2 velocity = {0, 0};
		float acceleration = 0.1f;
		float radius;
		Float2 position;
		void MoveLeft()  { velocity.x -= acceleration; }
		void MoveRight() { velocity.x += acceleration; }
		void MoveUp()    { velocity.y -= acceleration; }
		void MoveDown()  { velocity.y += acceleration; }
		void Update() {
			velocity.x *= 0.99f;
			velocity.y *= 0.99f;

			if (velocity.x > MAX_VELOCITY) velocity.x = MAX_VELOCITY;
			else if (velocity.x < -MAX_VELOCITY) velocity.x = -MAX_VELOCITY;
			if (velocity.y > MAX_VELOCITY) velocity.y = MAX_VELOCITY;
			else if (velocity.y < -MAX_VELOCITY) velocity.y = -MAX_VELOCITY;

			position.x += velocity.x;
			position.y += velocity.y;
		}
	};
	bool IsColliding(Entity a, Entity b) {
		float r = a.radius + b.radius;
		if(r*r < (a.position.x - b.position.x)*(a.position.x - b.position.x) + (a.position.y - b.position.y) * (a.position.y - b.position.y))
			return false;
		else
			return true;
	}
}
