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

	// Si le fichier des scores existe, on affiche le plus haut
	std::ifstream file("./scores.txt");
	int highScore = 0;
	if (file.good()) {
		std::string line;
		int readedScore;
		while (std::getline(file, line)) {
			readedScore = std::stoi(line);
			if (readedScore > highScore)
				highScore = readedScore;
		}
	}

	std::vector<int> digits = Stats::uncomposeNumber(highScore);

	positionDigit = Coordinate::number_texture;
	positionDigit.x = windowWidth - (positionDigit.x * 2);

	for (int i: digits) {
		SDL_BlitScaled(this->getSprites(), &Coordinate::number[i],
			this->getSurface(), &positionDigit);
		positionDigit.x -= ALPHABET_TEXTURE_WIDTH;
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
	positionLettre.x = (windowWidth - (Coordinate::indexPressSpace.size() *
		ALPHABET_TEXTURE_WIDTH))/2;
	positionLettre.y = windowHeight/2;

	for (int i: Coordinate::indexPressSpace) {
		if (i != -1) {
			SDL_BlitScaled(this->getSprites(), &Coordinate::alphabet[i],
				this->getSurface(), &positionLettre);
		}
		positionLettre.x += ALPHABET_TEXTURE_WIDTH;
	}

	SDL_UpdateWindowSurface(this->getWindow());

	// Attend l'entrée de l'utilisateur
	bool quit = false;
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
			SDL_BlitScaled(surface, NULL, this->getSurface(), &rect);
			SDL_FreeSurface(surface);
			break;
		}
	}
}