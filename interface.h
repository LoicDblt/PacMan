#ifndef INTERFACE_H
#define INTERFACE_H

#include <algorithm>
#include <fstream>

#include "coordinate.h"
#include "stats.h"

class Interface {
	/* Variables et constantes */
	public:
		inline static const std::string SPRITE_FILE{"./pacman_sprites.bmp"};

		static const int WINDOW_WIDTH{680};
		static const int WINDOW_HEIGHT{1022};
		static const int DELAY{16};

	private:
		SDL_Window* window_ = nullptr;
		SDL_Surface* surface_ = nullptr;
		SDL_Surface* sprites_ = nullptr;


	/* Constructeurs et destructeur */
	public:
		Interface(void) = default;
		~Interface(void) = default;
		Interface(
			SDL_Window* window,
			SDL_Surface* surfuace,
			SDL_Surface* sprites
		);


	/* Getters */
	public:
		inline SDL_Window* getWindow(void) const {
			return window_;
		}

		inline SDL_Surface* getSurface(void) const {
			return surface_;
		}

		inline SDL_Surface* getSprites(void) const {
			return sprites_;
		}


	/* Setters */
	public:
		inline void setWindow(SDL_Window* window) {
			window_ = window;
		}

		inline void setSurface(SDL_Surface* surface) {
			surface_ = surface;
		}

		inline void setSprites(SDL_Surface* sprites) {
			sprites_ = sprites;
		}


	/* Méthodes */
	public:
		/**
		 * @brief Affiche l'écran titre
		 * 		- Logo Pac-Man
		 * 		- Les scores (actuel et maximum)
		 * 		- Le message "Push space key"
		 * 		- Les 10 meilleurs scores
		 * 		- Le logo Namco
		 *
		 * @param statsPac statistiques de la partie
		 * @return true si l'utilisateur a appuyé sur la touche échap
		 * @return false si l'utilisateur a appuyé sur la touche espace
		 */
		bool titleScreen(Stats &statsPac);

		/**
		 * @brief Mets à jour le score sur l'interface
		 *
		 * @param digits score à afficher
		 */
		void drawScore(std::vector<int> digits);

		/**
		 * @brief Affiche le nombre de vies restantes (sous forme de Pac-Man
		 * 		  sous la carte)
		 *
		 * @param healthPoints nombre de vies restantes à afficher
		 */
		void drawLives(int healthPoints);

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