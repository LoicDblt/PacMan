#ifndef STATS_H
#define STATS_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>

class Stats {
	/* Variables et constantes */
	public:
		inline static const std::string SCORES_FILE{"scores.txt"};

		static const int DOT{10};
		static const int ENERGIZER{50};
		static const int CHERRY{100};
		static const int GHOST{200};

		static const int GIVE_LIFE{10000};

	private:
		int dots_{0};
		int energizers_{0};
		int score_{0};
		int ghostsEaten_{0};


	/* Constructeurs et destructeur */
	public:
		Stats(void) = default;
		~Stats(void) = default;
		Stats(
			int dots,
			int energizers,
			int score
		);


	/* Getters */
	public:
		inline int getDotsEaten(void) const {
			return dots_;
		}

		inline int getEnergizersEaten(void) const {
			return energizers_;
		}

		inline int getGhostsEaten(void) const {
			return ghostsEaten_;
		}

		inline int getScore(void) const {
			return score_;
		}


	/* Méthodes */
	public:
		inline void addDotEatenScore(void) {
			dots_++;
			score_ += DOT;
		}

		inline void addEnergizerEatenScore(void) {
			energizers_++;
			score_ += ENERGIZER;
		}

		inline void addGhostScore(void) {
			score_ += GHOST * pow(2, this->getGhostsEaten() - 1);
		}

		inline void addCherryScore(void) {
			score_ += CHERRY;
		}

		inline void addGhostsEaten(void) {
			ghostsEaten_++;
			if (this->getGhostsEaten() > 4)
				std::cerr << "Error: ghostsEaten_ > 4" << std::endl;
		}

			inline void resetDotsEaten(void) {
			dots_ = 0;
		}
	
		inline void resetEnergizersEaten(void) {
			energizers_ = 0;
		}

		inline void resetGhostsEaten(void) {
			ghostsEaten_ = 0;
		}

	public:
		/**
		 * @brief Mets à jour le score en fonction du nombre de points gagnés
		 *
		 * @param earnedPoints nombre de points gagnés
		 */
		void updateScore(int earnedPoints);

		/**
		 * @brief Lit le fichier des scores et retourne un vecteur des "n"
		 * 		  valeurs les plus élevées
		 *
		 * @param numberOfScores nombre de scores à retourner
		 * @return std::vector<unsigned int> vecteur des "n" valeurs les plus
		 * 		   élevées
		 */
		static std::vector<unsigned int> readScores(int numberOfScores);

		/**
		 * @brief Ecrit le score dans le fichier des scores
		 */
		void writeScore(void);

		/**
		 * @brief Décompose un nombre en un vecteur de chiffres
		 *
		 * @param number chiffre à décomposer
		 * @return std::vector<int> vecteur des chiffres composant le nombre
		 */
		static std::vector<int> uncomposeNumber(int number);
};

#endif