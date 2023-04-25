#ifndef GHOST_H
#define GHOST_H

#include <random>

#include "person.h"

class Ghost : public Person {
	private:
		enum State {HUNTER, PREY, DEAD};
		Direction previousDirection_;	// Direction de laquelle on vient. Ex: wishDirection UP, behindWay DOWN
		int roundCmpt_{0}; // Compte le nombre de fois que l'algo boucle, pour la même position
		SDL_Rect previousPosition_;

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

		/* Move randomly on the map */
		void aleaMove(std::vector<SDL_Rect> &walls,
			std::vector<SDL_Rect> &tunnels);

	private:
		/* Give a random int beetween x and y */
		int aleaRand(int x , int y);

		/* TODO, go to a precise direction */
		void goCoordinate(int x, int y);

};

#endif