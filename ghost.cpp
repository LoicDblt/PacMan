#include "ghost.h"

Ghost::~Ghost() {};

Ghost::Ghost(
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

void Ghost::goCoordinate(int x, int y)
{
	int selfX = this->entityRect_.x;
	int selfY = this->entityRect_.y;
	if(x > selfX){
		this->setDirection(RIGHT);
	}else if(x < selfX){
		this->setDirection(LEFT);
	}
}