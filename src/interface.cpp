#include "interface.hpp"

Interface::Interface(
	SDL_Window* window,
	SDL_Surface* surface,
	SDL_Surface* sprites
):
	window_{window},
	surface_{surface},
	sprites_{sprites}
{}

/* Public */

bool Interface::titleScreen(Stats &statsPac) {
	int windowWidth, windowHeight;
	SDL_GetWindowSize(this->getWindow(), &windowWidth, &windowHeight);

	// Reset le background
	SDL_Rect background{0, 0, windowWidth, windowHeight};
	drawRectangle(background);

	// Affichage des logos
	SDL_Rect posPacman{Coordinate::posPacmanLogo};
	SDL_BlitScaled(this->getSprites(), &Coordinate::pacmanLogo,
		this->getSurface(), &posPacman);

	SDL_Rect posNamco{Coordinate::posNamcoLogo};
	SDL_BlitScaled(this->getSprites(), &Coordinate::namcoLogo,
		this->getSurface(), &posNamco);

	// Affichage de "SCORE"
	SDL_Rect letterPosition{Coordinate::alphabetTexture};
	SDL_Rect digitPosition{Coordinate::numberTexture};

	for (int i: Coordinate::indexScore) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &letterPosition);
		letterPosition.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
	}

	// Affiche du score actuel de la partie
	int score{statsPac.getScore()};
	std::vector<int> digits{Stats::uncomposeNumber(score)};
	std::reverse(digits.begin(), digits.end());


	for (int i: digits) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::number[i],
			this->getSurface(), &digitPosition);
		digitPosition.x += Coordinate::NUMBER_TEXTURE_WIDTH;
	}

	// Affichage de "HIGH SCORE"
	letterPosition = Coordinate::alphabetTexture;
	letterPosition.x = windowWidth - (letterPosition.x * 2);

	// Affichage du score le plus élevé
	int highScore{static_cast<int>(Stats::readScores(1).front())};
	digits = Stats::uncomposeNumber(highScore);

	digitPosition = Coordinate::numberTexture;
	digitPosition.x = windowWidth - (digitPosition.x * 2);

	for (int i: digits) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::number[i],
			this->getSurface(), &digitPosition);
		digitPosition.x -= Coordinate::NUMBER_TEXTURE_WIDTH;
	}

	// On part de l'extrémité droite de l'écran, donc on inverse l'ordre
	std::vector<int> indexScoreBuffer{Coordinate::indexScore};
	std::reverse(indexScoreBuffer.begin(), indexScoreBuffer.end());

	std::vector<int> indexHighBuffer{Coordinate::indexHigh};
	std::reverse(indexHighBuffer.begin(), indexHighBuffer.end());

		// Score
	for (int i: indexScoreBuffer) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &letterPosition);
		letterPosition.x -= Coordinate::ALPHABET_TEXTURE_WIDTH;
	}

		// Espace
	letterPosition.x -= Coordinate::ALPHABET_TEXTURE_WIDTH;

		// High
	for (int i: indexHighBuffer) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &letterPosition);
		letterPosition.x -= Coordinate::Coordinate::ALPHABET_TEXTURE_WIDTH;
	}

	// Affichage de "Press escape key"
	drawPushSpace(windowWidth, windowHeight);

	// Affichage de "RANK"
	letterPosition.x = (windowWidth - (Coordinate::indexRank.size() *
		Coordinate::ALPHABET_TEXTURE_WIDTH)) / 2;
	letterPosition.y = windowHeight / 1.75 -
		Coordinate::ALPHABET_TEXTURE_WIDTH * 2;

	for (int i: Coordinate::indexRank) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &letterPosition);
		letterPosition.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
	}

	// Affichage des 10 meilleures scores
	digitPosition = Coordinate::numberTexture;
	digitPosition.y = windowHeight / 1.75;

	std::vector<unsigned int> scores{Stats::readScores(10)};
	for (int i: scores) {
		digits = Stats::uncomposeNumber(i);

		digitPosition.x = (windowWidth/2 +
			(digits.size() / 2.0 * Coordinate::NUMBER_TEXTURE_WIDTH)) -
			Coordinate::NUMBER_TEXTURE_WIDTH;

		// Affiche un tiret si aucun score
		if (i == 0 && scores.size() == 1) {
			SDL_BlitScaled(this->getSprites(), &Coordinate::hyphen,
				this->getSurface(), &digitPosition);
		}
		else {
			for (int j: digits) {
				SDL_BlitScaled(this->getSprites(), &Coordinate::number[j],
					this->getSurface(), &digitPosition);
				digitPosition.x -= Coordinate::NUMBER_TEXTURE_WIDTH;
			}
		}

		digitPosition.y += Coordinate::NUMBER_TEXTURE_WIDTH;
	}

	// Mets à jour la fenêtre
	SDL_UpdateWindowSurface(this->getWindow());

	// Attend l'entrée de l'utilisateur
	bool quit{false};
	int count{0};
	while (!quit) {
		if (count > 2048)
			count = 0;

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
		const Uint8* keys{SDL_GetKeyboardState(&nbk)};

		// Quitter
		if (keys[SDL_SCANCODE_ESCAPE])
			quit = true;

		// Commence la partie
		if (keys[SDL_SCANCODE_SPACE]) {
			// Créé un rectangle rempli, à la taille exacte du score à afficher
			SDL_Rect rect{0, 0, windowWidth, windowHeight};
			drawRectangle(rect);

			return false;
		}

		/**
		 * Attend 0,5s avant de passer d'un message à l'autre
		 * 1 tour = 16m et 1s = 62*16ms, d'où le modulo 62
		 */
		if ((count % 62) == 1) {
			letterPosition.x = (windowWidth -
				(Coordinate::indexPressSpace.size() *
				Coordinate::ALPHABET_TEXTURE_WIDTH)) / 2;
			letterPosition.y = windowHeight / 2.5;

			// Créé un rectangle rempli, à la taille exacte de la phrase
			SDL_Rect rect{
				letterPosition.x,
				letterPosition.y,
				static_cast<int>(Coordinate::ALPHABET_TEXTURE_WIDTH *
					Coordinate::indexPressSpace.size()),
				Coordinate::ALPHABET_TEXTURE_WIDTH
			};
			drawRectangle(rect);
		}
		else if ((count % 31) == 1)
			drawPushSpace(windowWidth, windowHeight);

		count++;
		SDL_UpdateWindowSurface(this->getWindow());
		SDL_Delay(DELAY);
	}

	return true;
}

