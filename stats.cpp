#include "stats.h"

Stats::Stats(
	int dots,
	int energizers,
	int score
):
	dots_{dots},
	energizers_{energizers},
	score_{score}
{}

Stats::~Stats() {}

void Stats::updateScore(int earnedPoints) {
	switch (earnedPoints) {
		case DOT:
			this->addDot();
			break;

		case ENERGIZER:
			this->addEnergizer();
			break;

		case GHOST:
			this->addGhost();
			break;

		default:
			break;
	}
}

void Stats::checkWon(void) {
	if (this->getDots() == 189) {
		std::cout << "You win!" << std::endl;
		writeScore();
	}
}

void Stats::writeScore(void) {
	std::ofstream scoresFile(Stats::SCORES_FILE, std::ios_base::app);
	if (scoresFile.is_open()) {
			scoresFile << this->getScore() << std::endl;
		scoresFile.close();
	}
}

std::vector<unsigned int> Stats::readScores(int numberOfScores) {
	std::vector<unsigned int> scores;
	std::ifstream file(Stats::SCORES_FILE);
	int numberOfLines = 0;

	// Récupère toutes les valeurs du fichier
	if (file.good()) {
		std::string line;
		while (std::getline(file, line)) {
			numberOfLines++;
			try {
				scores.push_back(std::stoi(line));
			} catch (std::invalid_argument) {
				std::cerr << "Invalid format in " + Stats::SCORES_FILE
					<< std::endl;
			}
		}
	}

	std::sort(scores.begin(), scores.end(), std::greater<unsigned int>());

	if (numberOfScores > numberOfLines)
		numberOfScores = numberOfLines;

	std::vector<unsigned int> nHighest =
		std::vector<unsigned int>(scores.begin(), scores.begin() +
		numberOfScores);

	return nHighest;
}

std::vector<int> Stats::uncomposeNumber(int number) {
	std::vector<int> digits;
	while (number > 0) {
		digits.push_back(number % 10);
		number /= 10;
	}
	return digits;
}