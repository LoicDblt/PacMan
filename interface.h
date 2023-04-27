#ifndef INTERFACE_H
#define INTERFACE_H

#include <algorithm>
#include <fstream>

#include "coordinate.h"
#include "stats.h"

class Interface {
	public:
		static const int WINDOW_WIDTH = 680;
		static const int WINDOW_HEIGHT = 1022;
		static const int DELAY = 16;

	private:
		SDL_Window* window_ = nullptr;
		SDL_Surface* surface_ = nullptr;
		SDL_Surface* sprites_ = nullptr;

	/* Constructors */
	public:
		Interface() = default;
		Interface(
			SDL_Window* window,
			SDL_Surface* surfuace,
			SDL_Surface* sprites
		);
		~Interface();

	/* Getters */
	public:
		inline SDL_Window* getWindow() const {
			return window_;
		}

		inline SDL_Surface* getSurface() const {
			return surface_;
		}

		inline SDL_Surface* getSprites() const {
			return sprites_;
		}

	/* Methods */
	public:
		/**
		 * @brief Affiche l'écran titre
		 * 		- Logo Pacman
		 * 		- Les scores (actuel et maximum)
		 * 		- Le message "Push space key"
		 * 		- Les 10 meilleurs scores
		 * 		- Le logo Namco
		 */
		void titleScreen();

		/**
		 * @brief Mets à jour le score pendant la partie
		 * 
		 * @param digits score à afficher
		 */
		void drawScore(std::vector<int> digits);

		/**
		 * @brief Affiche le nombre de vies restantes (sous forme de Pacman)
		 * 
		 * @param lives nombre de vies restantes à afficher
		 */
		void drawLives(int lives);

	private:
		/**
		 * @brief Affiche le message "Push space key"
		 * 
		 * @param windowWidth of the window
		 * @param windowHeight of the window
		 */
		void drawPushSpace(int windowWidth, int windowHeight);

		/**
		 * @brief Dessine un rectangle noir pour masquer un élément
		 * 
		 * @param rect emplacement et taille du rectangle à dessiner
		 */
		void drawRectangle(SDL_Rect rect);
};

#endif