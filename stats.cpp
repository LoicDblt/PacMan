#include "stats.h"

Stats::Stats(
	int dots,
	int energizers,
	int ghosts,
	int score
):
	dots_{dots},
	energizers_{energizers},
	ghosts_{ghosts},
	score_{score}
{};

Stats::~Stats() {};

/**
 * @brief Update the score according to the type of what have been eaten
 * 
 * @param earnedPoints number of points earned
 */
void Stats::updateScore(int earnedPoints) {
	switch (earnedPoints) {
		case DOT:
			this->addDot();
			break;

		case ENERGIZER:
			this->addEnergizer();
			break;

		default:
			break;
	}
};

/**
 * @brief Update the score according to the type of what have been eaten, but
 * take in account the number of ghosts eaten in the span of the "power pellet
 * mode"
 * 
 * @param earnedPoints number of points earned
 * @param eatenGhosts number of ghosts eaten in the span of the "power pellet
 * 					  mode"
 */
void Stats::updateScore(int earnedPoints, int eatenGhosts) {
	switch (earnedPoints) {
		case GHOST:
			this->addGhost(eatenGhosts);
			break;

		default:
			std::cerr << "This function is specific to ghosts" << std::endl;
			break;
	}
};

/**
 * @brief Check if the player has won the game
 */
bool Stats::isWon(void) {
	if (this->getDots() == 189)
		return true;
	return false;
};