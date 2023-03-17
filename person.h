#ifndef PERSON_H
#define PERSON_H

#include "entity.h"

#include <iostream>

class Person : public Entity {
	public:
		enum Direction {UP, DOWN, RIGHT, LEFT};

	private:
		float x;
		float y;
		float speed_;
		Direction direction_;

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
			Direction direction
		);
		~Person();
};

#endif