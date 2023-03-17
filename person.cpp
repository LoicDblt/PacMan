#include "person.h"

Person::Person(
	float x,
	float y,
	float width,
	float heigh,
	SDL_Rect entityPicture,
	float speed,
	Direction direction
):
	Entity{x, y, width, heigh, entityPicture},
	speed_{speed},
	direction_{direction}
{};

Person::~Person() {};