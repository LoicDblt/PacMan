#ifndef PERSON_H
#define PERSON_H

#include <cstdlib>
#include <iostream>

#include "entity.h"

class Person : public Entity {
	public:
		enum Direction {UP, DOWN, RIGHT, LEFT, NONE};

	private:
		float x;
		float y;
		float speed_;
		Direction direction_;
		Direction wishDirection_;
		int pointsDeVie_;
		int tryToTurnCmp_{50};

	/* Constructors */
	public:
		Person() = default;
		Person(
			float speed,
			enum Direction direction
		);
		Person(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			int pointsDeVie
		);
		~Person();

	private:
		bool checkWalls(std::vector<SDL_Rect> &walls);
		bool checkDirection(std::vector<SDL_Rect> &walls, Direction direction);

	public:
		void move(std::vector<SDL_Rect>& walls);
		bool ghostBehavior(std::vector<SDL_Rect> &walls);

	/* Getter */
	public:
		inline Direction getDirection() const {
			return direction_;
		}

		inline int getPointsDeVie() const {
			return pointsDeVie_;
		}

	/* Setter */
	public:
		inline void setDirection(Direction direction) {
			direction_ = direction;
		}

		inline void setWishDirection(Direction wishDirection) {
			wishDirection_ = wishDirection;
		}

		inline void pertePointDeVie(void) {
			pointsDeVie_ -= 1;
		}
};

#endif