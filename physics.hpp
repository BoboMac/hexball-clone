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


namespace Physics {

	struct Position{
		float x;
		float y;
	};

	struct Player {
		float mass;
		float velocity;
		float speed;
		float radius;
		Position position;
		
		float GetX() {
			return position.x;
		}
		int GetY() {
			return position.y;
		}
	};

	bool IsColiding(Player a, Player b){
			float r = a.radius + b.radius;
  			r *= r;
  			if(r < (a.position.x + b.position.x)*(a.position.x + b.position.x) + (a.position.y + b.position.y)^2)
				return false;
			else
				return true;
	}

	struct World {

	};

	struct Entity {
		 		
	};
}
