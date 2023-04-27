#ifndef GHOST_H
#define GHOST_H

#include <random>

#include "coordinate.h"
#include "person.h"

class Ghost : public Person {
	public:
		/**
		 * Etats possibles pour les fantômes
		 * Hunter : chasse pacman
		 * Prey : fuit pacman
		 * Dead : mort
		 * Wait : attend de sortir du spawn
		 */
		enum State {HUNTER, PREY, DEAD, WAIT};
		enum Name {BLINKY, PINKY, INKY, CLYDE};

	private:
		SDL_Rect previousPosition_;

		// Direction de laquelle on vient
		Direction previousDirection_;

		// Compte le nombre de tours de boucle pour la même position
		int roundCmpt_{0};

		// Etat du fantôme
		State status_{WAIT};
		Name name_;

	public:
		Ghost() = default;
		~Ghost();
		Ghost(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			Direction wishDirection,
			int healthPoints,
			State status,
			Name name
		);

	/* Getters */
	public:
		inline void setStatus(State status) {
			status_ = status;
		}

		inline Name getName(void) const {
			return name_;
		}

	/* Setters */
	public:
		inline State getStatus(void) const {
			return status_;
		}

	/* Methods */
	public:
		/**
		 * @brief Déplace le fantôme aléatoire sur la carte
		 *
		 * @param walls les murs présents sur la carte
		 * @param tunnels les tunnels présents sur la carte
		 */
		void aleaMove(std::vector<SDL_Rect> &walls,
			std::vector<SDL_Rect> &tunnels);

		/**
		 * @brief Replace le fantôme à sa position initiale s'il a été mangé
		 *
		 */
		void eated(void);

		/**
		 * @brief Replace le fantôme à sa position initiale à la fin de la
		 * 		  période de power pellet
		 *
		 */
		void resetStatus(void);

	private:
		/**
		 * @brief Retourne un nombre aléatoire entre x et y
		 *
		 * @param x borne basse
		 * @param y borne haute
		 * @return int le nombre aléatoire
		 */
		int aleaRand(int x , int y);

		/* TODO, go to a precise direction */
		void goCoordinate(int x, int y);
};

#endif