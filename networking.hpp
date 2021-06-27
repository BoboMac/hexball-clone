/*
The server will store information about the ball's position,
players' position, color and names. They will be sent either
via a packed struct(?) or an encoded string (e.g.
"player BoboMac red 169 255", "ball 160 256").

bivol vezi cum faci
*/

struct Networking_PlayerData {
	// Color
	// Position
	// Name/ID
};

struct Networking {
	// Will take some sort of an IP and PORT
	void ConnectToServer() {

	}
	void GetPlayerData(Networking_PlayerData *player_data) {

	}
	// Updates all entities (players & ball)
	void Update() {
		
	}
};