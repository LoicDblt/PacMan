#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <vector>
#include <SDL.h>

class Stats {
	private:
		int dots_{0};
		int energizers_{0};
		int ghosts_{0};
		int score_{0};

	/* Points */
	public:
		#define DOT			10
		#define ENERGIZER	50
		#define CHERRY		100
		#define GHOST		200

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

			if (isWon())
				std::cout << "You win!" << std::endl;
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
		bool isWon(void);

	public:
		void updateScore(int earnedPoints);
		void updateScore(int earnedPoints, int eatenGhosts);
};

#endif