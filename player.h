#ifndef PLAYER_H
#define PLAYER_H

#include "person.h"

class Player : public Person {
	public:
		Player() = default;
		~Player();
		Player(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			Direction wishDirection,
			int pointsDeVie
		);
};

#endif