void Interface::drawScore(std::vector<int> digits) {
	// Inverse le vecteur pour l'afficher dans le bon sens
	std::reverse(digits.begin(), digits.end());

	// Créé un rectangle rempli, à la taille exacte du score à afficher
	SDL_Rect rect{25, 50, static_cast<int>(
		Coordinate::ALPHABET_TEXTURE_WIDTH * digits.size()),
		Coordinate::numberTexture.h};
	drawRectangle(rect);

	// Affiche le score
	SDL_Rect digitPosition{Coordinate::numberTexture};
	for (int i: digits) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::number[i],
			this->getSurface(),	&digitPosition);
		digitPosition.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
	}
}

void Interface::drawLives(int healthPoints) {
	SDL_Rect position{Coordinate::pacLives};
	SDL_Rect face{Coordinate::pacL[0]};

	// Créé un rectangle rempli, à la taille exacte du nombre de vies à masquer
	SDL_Rect rect{position.x, position.y, (healthPoints + 1) *
		(position.w + 14), position.h};
	drawRectangle(rect);

	for (int i{0}; i < healthPoints; i++) {
		SDL_BlitScaled(this->getSprites(), &face, this->getSurface(),
			&position);
		position.x += 32 + 14;
	}
}

/* Private */

void Interface::drawPushSpace(int windowWidth, int windowHeight) {
	SDL_Rect letterPosition{Coordinate::alphabetTexture};

	// Affichage de "Press escape key"
	letterPosition.x = (windowWidth -
		(Coordinate::indexPressSpace.size() *
		Coordinate::ALPHABET_TEXTURE_WIDTH)) / 2;
	letterPosition.y = windowHeight / 2.5;

	for (int i: Coordinate::indexPressSpace) {
		if (i != -1) {
			SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
				this->getSurface(), &letterPosition);
		}
		letterPosition.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
	}
}

void Interface::drawRectangle(SDL_Rect rect) {
	SDL_Color color{0, 0, 0, 255};
	SDL_Surface* surface = SDL_CreateRGBSurface(0, rect.w, rect.h,
		32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, color.r,
		color.g, color.b));
	SDL_BlitScaled(surface, NULL, this->getSurface(), &rect);
	SDL_FreeSurface(surface);
}