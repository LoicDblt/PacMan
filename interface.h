#ifndef INTERFACE_H
#define INTERFACE_H

#include <algorithm>
#include <fstream>

#include "coordinate.h"
#include "stats.h"


class Interface {
	public:
		static void titleScreen(SDL_Window* pWindow, SDL_Surface* win_surf,
			SDL_Surface* plancheSprites);
};

#endif