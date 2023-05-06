#include "pacman.h"

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to initialize SDL" << SDL_GetError()
			<< std::endl;
		return EXIT_FAILURE;
	}

	Game game{};
	Interface interface{};

	// Créé les personnages dans leur état par défaut
	Player pacman{Player::initPacMan()};
	std::vector<Ghost> ghosts{Ghost::initGhosts()};

	Stats statsPac{0, 0, 0};
	game.initGame(pacman, ghosts, statsPac, interface);

	SDL_Rect* pacIn{nullptr};
	SDL_Rect pacBuffer;
	SDL_Rect* ghostIn{nullptr};
	SDL_Rect ghostBuffer;

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
			game.resetGame(pacman, ghosts, statsPac);

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
		pacman.move(game.getWalls(), game.getTunnels());
		pacman.checkPostion(game.getDots(), game.getEnergizers(),
			game.getFruit(), statsPac, ghosts);
		pacman.checkGhost(ghosts, statsPac, interface);
		pacman.checkPelletActive(ghosts, statsPac);
		pacman.animation(game.getCount());

		for (int i{0}; i < ghosts.size(); i++) {
			ghosts[i].enableGhost();
			if (ghosts[i].getOutSpawn())
				ghosts[i].aleaMove(game.getWalls(), game.getTunnels());
			else
				ghosts[i].moveOutOfSpawn(game.getWalls(), game.getTunnels());
			ghosts[i].animation(game.getCount());
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

		// Détermine un emplacement pour la cerise
		if (
			SDL_RectEquals(&game.getFruit(), &Coordinate::NONE_FRUIT) &&
			statsPac.getDotsEaten() == 70 ||
			statsPac.getDotsEaten() == 170
		)
			game.genFruit();

		// Affichage du fond
		game.draw(interface);

		// Mets à jour l'affichage de Pac-Man et des fantômes
		pacBuffer = pacman.getEntityPic();
		pacIn = &(pacBuffer);
		SDL_BlitScaled(interface.getSprites(), pacIn, interface.getSurface(),
			&pacman.getEntityRect());

		for (int i{0}; i < ghosts.size(); i++) {
			ghostBuffer = ghosts[i].getEntityPic();
			ghostIn = &(ghostBuffer);
			SDL_BlitScaled(interface.getSprites(), ghostIn,
				interface.getSurface(), &ghosts[i].getEntityRect());
		}

		// Mise à jour de l'affichage du score et des vies
		std::vector<int> digits{statsPac.uncomposeNumber(statsPac.getScore())};
		interface.drawScore(digits);
		interface.drawLives(pacman.getHelthPoints());

		// Vérifie si le niveau est terminé
		if (game.getDots().empty() && game.getEnergizers().empty())
			game.resetGame(pacman, ghosts, statsPac);

		SDL_UpdateWindowSurface(interface.getWindow());

		// Limite à 60 FPS
		SDL_Delay(Interface::DELAY);
	}
	SDL_Quit();

	return EXIT_SUCCESS;
}