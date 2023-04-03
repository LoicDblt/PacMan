#include "person.h"

Person::Person(
	float x,
	float y,
	float width,
	float heigh,
	SDL_Rect entityPicture,
	float speed,
	Direction direction,
	int pointsDeVie
):
	Entity{x, y, width, heigh, entityPicture},
	speed_{speed},
	direction_{direction},
	pointsDeVie_{pointsDeVie}
{};

Person::~Person() {};