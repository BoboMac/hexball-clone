/*
The server will store information about the ball's position,
players' position, color and names. They will be sent either
via a packed struct(?) or an encoded string (e.g.
"player BoboMac red 169 255", "ball 160 256").

TODO:
- send actual player data (and let the server decode it *ghm ghm*)
*/

#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <vector>
#include <thread>

// socket bs the compiler is too old to implement
int inet_pton(int af, const char *src, void *dst) {
	struct sockaddr_storage ss;
	int size = sizeof(ss);
	char src_copy[INET6_ADDRSTRLEN + 1];

	ZeroMemory(&ss, sizeof(ss));
	/* stupid non-const API */
	strncpy(src_copy, src, INET6_ADDRSTRLEN + 1);
	src_copy[INET6_ADDRSTRLEN] = 0;

	if (WSAStringToAddress((LPSTR)src_copy, af, NULL, (struct sockaddr *)&ss, &size) == 0)
	{
		switch (af)
		{
		case AF_INET:
			*(struct in_addr *)dst = ((struct sockaddr_in *)&ss)->sin_addr;
			return 1;
		case AF_INET6:
			*(struct in6_addr *)dst = ((struct sockaddr_in6 *)&ss)->sin6_addr;
			return 1;
		}
	}
	return 0;
}
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size) {
	struct sockaddr_storage ss;
	unsigned long s = size;

	ZeroMemory(&ss, sizeof(ss));
	ss.ss_family = af;

	switch (af)
	{
	case AF_INET:
		((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
		break;
	case AF_INET6:
		((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
		break;
	default:
		return NULL;
	}
	/* cannot direclty use &size because of strict aliasing rules */
	return (WSAAddressToString((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0) ? dst : NULL;
}

enum PlayerColor {
	PlayerColorRed,
	PlayerColorBlue
};

struct Networking_EntityData {
	PlayerColor color;
	float x, y;
	char* name;
};

struct Networking {
	char entities_num = 2;
	Networking_EntityData *entities;
	// Returns 1 on success
	bool ConnectToServer() {
		// Initialize winsock
		WSAData data;
		if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
			return 0;

		// Create socket
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET)
			return 0;

		// Fill in the hint struct
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, ip_addr, &hint.sin_addr);

		// Actually connet to the mfking server
		if (connect(sock, (sockaddr *)&hint, sizeof(hint)) == SOCKET_ERROR) {
			closesocket(sock);
			return 0;
		}

		// Initialize the other shit
		entities = (Networking_EntityData*)malloc(entities_num * sizeof(Networking_EntityData));
		for(int i = 0; i < entities_num; i++) {
			entities[i].name = (char*)malloc(256);
			ZeroMemory(entities[i].name, 256);
		}
		return 1;
	}
	void GetEntityData(char* data, int size, Networking_EntityData *player_data) {
		if (!data || !size) {
			std::cout << "No data being received.\n";
			return;
		}
		std::string tokens[4]; // name color x y
		std::string token;
		char token_index = 0;
		for(int i = 0; i < size && data[i] != 0; i++) {
			if (data[i] == ' ') {
				tokens[token_index] = token;
				token.clear();
				token_index++;
			}
			else {
				token += data[i];
			}
		}
		tokens[token_index] = token;
		token.clear();
		token_index++;

		if (tokens[0].size() && tokens[1].size() && tokens[2].size() && tokens[3].size()) {
			//player_data->name = (char*)tokens[0].c_str();
			player_data->color = (tokens[1] == "red" ? PlayerColorRed : PlayerColorBlue);
			player_data->x = std::stof(tokens[2]);
			player_data->y = std::stof(tokens[3]);
		}
	}
	// Update all entitie's data
	void ReadServerData() {
		Sleep(10);
		for(int i = 0; i < entities_num; i++) {
			char* buf = (char*)malloc(4096);
			ZeroMemory(buf, 4096);
			int received_bytes = recv(sock, buf, 4096, 0);
			GetEntityData(buf, received_bytes, &entities[i]);
		}
	}
	void SendPlayerData(const std::string& name, PlayerColor color, float x, float y) {
		std::string data = name + (color == PlayerColorRed ? " red " : " blue ") + std::to_string(x) + " " + std::to_string(y);
		send(sock, data.c_str(), data.size() + 1, 0);
	}
private:
	const char *ip_addr = "127.0.0.1";
	int port = 54000;
	SOCKET sock;
};