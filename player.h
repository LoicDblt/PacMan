#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"
#include "ghost.h"
#include "interface.h"
#include "person.h"
#include "stats.h"

class Player : public Person {
	/* Variables et constantes */
	public:
		/**
		 * 10 seconde = 10000ms
		 * 10000/16 = 625
		 * 16 = durée d'attente de SDL_Delay = 1 tour de boucle
		 */
		static const int TIMER_PELLET{625};
		static const int PAC_HEALTH{3};

	private:
		int pelletTime_{0};


	/* Constructeurs et destructeur */
	public:
		Player() = default;
		~Player();
		Player(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			Direction wishDirection,
			int healthPoints
		);


	/* Getters */
	public:
		inline int getPelletTime(void) const {
			return pelletTime_;
		}


	/* Setters */
	public:
		inline void setPelletTime(int pelletTime) {
			pelletTime_ += pelletTime;
		}


	/* Méthodes */
	public:
		/**
		 * @brief Vérifie si le joueur est sur un élément
		 *
		 * @param pac pacman
		 * @param statsPac les stats à mettre à jour en fonction des points
		 * @param element pacgommes ou super pacgommes
		 * @return true si le joueur est sur un élément
		 * @return false si le joueur n'est pas sur un élément
		 */
		bool onElement(
			std::vector<SDL_Rect> &pac,
			Stats &statsPac,
			int element
		);

		/**
		 * @brief Vérifie si le joueur est sur un dot ou un energizer
		 *
		 * @param dots les pacgommes
		 * @param energizers les super pacgommes
		 * @param statsPac les stats à mettre à jour en fonction des points
		 * @param ghosts à passer en mode apeuré
		 */
		void checkPostion(
			std::vector<SDL_Rect> &dots,
			std::vector<SDL_Rect> &energizers,
			Stats &statsPac,
			std::vector<Ghost> &ghosts
		);

		/**
		 * @brief Vérifie si le joueur est sur un fantôme
		 *
		 * @param ghosts à vérifier et à renvoyer au spawn si en mode apeuré
		 * @param statsPac à mettre à jour en fonction des points
		 * @param interface afficher l'écran de titre si plus de vie
		 */
		void checkGhost(
			std::vector<Ghost> &ghosts,
			Stats &statsPac,
			Interface &interface
		);

		/**
		 * @brief Vérifie si le joueur est encore en mode "pellet"
		 *
		 * @param ghost à reset si fin du mode "pellet"
		 * @param statsPac à reset si fin du mode "pelelet" (pour le coeff) de
		 * 				   ghosts tués pendant la période
		 */
		void checkPelletActive(std::vector<Ghost> &ghost, Stats &statsPac);

		/**
		 * @brief Vérifie si le joueur est mort
		 *
		 * @param statsPac pour écrire le score
		 * @param interface afficher l'écran de titre si plus de vie
		 * @return true si le joueur est mort
		 * @return false si le joueur n'est pas mort
		 */
		bool isDead(Stats &statsPac, Interface &interface);
};

#endif