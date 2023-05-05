#include "interface.h"

Interface::~Interface() {}

Interface::Interface(
	SDL_Window* window,
	SDL_Surface* surface,
	SDL_Surface* sprites
):
	window_{window},
	surface_{surface},
	sprites_{sprites}
{}

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
	SDL_Rect positionLettre{Coordinate::alphabetTexture};
	SDL_Rect positionDigit{Coordinate::numberTexture};

	for (int i: Coordinate::indexScore) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &positionLettre);
		positionLettre.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
	}

	// Affiche du score actuel de la partie
	int score{statsPac.getScore()};
	std::vector<int> digits{Stats::uncomposeNumber(score)};
	std::reverse(digits.begin(), digits.end());

	// Si le score est nul, on affiche un seul 0
	if (digits.size() == 0)
		digits.push_back(0);

	for (int i: digits) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::number[i],
			this->getSurface(), &positionDigit);
		positionDigit.x += Coordinate::NUMBER_TEXTURE_WIDTH;
	}

	// Affichage de "HIGH SCORE"
	positionLettre = Coordinate::alphabetTexture;
	positionLettre.x = windowWidth - (positionLettre.x * 2);

	// Affichage du score le plus élevé
	int highScore{static_cast<int>(Stats::readScores(1).front())};
	digits = Stats::uncomposeNumber(highScore);

	positionDigit = Coordinate::numberTexture;
	positionDigit.x = windowWidth - (positionDigit.x * 2);

	for (int i: digits) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::number[i],
			this->getSurface(), &positionDigit);
		positionDigit.x -= Coordinate::NUMBER_TEXTURE_WIDTH;
	}

	// On part de l'extrémité droite de l'écran, donc on inverse l'ordre
	std::vector<int> tamponIndexScore{Coordinate::indexScore};
	std::reverse(tamponIndexScore.begin(), tamponIndexScore.end());

	std::vector<int> tamponIndexHigh{Coordinate::indexHigh};
	std::reverse(tamponIndexHigh.begin(), tamponIndexHigh.end());

		// Score
	for (int i: tamponIndexScore) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &positionLettre);
		positionLettre.x -= Coordinate::ALPHABET_TEXTURE_WIDTH;
	}

		// Espace
	positionLettre.x -= Coordinate::ALPHABET_TEXTURE_WIDTH;

		// High
	for (int i: tamponIndexHigh) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &positionLettre);
		positionLettre.x -= Coordinate::Coordinate::ALPHABET_TEXTURE_WIDTH;
	}

	// Affichage de "Press escape key"
	drawPushSpace(windowWidth, windowHeight);

	// Affichage de "RANK"
	positionLettre.x = (windowWidth - (Coordinate::indexRank.size() *
		Coordinate::ALPHABET_TEXTURE_WIDTH)) / 2;
	positionLettre.y = windowHeight / 1.75 -
		Coordinate::ALPHABET_TEXTURE_WIDTH * 2;

	for (int i: Coordinate::indexRank) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
			this->getSurface(), &positionLettre);
		positionLettre.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
	}

	// Affichage des 10 meilleures scores
	positionDigit = Coordinate::numberTexture;
	positionDigit.y = windowHeight / 1.75;

	std::vector<unsigned int> scores{Stats::readScores(10)};
	for (int i: scores) {
		digits = Stats::uncomposeNumber(i);

		positionDigit.x = (windowWidth/2 +
			(digits.size() / 2.0 * Coordinate::NUMBER_TEXTURE_WIDTH)) -
			Coordinate::NUMBER_TEXTURE_WIDTH;

		for (int j: digits) {
			SDL_BlitScaled(this->getSprites(), &Coordinate::number[j],
				this->getSurface(), &positionDigit);
			positionDigit.x -= Coordinate::NUMBER_TEXTURE_WIDTH;
		}

		positionDigit.y += Coordinate::NUMBER_TEXTURE_WIDTH;
	}

	// Mets à jour la fenêtre
	SDL_UpdateWindowSurface(this->getWindow());

	// Attend l'entrée de l'utilisateur
	bool quit{false};
	int count{0};
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
			positionLettre.x = (windowWidth -
				(Coordinate::indexPressSpace.size() *
				Coordinate::ALPHABET_TEXTURE_WIDTH)) / 2;
			positionLettre.y = windowHeight / 2.5;

			// Créé un rectangle rempli, à la taille exacte de la phrase
			SDL_Rect rect{
				positionLettre.x,
				positionLettre.y,
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

	// Si le score est nul, on affiche quand même 0
	if (digits.size() == 0)
		digits.push_back(0);

	// Créé un rectangle rempli, à la taille exacte du score à afficher
	SDL_Rect rect{25, 50, static_cast<int>(
		Coordinate::ALPHABET_TEXTURE_WIDTH * digits.size()),
		Coordinate::numberTexture.h};
	drawRectangle(rect);

	// Affiche le score
	SDL_Rect positionDigit{Coordinate::numberTexture};
	for (int i: digits) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::number[i],
			this->getSurface(),	&positionDigit);
		positionDigit.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
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

void Interface::drawPushSpace(int windowWidth, int windowHeight) {
	SDL_Rect positionLettre{Coordinate::alphabetTexture};

	// Affichage de "Press escape key"
	positionLettre.x = (windowWidth -
		(Coordinate::indexPressSpace.size() *
		Coordinate::ALPHABET_TEXTURE_WIDTH)) / 2;
	positionLettre.y = windowHeight / 2.5;

	for (int i: Coordinate::indexPressSpace) {
		if (i != -1) {
			SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
				this->getSurface(), &positionLettre);
		}
		positionLettre.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
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