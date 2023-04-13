#include "person.h"

Person::Person(
	SDL_Rect entityRect,
	SDL_Rect entityPicture,
	float speed,
	Direction direction,
	int pointsDeVie
):
	Entity{entityRect, entityPicture},
	speed_{speed},
	direction_{direction},
	pointsDeVie_{pointsDeVie}
{};

Person::~Person() {};

void Person::move(std::vector<SDL_Rect>& walls) {
	if(tryToTurnCmp_ != 60) {
		if (checkDirection(walls, wishDirection_)) {
			tryToTurnCmp_ = 0;
			direction_ = wishDirection_;
		}
		else
			tryToTurnCmp_--;
	}
	
	switch (direction_) {
		case NONE:
			break;

		case UP:
			this->entityRect_.y -= speed_;
			if(checkWalls(walls))
				this->entityRect_.y += speed_;
			break;

		case DOWN:
			this->entityRect_.y += speed_;
			if(checkWalls(walls))
				this->entityRect_.y -= speed_;
			break;

		case RIGHT:
			this->entityRect_.x += speed_;
			if(checkWalls(walls))
				this->entityRect_.x -= speed_;
			break;

		case LEFT:
			this->entityRect_.x -= speed_;
			if(checkWalls(walls))
				this->entityRect_.x += speed_;
			break;

		default:
			std::cerr << "Person Direction UNKNOW" << SDL_GetError()
				<< std::endl;
			break;
	}
};

/**
 * Wall detection
 * Si le personnage rencontre un mur il renvoie true
 * cela empêchera d'aller dans cette direction
 * */ 
bool Person::checkWalls(std::vector<SDL_Rect> &walls) {
	for(int i=0; i<walls.size();i++) {
		if(SDL_HasIntersection(&this->getEntityRect(), &walls[i]))
			return true;
	}
	return false;
};

/**
 * Return true if direction is free
*/
bool Person::checkDirection(std::vector<SDL_Rect> &walls, Direction direction)
{
	bool res = true;

	switch (direction) {
		case NONE:
			break;

		case UP:
			this->entityRect_.y -= speed_;
			if(checkWalls(walls))
				res = false;
			this->entityRect_.y += speed_;
			break;

		case DOWN:
			this->entityRect_.y += speed_;
			if(checkWalls(walls))
				res = false;
			this->entityRect_.y -= speed_;
			break;

		case RIGHT:
			this->entityRect_.x += speed_;
			if(checkWalls(walls))
				res = false;
			this->entityRect_.x -= speed_;
			break;

		case LEFT:
			this->entityRect_.x -= speed_;
			if(checkWalls(walls))
				res = false;
			this->entityRect_.x += speed_;
			break;

		default:
			std::cerr << "Person Direction UNKNOW" << SDL_GetError()
				<< std::endl;
			break;
	}

	return res;
};