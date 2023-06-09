#include "player.hpp"

Player::Player(
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
	Person{
		entityRect,
		entityPicture,
		speed,
		direction,
		wishDirection,
		healthPoints,
		true,
		up,
		down,
		left,
		right
	}
{}

/* Public */

Player Player::initPacMan(int healthPoints) {
	return Player{
		Coordinate::pacDefaultPos,
		Coordinate::pacB[0],
		2,
		Person::NONE,
		Person::NONE,
		healthPoints,
		Coordinate::pacU,
		Coordinate::pacD,
		Coordinate::pacL,
		Coordinate::pacR
	};
}

bool Player::onElement(
	std::vector<SDL_Rect> &element,
	Stats &statsPac,
	int score
) {
	for (int i{0}; i < element.size(); i++) {
		if (SDL_HasIntersection(&this->getEntityRect(), &element[i])) {
			element.erase(element.begin() + i);
			statsPac.updateScore(score);

			// Ajoute une vie tous les 10000 points
			if (
				statsPac.getScore() >
				(Stats::GIVE_LIFE * (this->getNbrHealthPointsEarned() + 1)) == 1
			) {
				this->setHelthPoints(this->getHelthPoints() + 1);
				this->addNbrHealthPointsEarned();
			}

			return true;
		}
	}

	return false;
}

void Player::checkPostion(
	std::vector<SDL_Rect> &dots,
	std::vector<SDL_Rect> &energizers,
	SDL_Rect &fruit,
	Stats &statsPac,
	std::vector<Ghost> &ghosts
) {
	// Pac-gommes
	onElement(dots, statsPac, Stats::DOT);

	// Fruits
	std::vector<SDL_Rect> buffFruit{fruit};
	if (onElement(buffFruit, statsPac, Stats::CHERRY))
		fruit = Coordinate::NONE_FRUIT;

	// Super pac-gommes
	if (onElement(energizers, statsPac, Stats::ENERGIZER)) {
		this->setPelletTime(TIMER_PELLET);

		for (int i{0}; i < ghosts.size(); i++) {
			ghosts[i].setStatus(Ghost::PREY);
			ghosts[i].setAnimation(
				Coordinate::ghostAfraidBlue,
				Coordinate::ghostAfraidBlue,
				Coordinate::ghostAfraidBlue,
				Coordinate::ghostAfraidBlue
			);
		}
	}
}

void Player::checkGhost(
	std::vector<Ghost> &ghosts,
	Stats &statsPac,
	Interface &interface
) {
	for (int i{0}; i < ghosts.size(); i++) {
		if (
			SDL_HasIntersection(
				&this->getEntityRect(),
				&ghosts[i].getEntityRect()
			)
		) {
			if (ghosts[i].getStatus() == Ghost::PREY) {
				statsPac.addGhostsEaten();
				statsPac.updateScore(Stats::GHOST);
				ghosts[i].eated();
			}

			else if (ghosts[i].getStatus() == Ghost::HUNTER) {
				this->lostHelthPoint();

				// Reset Pac-Man à sa position d'origine
				this->setEntityRect(Coordinate::pacDefaultPos);
				this->setEntityPic(Coordinate::pacB[0]);
				this->setDirection(Person::NONE);
				this->setWishDirection(Person::NONE);
			}
		}
	}
}

void Player::checkPelletActive(std::vector<Ghost> &ghosts, Stats &statsPac) {
	if (this->getPelletTime() > 0)
		this->setPelletTime(-1);

	else {
		for (int i{0}; i < ghosts.size(); i++) {
			if (ghosts[i].getStatus() == Ghost::PREY) {
				statsPac.resetGhostsEaten();
				ghosts[i].resetStatus();
			}
		}
	}
}

bool Player::isDead(Stats &statsPac, Interface &interface) {
	if (this->getHelthPoints() == 0) {
		statsPac.writeScore();

		return true;
	}

	return false;
}