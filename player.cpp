#include "player.h"

/**
 * Constructor and Destructor
*/
Player::~Player() {};

Player::Player(
	SDL_Rect entityRect,
	SDL_Rect entityPicture,
	float speed,
	Direction direction,
	Direction wishDirection,
	int healthPoints
):
	Person{
		entityRect,
		entityPicture,
		speed,
		direction,
		wishDirection,
		healthPoints
	}
{};

/**
 * Methods
*/
bool Player::onElement(std::vector<SDL_Rect> &pac, Stats &statsPac, int element)
{
	for (int i=0; i<pac.size(); i++) {
		if(SDL_HasIntersection(&this->getEntityRect(), &pac[i])){
			pac.erase(pac.begin()+i);
			statsPac.updateScore(element);
			return true;
		}
	}

	return false;
}

void Player::checkPostion(
	std::vector<SDL_Rect> &dots, 
	std::vector<SDL_Rect> &energizers, 
	Stats &statsPac
) {
	onElement(dots,statsPac,Stats::DOT);
	onElement(energizers,statsPac,Stats::ENERGIZER);
}

void Player::checkGhost(Ghost ghost) {
	if (SDL_HasIntersection(&this->getEntityRect(), &ghost.getEntityRect())) {
		this->lostLive();

		if (this->getLives() == 0) {
			puts("PacMan est mort !");
			exit(0);
		}
		else
			printf("Il reste %d vies à PacMan\n", this->getLives());

		// Reset PacMan à sa position d'origine
		this->entityRect_.x = 324;
		this->entityRect_.y = 744;
		this->setEntityPic(Coordinate::pac_b[0]);
		this->setDirection(Person::NONE);
		this->setWishDirection(Person::NONE);
	}
}