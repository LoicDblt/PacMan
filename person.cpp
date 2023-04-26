#include "person.h"

Person::Person(
	SDL_Rect entityRect,
	SDL_Rect entityPicture,
	float speed,
	Direction direction,
	Direction wishDirection,
	int healthPoints
):
	Entity{entityRect, entityPicture},
	speed_{speed},
	direction_{direction},
	wishDirection_{wishDirection},
	healthPoints_{healthPoints}
{};

Person::Person(
	SDL_Rect entityRect,
	SDL_Rect entityPicture,
	float speed,
	Direction direction,
	Direction wishDirection,
	int healthPoints,
	std::vector<SDL_Rect> up,
	std::vector<SDL_Rect> down,
	std::vector<SDL_Rect> left,
	std::vector<SDL_Rect> right
):
	Entity{entityRect, entityPicture},
	speed_{speed},
	direction_{direction},
	wishDirection_{wishDirection},
	healthPoints_{healthPoints},
	up_{up},
	down_{down},
	left_{left},
	right_{right}	
{};

Person::~Person() {};

void Person::move(
	std::vector<SDL_Rect>& walls,
	std::vector<SDL_Rect>& tunnels
) {
	if (tryToTurnCmp_ != 60) {
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
			if (checkWalls(walls, this->entityRect_))
				this->entityRect_.y += speed_;
			break;

		case DOWN:
			this->entityRect_.y += speed_;
			if (checkWalls(walls, this->entityRect_))
				this->entityRect_.y -= speed_;
			break;

		case RIGHT:
			this->entityRect_.x += speed_;

			if (checkWalls(tunnels, this->getEntityRect()))
				this->entityRect_.x = tunnels[0].x + tunnels[0].w;

			if (checkWalls(walls, this->entityRect_))
				this->entityRect_.x -= speed_;
			break;

		case LEFT:
			this->entityRect_.x -= speed_;

			if (checkWalls(tunnels, this->getEntityRect())) {
				this->entityRect_.x = tunnels[1].x - (tunnels[1].w +
					this->entityRect_.w);
			}

			if (checkWalls(walls, this->entityRect_))
				this->entityRect_.x += speed_;
			break;

		default:
			break;
	}
};

/**
 * Wall detection
 * Si le personnage rencontre un mur il renvoie true
 * cela empêchera d'aller dans cette direction
 * */
bool Person::checkWalls(std::vector<SDL_Rect> &walls,SDL_Rect &entity) 
{
	for (int i=0; i<walls.size();i++) {
		if (SDL_HasIntersection(&entity, &walls[i]))
			return true;
	}
	return false;
};

/**
 * Effectue les différentes animations
*/
void Person::animation(int count) 
{
	if(count%5 == 0) {
		if(tmpAnimation_ == 1)
			tmpAnimation_ = 0;
		else
			tmpAnimation_ = 1;
	}
	
	switch (direction_)
	{
	case RIGHT:
		this->setEntityPic(right_[tmpAnimation_]);
		break;
	case LEFT:
		this->setEntityPic(left_[tmpAnimation_]);
		break;
	case DOWN:
		this->setEntityPic(down_[tmpAnimation_]);
		break;
	case UP:
		this->setEntityPic(up_[tmpAnimation_]);
		break;
	default:
		break;
	}
}

/**
 * Return true if direction is free
*/
bool Person::checkDirection(std::vector<SDL_Rect> &walls, Direction direction) 
{
	bool res = true;
	SDL_Rect tmpRect{
		this->entityRect_.x,
		this->entityRect_.y,
		this->entityRect_.w,
		this->entityRect_.h,
	};

	switch (direction) {
		case NONE:
			break;

		case UP:
			tmpRect.y -= speed_+2;
			if (checkWalls(walls, tmpRect))
				res = false;
			break;

		case DOWN:
			tmpRect.y += speed_+2;
			if (checkWalls(walls, tmpRect))
				res = false;
			break;

		case RIGHT:
			tmpRect.x += speed_+2;
			if (checkWalls(walls, tmpRect))
				res = false;
			break;

		case LEFT:
			tmpRect.x -= speed_+2;
			if (checkWalls(walls, tmpRect))
				res = false;
			break;

		default:
			std::cerr << "Person Direction UNKNOW" << SDL_GetError()
				<< std::endl;
			break;
	}

	return res;
};

/**
 * Return a list of valid direction
*/
void Person::intersectionDirection(
	std::vector<SDL_Rect> &walls,
	std::list<Direction> &validDirection
) {
	// Chech if the direction is available
	if (checkDirection(walls, Person::UP))
		validDirection.push_front(Person::UP);

	if (checkDirection(walls, Person::DOWN))
		validDirection.push_front(Person::DOWN);

	if (checkDirection(walls, Person::LEFT))
		validDirection.push_front(Person::LEFT);

	if (checkDirection(walls, Person::RIGHT))
		validDirection.push_front(Person::LEFT);
}
