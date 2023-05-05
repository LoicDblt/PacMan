#include "entity.hpp"

Entity::Entity(
	SDL_Rect entityRect,
	SDL_Rect entityPicture
):
	entityRect_{entityRect},
	entityPicture_{entityPicture}
{}