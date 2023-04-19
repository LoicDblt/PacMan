#include "player.h"

Player::~Player() {};

Player::Player(
	SDL_Rect entityRect,
	SDL_Rect entityPicture,
	float speed,
	Direction direction,
	Direction wishDirection,
	int pointsDeVie
):
    Person{
        entityRect, 
		entityPicture,
        speed,
        direction,
		wishDirection,
        pointsDeVie
    }
{};