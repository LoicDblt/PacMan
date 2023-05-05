#ifndef GAME_H
#define GAME_H

#include "coordinate.hpp"
#include "ghost.hpp"
#include "interface.hpp"
#include "player.hpp"
#include "stats.hpp"

class Game {
	/* Variables et constantes */
	public:
		inline static const std::string GAME_NAME{"Pac-Man"};

		inline static const SDL_Rect BACKGROUND{4, 104, 672, 864};

	private:
		std::vector<SDL_Rect> dots_{Coordinate::dots};
		std::vector<SDL_Rect> energizers_{Coordinate::energizers};
		std::vector<SDL_Rect> tunnels_{Coordinate::tunnels};
		std::vector<SDL_Rect> walls_{Coordinate::walls};
		int count_{0};


	/* Constructeurs et destructeur */
	public:
		Game(void) = default;
		~Game(void) = default;


	/* Getters */
	public:
		inline std::vector<SDL_Rect>& getDots(void) {
			return dots_;
		}

		inline std::vector<SDL_Rect>& getEnergizers(void) {
			return energizers_;
		}


		inline std::vector<SDL_Rect>& getTunnels(void) {
			return tunnels_;
		}

		inline std::vector<SDL_Rect>& getWalls(void) {
			return walls_;
		}

		inline int getCount(void) const {
			return count_;
		}


	/* Setters */
	public:
		inline void setCount(int count) {
			count_ = count;
		}


	/* Méthodes */
	public:
		inline void resetDots(void) {
			dots_ = {Coordinate::dots};
		}

		inline void resetEnergizers(void) {
			energizers_ = {Coordinate::energizers};
		}

	public:
		/**
		 * @brief Initialise le jeu et l'interface
		 *
		 * @param player Pac-Man
		 * @param ghosts vecteur de fantômes
		 * @param statsPac les stats à afficher
		 * @param interface l'interface du jeu
		 */
		void initGame(
			Player &player,
			std::vector<Ghost> &ghosts,
			Stats &statsPac,
			Interface &interface
		);

		/**
		 * @brief Replace les dots, energizers, ghosts à leur position d'origine
		 *
		 * @param player Pac-Man
		 * @param ghosts vecteur de fantômes
		 * @param statsPac les stats à afficher
		 */
		void resetGame(
			Player &Player,
			std::vector<Ghost> &ghosts,
			Stats &statsPac
		);

		/**
		 * @brief Mets à jour la fenêtre de jeu
		 *
		 * @param interface l'interface du jeu
		 */
		void draw(Interface &interface);
};

#endif