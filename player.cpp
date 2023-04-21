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
)
{
	onElement(dots,statsPac,Stats::DOT);
	onElement(energizers,statsPac,Stats::ENERGIZER);
}