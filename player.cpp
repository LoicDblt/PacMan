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
	Stats &statsPac,
	Ghost &ghost
) {
	onElement(dots,statsPac,Stats::DOT);
	if (onElement(energizers,statsPac,Stats::ENERGIZER)) {
		ghost.setStatus(Ghost::PREY);
		ghost.setAnimation(
			Coordinate::ghost_afraid_blue,
			Coordinate::ghost_afraid_blue,
			Coordinate::ghost_afraid_blue,
			Coordinate::ghost_afraid_blue
		);
	}
}

void Player::checkGhost(Ghost &ghost) {
	if (SDL_HasIntersection(&this->getEntityRect(), &ghost.getEntityRect())) {
		if (ghost.getStatus() == Ghost::PREY) {
			ghost.eated();
		}

		else {
			this->lostLive();

			if (this->getLives() == 0) {
				puts("PacMan est mort !");
				exit(0); // Gérer la fin du jeu <=============================== TODO
			}

			// Reset PacMan à sa position d'origine
			this->setEntityRect(Coordinate::pac_default_pos);
			this->setEntityPic(Coordinate::pac_b[0]);
			this->setDirection(Person::NONE);
			this->setWishDirection(Person::NONE);
		}
	}
}