#ifndef PERSON_H
#define PERSON_H

#include "entity.h"

#include <iostream>

class Person : public Entity {
	public:
		enum Direction {UP, DOWN, RIGHT, LEFT, NONE};

	private:
		float x;
		float y;
		float speed_;
		Direction direction_;
		int pointsDeVie_;

	/* Constructors */
	public:
		Person() = default;
		Person(
			float speed,
			enum Direction direction
		);
		Person(
			float x,
			float y,
			float width,
			float heigh,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			int pointsDeVie
		);
		~Person();

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

		inline void pertePointDeVie(void) {
			pointsDeVie_ -= 1;
		}
};

#endif