#ifndef INTERFACE_H
#define INTERFACE_H

#include <algorithm>
#include <fstream>

#include "coordinate.h"
#include "stats.h"


class Interface {
	private:
		SDL_Window* window_ = nullptr;
		SDL_Surface* surface_ = nullptr;
		SDL_Surface* sprites_ = nullptr;

	public:
		Interface() = default;
		Interface(
			SDL_Window* window,
			SDL_Surface* surfuace,
			SDL_Surface* sprites
		);
		~Interface();

	/* Getter */
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

	public:
		void titleScreen();

	private:
		void displayPushSpace(int windowWidth, int windowHeight);
};

#endif