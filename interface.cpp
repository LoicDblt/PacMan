#include "interface.h"

void Interface::titleScreen(SDL_Window* pWindow, SDL_Surface* win_surf,
	SDL_Surface* plancheSprites
) {
	bool quit = false;
	int windowWidth, windowHeight;
	SDL_GetWindowSize(pWindow, &windowWidth, &windowHeight);
	while (!quit) {
		SDL_Event event;
		while (!quit && SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;

				default:
					break;
			}
		}

		// Gestion du clavier
		int nbk;
		const Uint8* keys = SDL_GetKeyboardState(&nbk);

		// Quitter
		if (keys[SDL_SCANCODE_ESCAPE])
			quit = true;

		// Commence la partie
		if (keys[SDL_SCANCODE_SPACE]) {
			// Créé un rectangle rempli, à la taille exacte du score à afficher
			SDL_Rect rect = {0, 0, windowWidth, windowHeight};
			SDL_Color color = {0, 0, 0, 255};
			SDL_Surface* surface = SDL_CreateRGBSurface(0, rect.w, rect.h,
				32, 0, 0, 0, 0);
			SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, color.r,
				color.g, color.b));
			SDL_BlitScaled(surface, NULL, win_surf, &rect);
			SDL_FreeSurface(surface);
			break;
		}

		// Affichage des logos
		SDL_BlitScaled(plancheSprites, &Coordinate::pacmanLogo, win_surf,
			&Coordinate::posPacmanLogo);

		SDL_BlitScaled(plancheSprites, &Coordinate::namcoLogo, win_surf,
			&Coordinate::posNamcoLogo);

		// Affichage de "SCORE"
		SDL_Rect positionLettre = Coordinate::alphabet_texture;
		SDL_Rect positionDigit = Coordinate::number_texture;
		SDL_BlitScaled(plancheSprites, &Coordinate::number[0], win_surf,
			&positionDigit);

		for (int i: Coordinate::indexScore) {
			SDL_BlitScaled(plancheSprites, &Coordinate::alphabet[i], win_surf,
				&positionLettre);
			positionLettre.x += ALPHABET_TEXTURE_WIDTH;
		}

		// Affichage de "HIGH SCORE"
		positionLettre = Coordinate::alphabet_texture;
		positionLettre.x = windowWidth - (positionLettre.x * 2);

		// Si le fichier des scores existe, on affiche le plus haut
		std::ifstream file("./scores.txt");
		if (file.good()) {
			std::string line;
			getline(file, line);
			int highScore = std::stoi(line);

			std::vector<int> digits = Stats::uncomposeNumber(highScore);

			SDL_Rect positionDigit = Coordinate::number_texture;
			positionDigit.x = windowWidth - (positionDigit.x * 2);

			for (int i: digits) {
				SDL_BlitScaled(plancheSprites, &Coordinate::number[i], win_surf,
					&positionDigit);
				positionDigit.x -= ALPHABET_TEXTURE_WIDTH;
			}
		}

		// On part de l'extrémité droite de l'écran, donc on inverse l'ordre
		std::vector<int> tamponIndexScore = Coordinate::indexScore;
		std::reverse(tamponIndexScore.begin(), tamponIndexScore.end());

		std::vector<int> tamponIndexHigh = Coordinate::indexHigh;
		std::reverse(tamponIndexHigh.begin(), tamponIndexHigh.end());

			// Score
		for (int i: tamponIndexScore) {
			SDL_BlitScaled(plancheSprites, &Coordinate::alphabet[i], win_surf,
				&positionLettre);
			positionLettre.x -= ALPHABET_TEXTURE_WIDTH;
		}
		
			// Espace
		positionLettre.x -= ALPHABET_TEXTURE_WIDTH;

			// High
		for (int i: tamponIndexHigh) {
			SDL_BlitScaled(plancheSprites, &Coordinate::alphabet[i], win_surf,
				&positionLettre);
			positionLettre.x -= ALPHABET_TEXTURE_WIDTH;
		}

		// Affichage de "Press escape key"
		positionLettre.x = (windowWidth - (Coordinate::indexPressSpace.size() *
			ALPHABET_TEXTURE_WIDTH))/2;
		positionLettre.y = windowHeight/2;

		for (int i: Coordinate::indexPressSpace) {
			if (i != -1) {
				SDL_BlitScaled(plancheSprites, &Coordinate::alphabet[i],
					win_surf, &positionLettre);
			}
			positionLettre.x += ALPHABET_TEXTURE_WIDTH;
		}

		SDL_UpdateWindowSurface(pWindow);
		SDL_Delay(16);
	}
}