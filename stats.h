#ifndef STATS_H
#define STATS_H

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL.h>

class Stats {
	/* Points */
	public:
		static const int DOT{10};
		static const int ENERGIZER{50};
		static const int CHERRY{100};
		static const int GHOST{200};

	public:
		inline static const std::string SCORES_FILE{"scores.txt"};

	private:
		int dots_{0};
		int energizers_{0};
		int score_{0};
		int ghostsEaten_{0};

	/* Constructors */
	public:
		Stats() = default;
		Stats(
			int dots,
			int energizers,
			int score
		);
		~Stats();


	/* Getters */
	public:
		inline int getDots() const {
			return dots_;
		}
		inline int getEnergizers() const {
			return energizers_;
		}
		inline int getScore() const {
			return score_;
		}
		inline int getGhostsEaten() const {
			return ghostsEaten_;
		}


	/* Setters */
	private:
		inline void addDot(void) {
			dots_++;
			score_ += DOT;

			checkWon();
		}

		inline void addEnergizer(void) {
			energizers_++;
			score_ += ENERGIZER;
		}

	public:
		inline void addGhost(void) {
			score_ += pow(GHOST, this->getGhostsEaten());
		}

		inline void addGhostsEaten(void) {
			ghostsEaten_++;
			if (this->getGhostsEaten() > 4)
				std::cerr << "Error: ghostsEaten_ > 4" << std::endl;
		}

		inline void resetGhostsEaten(void) {
			ghostsEaten_ = 0;
		}


	/* Methods */
	public:
		/**
		 * @brief Update the score according to the type of what have been eaten
		 *
		 * @param earnedPoints number of points earned
		 */
		void updateScore(int earnedPoints);

		/**
		 * @brief Write the score in the scores file
		 */
		void writeScore(void);

		/**
		 * @brief Read the scores file and return a vector of the "n" highest
		 * 		  scores
		 *
		 * @param numberOfScores number of scores to return
		 * @return std::vector<unsigned int> vector which contains "n" highest
		 * 		   scores
		 */
		static std::vector<unsigned int> readScores(int numberOfScores);

		/**
		 * @brief Uncompose a number into its digits
		 *
		 * @param number number to uncompose
		 * @return std::vector<int> vector of digits
		 */
		static std::vector<int> uncomposeNumber(int number);

	private:
		/**
		 * @brief Check if the player has won the game
		 */
		void checkWon(void);
};

#endif