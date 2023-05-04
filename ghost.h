#ifndef GHOST_H
#define GHOST_H

#include <random>

#include "coordinate.h"
#include "person.h"

class Ghost : public Person {
	/* Variables et constantes */
	public:
		/**
		 * Etats possibles pour les fantômes
		 * HUNTER : chasse pacman
		 * PREY : fuit pacman
		 * WAIT : attend de sortir du spawn
		 */
		enum State {HUNTER, PREY, WAIT};
		enum Name {BLINKY, PINKY, INKY, CLYDE};
		static const int TIMER_DEAD = 312;
		static const int TIMER_PINK = 312;
		static const int TIMER_BLUE = 624;
		static const int TIMER_ORANGE = 936;

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
		int timerSpawn_{0};


	/* Constructeurs et destructeur */
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
			bool outSpawn,
			int timerSpawn
		);


	/* Getters */
	public:
		inline State getStatus(void) const {
			return status_;
		}

		inline Name getName(void) const {
			return name_;
		}

		inline int getTimerSpawn(void) const {
			return timerSpawn_;
		}


	/* Setters */
	public:
		inline void setStatus(State status) {
			status_ = status;
		}

		inline void setTimerSpawn(int timerSpawn) {
			timerSpawn_ = timerSpawn;
		}

		inline void decrementTimerSpawn(void) {
			timerSpawn_--;
		}

		inline void setOutSpawn(bool inOrOut) {
			outSpawn_ = inOrOut;
		}


	/* Méthodes */
	public:
		/**
		 * @brief Centre la sortie des fantômes dans le spawn
		 *
		 * @param walls les murs présents sur la carte
		 * @param tunnels les tunnels présents sur la carte
		 */
		void moveOutOfSpawn(
			std::vector<SDL_Rect> &walls,
			std::vector<SDL_Rect> &tunnels
		);

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
		 * @brief Active le fantôme en lui changeant le status lorsque son
		 * 		  timer est à 0
		 *
		 */
		void enableGhost(void);

	private:
		/**
		 * @brief Retourne un nombre aléatoire entre x et y
		 *
		 * @param x borne basse
		 * @param y borne haute
		 * @return int le nombre aléatoire
		 */
		int aleaRand(int x, int y);

		/**
		 * @brief [TODO] Permet d'aller à des coordonnées donnée
		 *
		 * @param x abscisse
		 * @param y ordonnée
		 */
		void goCoordinate(int x, int y);

		/**
		 * @brief Force la sortie du spawn en mettant wishDirection à UP
		*/
		void moveOutOfSpawn(void);

		/**
		 * @brief Retourne la direction opposée à celle donnée
		 *
		 * @param direction à inverser
		 * @return Person::Direction
		 */
		Person::Direction oppositeDirection(Direction direction);
};

#endif