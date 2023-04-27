#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"
#include "ghost.h"
#include "person.h"
#include "stats.h"

class Player : public Person {
	/* Constructor & Destructor */
	public:
		Player() = default;
		~Player();
		Player(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			Direction wishDirection,
			int healthPoints
		);

	/* Methods */
	public:
		/* Return true si le joueur est sur une pacgomme ou energizer */
		bool onElement(std::vector<SDL_Rect> &pac, Stats &statsPac,
			int element);

		void checkPostion(
			std::vector<SDL_Rect> &dots,
			std::vector<SDL_Rect> &energizers,
			Stats &statsPac,
			Ghost &ghost);

		void checkGhost(Ghost &ghost);
};

#endif