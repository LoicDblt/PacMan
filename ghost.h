#ifndef GHOST_H
#define GHOST_H

#include <random>

#include "coordinate.h"
#include "person.h"

class Ghost : public Person {
	public:
		// Chasse PacMan, se fait chasser (energizer), mort, attend de sortir
		enum State {HUNTER, PREY, DEAD, WAIT};
		enum Name {BLINKY, PINKY, INKY, CLYDE};

	private:
		SDL_Rect previousPosition_;

		// Direction de laquelle on vient.  Ex: wishDirection UP, behindWay DOWN
		Direction previousDirection_;

		// Compte le nombre de fois que l'algo boucle, pour la même position
		int roundCmpt_{0};

		// Etat du fantôme
		State status_{WAIT};
		Name name_;

	public:
		Ghost() = default;
		~Ghost();
		Ghost(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			Direction wishDirection,
			int healthPoints,
			State status,
			Name name
		);

	/* Getter */
	public:
		inline void setStatus(State status) {
			status_ = status;
		}

		inline Name getName(void) const {
			return name_;
		}

	/* Setter */
	public:
		inline State getStatus(void) const {
			return status_;
		}

	public:
		/* Move randomly on the map */
		void aleaMove(std::vector<SDL_Rect> &walls,
			std::vector<SDL_Rect> &tunnels);

		void eated();

	private:
		/* Give a random int beetween x and y */
		int aleaRand(int x , int y);

		/* TODO, go to a precise direction */
		void goCoordinate(int x, int y);
};

#endif