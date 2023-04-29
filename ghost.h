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
		 * Wait : attend de sortir du spawn
		 */
		enum State {HUNTER, PREY, WAIT};
		enum Name {BLINKY, PINKY, INKY, CLYDE};

	private:
		SDL_Rect previousPosition_;

		// Direction de laquelle on vient
		Direction previousDirection_;

		// Compte le nombre de tours de boucle pour la même position
		int roundCmpt_{0};

		// Etat du fantôme
		State status_{WAIT};
		bool outSpawn_{false};
		Name name_;


	/* Constructors */
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
			Name name,
			bool outSpawn
		);


	/* Getters */
	public:
		inline State getStatus(void) const {
			return status_;
		}

		inline Name getName(void) const {
			return name_;
		}


	/* Setters */
	public:
		inline void setStatus(State status) {
			status_ = status;
		}


	/* Methods */
	public:
		/**
		 * @brief Déplace le fantôme aléatoire sur la carte
		 *
		 * @param walls les murs présents sur la carte
		 * @param tunnels les tunnels présents sur la carte
		 */
		void aleaMove(
			std::vector<SDL_Rect> &walls,
			std::vector<SDL_Rect> &tunnels
		);

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

		/**
		 * @brief Active le fantôme en lui changeant le status au bout d'un
		 * 		  certain temps
		 * 
		 */
		static void enableGhost(std::vector<Ghost> &ghosts, int count);

	private:
		/**
		 * @brief Retourne un nombre aléatoire entre x et y
		 *
		 * @param x borne basse
		 * @param y borne haute
		 * @return int le nombre aléatoire
		 */
		int aleaRand(int x , int y);

		/**
		 * @brief [TODO] Permet d'aller à des coordonnées donnée
		 * 
		 * @param x abscisse
		 * @param y ordonnée
		 */
		void goCoordinate(int x, int y);
};

#endif