#include "interface.h"

Interface::Interface(
	SDL_Window* window,
	SDL_Surface* surface,
	SDL_Surface* sprites
):
	window_{window},
	surface_{surface},
	sprites_{sprites}
{};

Interface::~Interface() {};

/**
 * @brief Affiche le message "Push space key"
 * 
 * @param windowWidth of the window
 * @param windowHeight of the window
 */
void Interface::displayPushSpace(int windowWidth, int windowHeight) {
	SDL_Rect positionLettre = Coordinate::alphabet_texture;

	// Affichage de "Press escape key"
	positionLettre.x = (windowWidth -
		(Coordinate::indexPressSpace.size() *
		ALPHABET_TEXTURE_WIDTH))/2;
	positionLettre.y = windowHeight/2.5;

	for (int i: Coordinate::indexPressSpace) {
		if (i != -1) {
			SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
				this->getSurface(), &positionLettre);
		}
		positionLettre.x += ALPHABET_TEXTURE_WIDTH;
	}
}

/**
 * @brief Affiche l'écran titre
 * 		- Logo Pacman
 * 		- Les scores (actuel et maximum)
 * 		- Le message "Push space key"
 * 		- Les 10 meilleurs scores
 * 		- Le logo Namco
 */
void Interface::titleScreen() {
	int windowWidth, windowHeight;
	SDL_GetWindowSize(this->getWindow(), &windowWidth, &windowHeight);

	// Affichage des logos
	SDL_BlitScaled(this->getSprites(), &Coordinate::pacmanLogo,
		this->getSurface(), &Coordinate::posPacmanLogo);

	SDL_BlitScaled(this->getSprites(), &Coordinate::namcoLogo,
		this->getSurface(), &Coordinate::posNamcoLogo);

	// Affichage de "SCORE"
	SDL_Rect positionLettre = Coordinate::alphabet_texture;
	SDL_Rect positionDigit = Coordinate::number_texture;
	SDL_BlitScaled(this->getSprites(), &Coordinate::number[0],
		this->getSurface(), &positionDigit);

	for (int i: Coordinate::indexScore) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &positionLettre);
		positionLettre.x += ALPHABET_TEXTURE_WIDTH;
	}

	// Affichage de "HIGH SCORE"
	positionLettre = Coordinate::alphabet_texture;
	positionLettre.x = windowWidth - (positionLettre.x * 2);

	// Affichage du score le plus élevé
	int highScore = Stats::readScores(1).front();
	std::vector<int> digits = Stats::uncomposeNumber(highScore);

	positionDigit = Coordinate::number_texture;
	positionDigit.x = windowWidth - (positionDigit.x * 2);

	for (int i: digits) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::number[i],
			this->getSurface(), &positionDigit);
		positionDigit.x -= NUMBER_TEXTURE_WIDTH;
	}

	// On part de l'extrémité droite de l'écran, donc on inverse l'ordre
	std::vector<int> tamponIndexScore = Coordinate::indexScore;
	std::reverse(tamponIndexScore.begin(), tamponIndexScore.end());

	std::vector<int> tamponIndexHigh = Coordinate::indexHigh;
	std::reverse(tamponIndexHigh.begin(), tamponIndexHigh.end());

		// Score
	for (int i: tamponIndexScore) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &positionLettre);
		positionLettre.x -= ALPHABET_TEXTURE_WIDTH;
	}

		// Espace
	positionLettre.x -= ALPHABET_TEXTURE_WIDTH;

		// High
	for (int i: tamponIndexHigh) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &positionLettre);
		positionLettre.x -= ALPHABET_TEXTURE_WIDTH;
	}

	// Affichage de "Press escape key"
	displayPushSpace(windowWidth, windowHeight);

	// Affichage de "RANK"
	positionLettre.x = (windowWidth - (Coordinate::indexRank.size() *
		ALPHABET_TEXTURE_WIDTH))/2;
	positionLettre.y = windowHeight/1.75 - ALPHABET_TEXTURE_WIDTH*2;

	for (int i: Coordinate::indexRank) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &positionLettre);
		positionLettre.x += ALPHABET_TEXTURE_WIDTH;
	}

	// Affichage des 10 meilleures scores
	positionDigit = Coordinate::number_texture;
	positionDigit.y = windowHeight/1.75;

	std::vector<unsigned int> scores = Stats::readScores(10);
	for (int i: scores) {
		digits = Stats::uncomposeNumber(i);

		positionDigit.x = (windowWidth/2 + (digits.size()/2.0 *
			NUMBER_TEXTURE_WIDTH)) - NUMBER_TEXTURE_WIDTH;

		for (int j: digits) {
			SDL_BlitScaled(this->getSprites(), &Coordinate::number[j],
				this->getSurface(), &positionDigit);
			positionDigit.x -= NUMBER_TEXTURE_WIDTH;
		}

		positionDigit.y += NUMBER_TEXTURE_WIDTH;
	}

	// Mets à jour la fenêtre
	SDL_UpdateWindowSurface(this->getWindow());

	// Attend l'entrée de l'utilisateur
	bool quit = false;
	int count = 0;
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
			drawRectangle(rect);
			break;
		}

		/**
		 * Attend 0,5s avant de passer d'un message à l'autre
		 * 1 tour = 16m et 1s = 62*16ms, d'où le modulo 62
		*/
		if ((count % 62) == 1) {
			positionLettre.x = (windowWidth -
				(Coordinate::indexPressSpace.size() *
				ALPHABET_TEXTURE_WIDTH))/2;
			positionLettre.y = windowHeight/2.5;

			// Créé un rectangle rempli, à la taille exacte de la phrase
			SDL_Rect rect = {
				positionLettre.x,
				positionLettre.y,
				static_cast<int>(ALPHABET_TEXTURE_WIDTH *
					Coordinate::indexPressSpace.size()),
				ALPHABET_TEXTURE_WIDTH
			};
			drawRectangle(rect);
		}
		else if ((count % 31) == 1)
			displayPushSpace(windowWidth, windowHeight);

		count++;
		SDL_UpdateWindowSurface(this->getWindow());
		SDL_Delay(16);
	}
}

