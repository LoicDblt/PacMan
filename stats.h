#ifndef STATS_H
#define STATS_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <SDL.h>
#include <vector>

class Stats {
	/* Variables et constantes */
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
		inline int getDots(void) const {
			return dots_;
		}
		inline int getEnergizers(void) const {
			return energizers_;
		}
		inline int getScore(void) const {
			return score_;
		}
		inline int getGhostsEaten(void) const {
			return ghostsEaten_;
		}


	/* Setters */
	private:
		inline void addDot(void) {
			dots_++;
			score_ += DOT;
		}

		inline void addEnergizer(void) {
			energizers_++;
			score_ += ENERGIZER;
		}


	/* Méthodes */
	public:
		inline void addGhost(void) {
			score_ += GHOST * pow(2, this->getGhostsEaten() - 1);
		}

		inline void addGhostsEaten(void) {
			ghostsEaten_++;
			if (this->getGhostsEaten() > 4)
				std::cerr << "Error: ghostsEaten_ > 4" << std::endl;
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
		 * @brief Décompose un nombre en un vecteur de chiffres
		 *
		 * @param number chiffre à décomposer
		 * @return std::vector<int> vecteur des chiffres composant le nombre
		 */
		static std::vector<int> uncomposeNumber(int number);

		/**
		 * @brief Ecrit le score dans le fichier des scores
		 */
		void writeScore(void);
};

#endif