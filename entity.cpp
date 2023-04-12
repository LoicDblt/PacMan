#include "entity.h"

Entity::Entity(
	SDL_Rect entityRect,
	SDL_Rect entityPicture
):
	entityRect_{entityRect},
	entityPicture_{entityPicture}
{};

Entity::Entity(const Entity& other):
	entityRect_{other.entityRect_},
	entityPicture_{other.entityPicture_}
{};

Entity::~Entity() {};