/**
 * @brief Mets à jour le score pendant la partie
 * 
 * @param digits score à afficher
 */
void Interface::drawScore(std::vector<int> digits) {
	// Inverse le vecteur pour l'afficher dans le bon sens
	std::reverse(digits.begin(), digits.end());

	// Si le score est nul, on affiche quand même 0
	if (digits.size() == 0)
		digits.push_back(0);

	// Créé un rectangle rempli, à la taille exacte du score à afficher
	SDL_Rect rect = {25, 50,
		static_cast<int>(ALPHABET_TEXTURE_WIDTH * digits.size()),
		Coordinate::number_texture.h};
	drawRectangle(rect);

	// Affiche le score
	SDL_Rect positionDigit = Coordinate::number_texture;
	for (int i: digits) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::number[i],
			this->getSurface(),	&positionDigit);
		positionDigit.x += ALPHABET_TEXTURE_WIDTH;
	}
}

/**
 * @brief Affiche le nombre de vies restantes (sous forme de Pacman)
 * 
 * @param lives nombre de vies restantes à afficher
 */
void Interface::drawLives(int lives) {
	SDL_Rect position{Coordinate::pacLives};
	SDL_Rect face{Coordinate::pac_l[0]};

	// Créé un rectangle rempli, à la taille exacte du nombre de vies à masquer
	SDL_Rect rect = {position.x, position.y, (lives + 1) * (position.w + 14),
		position.h};
	drawRectangle(rect);

	for (int i = 0; i < lives; i++) {
		SDL_BlitScaled(this->getSprites(), &face, this->getSurface(),
			&position);
		position.x += 32 + 14;
	}
}

/**
 * @brief Dessine un rectangle noir pour masquer un élément
 * 
 * @param rect emplacement et taille du rectangle à dessiner
 */
void Interface::drawRectangle(SDL_Rect rect) {
	SDL_Color color = {0, 0, 0, 255};
	SDL_Surface* surface = SDL_CreateRGBSurface(0, rect.w, rect.h,
		32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, color.r,
		color.g, color.b));
	SDL_BlitScaled(surface, NULL, this->getSurface(), &rect);
	SDL_FreeSurface(surface);
}