#include "player.h"

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
		healthPoints,
		true
	}
{};

bool Player::onElement(
	std::vector<SDL_Rect> &pac,
	Stats &statsPac,
	int element
) {
	for (int i = 0; i < pac.size(); i++) {
		if (SDL_HasIntersection(&this->getEntityRect(), &pac[i])){
			pac.erase(pac.begin() + i);
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
	std::vector<Ghost> &ghosts
) {
	onElement(dots, statsPac, Stats::DOT);
	if (onElement(energizers, statsPac, Stats::ENERGIZER)) {
		this->setSlayerTime(PELLET_TIME);
		for (int i = 0; i < ghosts.size(); i++) {
			if (ghosts[i].getStatus() != Ghost::HUNTER)
				continue;
			ghosts[i].setStatus(Ghost::PREY);
			ghosts[i].setAnimation(
				Coordinate::ghost_afraid_blue,
				Coordinate::ghost_afraid_blue,
				Coordinate::ghost_afraid_blue,
				Coordinate::ghost_afraid_blue
			);
		}
	}
}

void Player::checkGhost(std::vector<Ghost> &ghosts, Stats &statsPac) {
	for (int i = 0; i < ghosts.size(); i++) {
		if (
			SDL_HasIntersection(
				&this->getEntityRect(), &ghosts[i].getEntityRect())
		) {
			if (ghosts[i].getStatus() == Ghost::PREY) {
				statsPac.addGhostsEaten();
				statsPac.updateScore(Stats::GHOST);
				ghosts[i].eated();
			}

			else {
				this->lostLive();

				if (this->getLives() == 0) {
					puts("PacMan est mort !");
					exit(0); // Gérer la fin du jeu <=========================== TODO
				}

				// Reset PacMan à sa position d'origine
				this->setEntityRect(Coordinate::pac_default_pos);
				this->setEntityPic(Coordinate::pac_b[0]);
				this->setDirection(Person::NONE);
				this->setWishDirection(Person::NONE);
			}
		}
	}
}

void Player::checkPelletActive(std::vector<Ghost>  &ghosts, Stats &statsPac) {
	if (this->getSlayerTime() > 0)
		this->setSlayerTime(-1);
	
	else {
		for (int i = 0; i < ghosts.size(); i++) {
			if (ghosts[i].getStatus() == Ghost::PREY) {
				statsPac.resetGhostsEaten();
				ghosts[i].resetStatus();
			}
		}
	}
}