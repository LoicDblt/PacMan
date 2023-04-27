#include "ghost.h"

Ghost::~Ghost() {};

Ghost::Ghost(
	SDL_Rect entityRect,
	SDL_Rect entityPicture,
	float speed,
	Direction direction,
	Direction wishDirection,
	int healthPoints,
	State status,
	Name name
):
	Person{
		entityRect,
		entityPicture,
		speed,
		direction,
		wishDirection,
		healthPoints
	},
	name_{name},
	status_{status},
	previousPosition_{entityRect}
{};

void Ghost::aleaMove(
	std::vector<SDL_Rect> &walls,
	std::vector<SDL_Rect> &tunnels
) {
	std::list<Direction> validDirection;
	intersectionDirection(walls, validDirection);

	// Si à une intersection de 3 chemins minimum
	int size = validDirection.size();
	auto iterList = validDirection.begin();

	if(size >= 3) {
		int nb = aleaRand(1,size);
		std::advance(iterList, nb);
		setWishDirection(*iterList);
	}

	// Si bloqué cherche une autre direction
	if(roundCmpt_ == 2){
		int nb = aleaRand(1,4);
		switch (nb)
		{
		case 1:
			setWishDirection(UP);
			break;
		case 2:
			setWishDirection(DOWN);
			break;
		case 3:
			setWishDirection(RIGHT);
			break;
		case 4:
			setWishDirection(LEFT);
			break;
		default:
			break;
		}
		roundCmpt_ = 0;
	}else if (SDL_RectEquals(&previousPosition_, &entityRect_) == SDL_TRUE) {
		roundCmpt_++;
	}
	previousPosition_ = entityRect_;
	move(walls, tunnels);
}

int Ghost::aleaRand(int x, int y)
{
	std::random_device rd; 		// nb alea du hardware
	std::mt19937 gen(rd()); 	// génére une seed
	std::uniform_int_distribution<> distr(x,y);		// défini l'intervalle

	return distr(gen);
}

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

void Ghost::eated() {
	this->setStatus(WAIT);
	this->setWishDirection(UP);

	switch (this->getName()) {
		case BLINKY:
			this->setEntityRect(Coordinate::ghost_red_default_pos);

			this->setAnimation(
				Coordinate::ghost_red_l,
				Coordinate::ghost_red_r,
				Coordinate::ghost_red_u,
				Coordinate::ghost_red_d
			);

			break;
		// case PINKY:
		// 	this->entityRect_.x = 36;
		// 	this->entityRect_.y = 136;
		// 	break;
		// case INKY:
		// 	this->entityRect_.x = 36;
		// 	this->entityRect_.y = 136;
		// 	break;
		// case CLYDE:
		// 	this->entityRect_.x = 36;
		// 	this->entityRect_.y = 136;
		// 	break;
		default:
			break;
	}
}