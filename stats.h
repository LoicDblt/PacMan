#ifndef STATS_H
#define STATS_H

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL.h>

class Stats {
	private:
		int dots_{0};
		int energizers_{0};
		int ghosts_{0};
		int score_{0};

	/* Points */
	public:
		static const int DOT{10};
		static const int ENERGIZER{50};
		static const int CHERRY{100};
		static const int GHOST{200};
	
	public:
		inline static const std::string SCORES_FILE{"scores.txt"};

	/* Constructors */
	public:
		// Default constructor
		Stats() = default;
		Stats(
			int dots,
			int energizers,
			int ghosts,
			int score
		);

		~Stats();

	/* Getter */
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

	/* Setter */
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

		inline void addGhost(int eatenGhosts) {
			ghosts_++;
			score_ += GHOST * eatenGhosts;
		}

	private:
		void checkWon(void);

	public:
		void updateScore(int earnedPoints);
		void updateScore(int earnedPoints, int eatenGhosts);
		void writeScore(void);
		static std::vector<unsigned int> readScores(int numberOfScores);
		static std::vector<int> uncomposeNumber(int number);
};

#endif