#ifndef GHOST_H
#define GHOST_H

#include "person.h"

class Ghost : public Person {
	private:
		enum State {HUNTER, PREY, DEAD};

	public:
		Ghost() = default;
		~Ghost();
		Ghost(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			Direction wishDirection,
			int pointsDeVie
		);

	private:
		void goCoordinate(int x, int y);
};

#endif