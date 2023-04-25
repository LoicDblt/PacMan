#ifndef PERSON_H
#define PERSON_H

#include <cstdlib>
#include <iostream>
#include <list>

#include "entity.h"

class Person : public Entity {
	public:
		enum Direction {UP, DOWN, RIGHT, LEFT, NONE};
		enum CaracterType {PACMAN, GRED, GPINK, GBLUE, GORANGE};

	private:
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
			Direction wishDirection,
			int pointsDeVie
		);
		~Person();

	/* Methods */
	private:
		bool checkWalls(std::vector<SDL_Rect> &walls, SDL_Rect &entity);

	protected:
		/* TRUE if direction available */
		bool checkDirection(std::vector<SDL_Rect> &walls, Direction direction);
		/* Intersection Direction */
		void intersectionDirection(std::vector<SDL_Rect> &walls, std::list<Direction> &validDirection);


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