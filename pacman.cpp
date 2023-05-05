#include "pacman.h"

// Pointeurs
SDL_Window* pWindow{nullptr};
SDL_Surface* winSurf{nullptr};
SDL_Surface* spritesBoard{nullptr};

// Carte (mise à l'échelle x4)
SDL_Rect bg{4, 104, 672, 864};

// Personnages (mise à l'échelle x2)
SDL_Rect ghost{34, 134, 32, 32};
SDL_Rect pac{34, 134, 32, 32};

// Murs
std::vector<SDL_Rect> walls{Coordinate::walls};

// Tunnels
std::vector<SDL_Rect> tunnels{Coordinate::tunnels};

// (Super) Pacgommes
std::vector<SDL_Rect> dots{Coordinate::dots};
std::vector<SDL_Rect> energizers{Coordinate::energizers};

int count;

void initGame(
	Player &player,
	Ghost &red,
	Ghost &blue,
	Ghost &pink,
	Ghost &orange,
	Stats &statsPac
) {
	// Créé la fenêtre de jeu
	pWindow = SDL_CreateWindow("Pac-Man", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, Interface::WINDOW_WIDTH,
		Interface::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	winSurf = SDL_GetWindowSurface(pWindow);
	spritesBoard = SDL_LoadBMP("./pacman_sprites.bmp");

	count = 0;

	// Initialise les murs avec mise à l'échelle
	for (int i{0}; i < walls.size(); i++) {
		walls[i].x *= 4;
		walls[i].y = 4 * (walls[i].y) + 100;
		walls[i].w *= 4;
		walls[i].h *= 4;
	}

	// Initialise les tunnels avec mise à l'échelle
	for (int i{0}; i < tunnels.size(); i++) {
		tunnels[i].x *= 4;
		tunnels[i].y = 4 * (tunnels[i].y) + 100;
		tunnels[i].w *= 4;
		tunnels[i].h *= 4;
	}

	player.setAnimation(
		Coordinate::pacL,
		Coordinate::pacR,
		Coordinate::pacU,
		Coordinate::pacD
	);

	red.setAnimation(
		Coordinate::ghostRedL,
		Coordinate::ghostRedR,
		Coordinate::ghostRedU,
		Coordinate::ghostRedD
	);

	pink.setAnimation(
		Coordinate::ghostPinkL,
		Coordinate::ghostPinkR,
		Coordinate::ghostPinkU,
		Coordinate::ghostPinkD
	);

	blue.setAnimation(
		Coordinate::ghostBlueL,
		Coordinate::ghostBlueR,
		Coordinate::ghostBlueU,
		Coordinate::ghostBlueD
	);

	orange.setAnimation(
		Coordinate::ghostOrangeL,
		Coordinate::ghostOrangeR,
		Coordinate::ghostOrangeU,
		Coordinate::ghostOrangeD
	);

	resetGame(player, red, blue, pink, orange, statsPac);
}

void resetGame(
	Player &player,
	Ghost &red,
	Ghost &blue,
	Ghost &pink,
	Ghost &orange,
	Stats &statsPac
) {
	// Initialise les Pacgommes
	dots = Coordinate::dots;
	for (int i{0}; i < dots.size(); i++) {
		dots[i].x = 4 * (dots[i].x + 1);
		dots[i].y = 4 * (dots[i].y + 1) + 100;
		dots[i].w *= 8;
		dots[i].h *= 8;
	}

	// Initialise les super Pacgommes
	energizers = Coordinate::energizers;
	for (int i{0}; i < energizers.size(); i++) {
		energizers[i].x = 4 * (energizers[i].x + 1);
		energizers[i].y = 4 * (energizers[i].y + 1) + 100;
		energizers[i].w *= 4;
		energizers[i].h *= 4;
	}

	// Réinitialise tous les personnages à leur place
	player.setEntityRect(Coordinate::pacDefaultPos);
	player.setWishDirection(Ghost::NONE);
	player.setEntityPic(Coordinate::pacB[0]);

	red.setEntityRect(Coordinate::ghostRedDefaultPos);
	pink.setEntityRect(Coordinate::ghostPinkDefaultPos);
	blue.setEntityRect(Coordinate::ghostBlueDefaultPos);
	orange.setEntityRect(Coordinate::ghostOrangeDefaultPos);

	// Réinitialise le status d'emplacement des fantômes
	red.setOutSpawn(false);
	pink.setOutSpawn(false);
	blue.setOutSpawn(false);
	orange.setOutSpawn(false);
}

void draw(void) {
	SDL_SetColorKey(spritesBoard, false, 0);
	SDL_BlitScaled(spritesBoard, &Coordinate::backMap[0], winSurf, &bg);

	// Couleur transparente
	SDL_SetColorKey(spritesBoard, true, 0);

	count = (count + 1) % (2048);

	// Affichage Pacgommes
	for (int i{0}; i < dots.size(); i++) {
		SDL_BlitScaled(spritesBoard, &Coordinate::dotsTexture, winSurf,
			&dots[i]);
	}

	// Affichage Super Pacgommes
	for (int i{0}; i < energizers.size(); i++) {
		SDL_BlitScaled(spritesBoard, &Coordinate::energizerTexture, winSurf,
			&energizers[i]);
	}

	// Affichage du "SCORE"
	SDL_Rect letterPosition{Coordinate::alphabetTexture};

	for (int i: Coordinate::indexScore) {
		SDL_BlitScaled(spritesBoard, &Coordinate::alphabet[i], winSurf,
			&letterPosition);
		letterPosition.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
	}
}

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to initialize SDL" << SDL_GetError()
			<< std::endl;
		return EXIT_FAILURE;
	}

	// Pac-Man
	Player pacman{
		Coordinate::pacDefaultPos,
		Coordinate::pacB[0],
		2,
		Person::NONE,
		Person::NONE,
		Player::PAC_HEALTH
	};

	std::vector<Ghost> ghosts{
		// Fantôme rouge
		{
			Coordinate::ghostRedDefaultPos,
			Coordinate::ghostRedL[0],
			1,
			Person::LEFT,
			Person::LEFT,
			1,
			Ghost::HUNTER,
			Ghost::BLINKY,
			true,
			0
		},

		// Fantôme bleu
		{
			Coordinate::ghostBlueDefaultPos,
			Coordinate::ghostBlueU[0],
			1,
			Person::UP,
			Person::UP,
			1,
			Ghost::WAIT,
			Ghost::INKY,
			false,
			Ghost::TIMER_BLUE
		},

		// Fantôme rose
		{
			Coordinate::ghostPinkDefaultPos,
			Coordinate::ghostPinkD[0],
			1,
			Person::DOWN,
			Person::UP,
			1,
			Ghost::WAIT,
			Ghost::PINKY,
			false,
			Ghost::TIMER_PINK
		},

		// Fantôme orange
		{
			Coordinate::ghostOrangeDefaultPos,
			Coordinate::ghostOrangeU[0],
			1,
			Person::UP,
			Person::UP,
			1,
			Ghost::WAIT,
			Ghost::CLYDE,
			false,
			Ghost::TIMER_ORANGE
		}
	};

	/**
	 * Index employés :
	 * - 0 : Fantôme rouge
	 * - 1 : Fantôme bleu
	 * - 2 : Fantôme rose
	 * - 3 : Fantome orange
	 */
	Stats statsPac{0, 0, 0};
	initGame(pacman, ghosts[0], ghosts[1], ghosts[2], ghosts[3], statsPac);

	SDL_Rect* pacIn{nullptr};
	SDL_Rect pacBuffer;
	SDL_Rect* ghostIn{nullptr};
	SDL_Rect ghostBuffer;

	Interface interface{pWindow, winSurf, spritesBoard};
	bool quit{interface.titleScreen(statsPac)};

	// Boucle principale
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

		if (keys[SDL_SCANCODE_R])
			resetGame(pacman, ghosts[0], ghosts[1], ghosts[2], ghosts[3], statsPac);

		// Droite
		else if (keys[SDL_SCANCODE_RIGHT])
			pacman.setWishDirection(Person::RIGHT);

		// Gauche
		else if (keys[SDL_SCANCODE_LEFT])
			pacman.setWishDirection(Person::LEFT);

		// Haut
		else if (keys[SDL_SCANCODE_UP])
			pacman.setWishDirection(Person::UP);

		// Bas
		else if (keys[SDL_SCANCODE_DOWN])
			pacman.setWishDirection(Person::DOWN);

		// Fait bouger PacMan
		pacman.move(walls, tunnels);
		pacman.checkPostion(dots, energizers, statsPac, ghosts);
		pacman.checkGhost(ghosts, statsPac, interface);
		pacman.checkPelletActive(ghosts, statsPac);
		pacman.animation(count);

		for (int i{0}; i < ghosts.size(); i++) {
			ghosts[i].enableGhost();
			if (ghosts[i].getOutSpawn())
				ghosts[i].aleaMove(walls, tunnels);
			else
				ghosts[i].moveOutOfSpawn(walls, tunnels);
			ghosts[i].animation(count);
		}


		/**
		 * Vérifie si Pac-Man et mort et attend une entrée de l'utilisateur
		 * pour recommencer la partie (ou quitter le jeu)
		 */
		if (pacman.isDead(statsPac, interface)) {
			if (interface.titleScreen(statsPac) == false) {
				pacman.setHelthPoints(Player::PAC_HEALTH);
				continue;
			}
			else {
				quit = true;
				continue;
			}
		}

		// Affichage du fond
		draw();

		// Mets à jour l'affichage de Pac-Man et des fantômes
		pacBuffer = pacman.getEntityPic();
		pacIn = &(pacBuffer);
		SDL_BlitScaled(spritesBoard, pacIn, winSurf, &pacman.getEntityRect());

		for (int i{0}; i < ghosts.size(); i++) {
			ghostBuffer = ghosts[i].getEntityPic();
			ghostIn = &(ghostBuffer);
			SDL_BlitScaled(spritesBoard, ghostIn, winSurf,
				&ghosts[i].getEntityRect());
		}

		// Mise à jour de l'affichage du score et des vies
		std::vector<int> digits{statsPac.uncomposeNumber(statsPac.getScore())};
		interface.drawScore(digits);
		interface.drawLives(pacman.getHelthPoints());

		// Vérifie si le niveau est terminé
		if (dots.empty() && energizers.empty()) {
			resetGame(pacman, ghosts[0], ghosts[1], ghosts[2], ghosts[3],
				statsPac);
		}

		SDL_UpdateWindowSurface(pWindow);

		// Limite à 60 FPS
		SDL_Delay(Interface::DELAY);
	}
	SDL_Quit();

	return EXIT_SUCCESS;
}