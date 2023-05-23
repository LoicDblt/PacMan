#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.hpp"
#include "ghost.hpp"
#include "interface.hpp"
#include "person.hpp"
#include "stats.hpp"

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
		int nbrHealthPointsEarned_{0};


	/* Constructeurs et destructeur */
	public:
		Player(void) = default;
		~Player(void) = default;
		Player(
			SDL_Rect entityRect,
			SDL_Rect entityPicture,
			float speed,
			Direction direction,
			Direction wishDirection,
			int healthPoints,
			std::vector<SDL_Rect> up,
			std::vector<SDL_Rect> down,
			std::vector<SDL_Rect> left,
			std::vector<SDL_Rect> right
		);


	/* Getters */
	public:
		inline int getPelletTime(void) const {
			return pelletTime_;
		}

		inline int getNbrHealthPointsEarned(void) const {
			return nbrHealthPointsEarned_;
		}


	/* Setters */
	public:
		inline void setPelletTime(int pelletTime) {
			pelletTime_ += pelletTime;
		}


	/* Méthodes */
	public:
		inline void addNbrHealthPointsEarned(void) {
			nbrHealthPointsEarned_ += 1;
		}

	public:
		/**
		 * @brief Initialise Pac-Man dans sa configuration de base
		 * 
		 * @param healthPoints les points de vie que Pac-Man aura
		 * @return la classe Player intialisée pour Pac-Man
		 */
		static Player initPacMan(int healthPoints);

		/**
		 * @brief Vérifie si le joueur est sur un élément et lance la mise à
		 * 		  jour du score
		 *
		 * @param element à vérifier si on est dessus
		 * @param statsPac les stats à mettre à jour en fonction des points
		 * @param score à ajouter en cas de collision
		 * @return true si le joueur est sur un élément
		 * @return false si le joueur n'est pas sur un élément
		 */
		bool onElement(
			std::vector<SDL_Rect> &element,
			Stats &statsPac,
			int score
		);

		/**
		 * @brief Vérifie si le joueur est sur un élément et passe les fantômes
		 * 		  en mode apeuré si Pac-Man est sur une super pac-gomme
		 *
		 * @param dots les pac-gommes à vérifier si l'on est dessus
		 * @param energizers les super pac-gommes à vérifier si l'on est dessus
		 * @param fruit le fruit à vérifier si l'on est dessus
		 * @param statsPac les stats à mettre à jour en fonction des points
		 * @param ghosts à passer en mode apeuré
		 */
		void checkPostion(
			std::vector<SDL_Rect> &dots,
			std::vector<SDL_Rect> &energizers,
			SDL_Rect &fruit,
			Stats &statsPac,
			std::vector<Ghost> &ghosts
		);

		/**
		 * @brief Vérifie si le joueur est sur un fantôme
		 *
		 * @param ghosts à vérifier et à renvoyer au spawn, si mangé en mode
		 * 				 apeuré
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
		 * @param ghost status à reset si fin du mode "pellet"
		 * @param statsPac nbr de fantômes mangés à reset si fin du mode
		 * 				   "pellet" (pour le coeff)
		 */
		void checkPelletActive(std::vector<Ghost> &ghost, Stats &statsPac);

		/**
		 * @brief Vérifie si le joueur est mort pour écrire le score
		 *
		 * @param statsPac pour y écrire le score
		 * @param interface afficher l'écran de titre si plus de points de vie
		 * @return true si le joueur est mort
		 * @return false si le joueur n'est pas mort
		 */
		bool isDead(Stats &statsPac, Interface &interface);
};

#endif