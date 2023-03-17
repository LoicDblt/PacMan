#ifndef PERSON_H
#define PERSON_H

#include "entity.h"

class Person : public Entity
{
	enum Direction {UP, DOWN, RIGHT, LEFT};

	private:
		float speed_;
		Direction direction_;

	public:
		Person();
		Person(
			float speed,
			enum Direction direction
		);
		Person(
			float x,
			float y,
			float width,
			float heigh,
			EntityPicture entityPicture,
			float speed,
			Direction direction
		);
		~Person();
};

#endif