#include "entity.h"

Entity::Entity(
	float x,
	float y,
	float width,
	float height,
	SDL_Rect entityPicture
):
	x_{x},
	y_{y},
	width_{width},
	heigh_{height},
	entityPicture_{entityPicture}
{};

Entity::Entity(const Entity& other):
	x_{other.x_},
	y_{other.y_},
	width_{other.width_},
	heigh_{other.heigh_},
	entityPicture_{other.entityPicture_}
{};

Entity::~Entity() {};