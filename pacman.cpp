#include "pacman.h"

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

// Carte
SDL_Rect src_bg =	{369, 3, 168, 216};
SDL_Rect bg =		{4, 104, 672, 864}; // Mise à l'échelle x4

// Personnages (mise à l'échelle x2)
SDL_Rect ghost =	{34, 134, 32, 32};
SDL_Rect pac =		{34, 134, 32, 32};

// Murs
std::vector<SDL_Rect> walls = Coordinate::walls;

// Tunnels
std::vector<SDL_Rect> tunnels = Coordinate::tunnels;

// (Super) Pacgommes
std::vector<SDL_Rect> dots = Coordinate::dots;
std::vector<SDL_Rect> energizers = Coordinate::energizers;

int count;

void init(Player& player, Ghost& red, Ghost &pink, Ghost& blue, Ghost& orange) {
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, Interface::WINDOW_WIDTH,
		Interface::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	win_surf = SDL_GetWindowSurface(pWindow);
	plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");

	count = 0;

	// Init les murs avec mise à l'échelle
	for (int i = 0; i < walls.size(); i++) {
		walls[i].x *= 4;
		walls[i].y = 4 * (walls[i].y) + 100;
		walls[i].w *= 4;
		walls[i].h *= 4;
	}

	// Init les tunnels avec mise à l'échelle
	for (int i = 0; i < tunnels.size(); i++) {
		tunnels[i].x *= 4;
		tunnels[i].y = 4 * (tunnels[i].y) + 100;
		tunnels[i].w *= 4;
		tunnels[i].h *= 4;
	}

	player.setAnimation(
		Coordinate::pac_l,
		Coordinate::pac_r,
		Coordinate::pac_u,
		Coordinate::pac_d
	);

	red.setAnimation(
		Coordinate::ghost_red_l,
		Coordinate::ghost_red_r,
		Coordinate::ghost_red_u,
		Coordinate::ghost_red_d
	);

	pink.setAnimation(
		Coordinate::ghost_pink_l,
		Coordinate::ghost_pink_r,
		Coordinate::ghost_pink_u,
		Coordinate::ghost_pink_d
	);

	blue.setAnimation(
		Coordinate::ghost_blue_l,
		Coordinate::ghost_blue_r,
		Coordinate::ghost_blue_u,
		Coordinate::ghost_blue_d
	);

	orange.setAnimation(
		Coordinate::ghost_orange_l,
		Coordinate::ghost_orange_r,
		Coordinate::ghost_orange_u,
		Coordinate::ghost_orange_d
	);

	resetGame();
}

// Remet les éléments de la carte et les perons
void resetGame()
{
	// Init les Pacgommes
	for (int i = 0; i < dots.size(); i++) {
		dots[i].x = 4 * (dots[i].x + 1);
		dots[i].y = 4 * (dots[i].y + 1) + 100;
		dots[i].w *= 8;
		dots[i].h *= 8;
	}

	// Init les super Pacgommes
	for (int i = 0; i < energizers.size(); i++) {
		energizers[i].x = 4 * (energizers[i].x + 1);
		energizers[i].y = 4 * (energizers[i].y + 1) + 100;
		energizers[i].w *= 4;
		energizers[i].h *= 4;
	}
}

// Fonction mettant à jour la surface de la fenêtre "win_surf"
void draw(void) {
	SDL_SetColorKey(plancheSprites, false, 0);
	SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

	// Couleur transparente
	SDL_SetColorKey(plancheSprites, true, 0);

	count = (count + 1)%(2048);

	// Affichage Pacgommes
	for (int i=0;i<dots.size();i++) {
		SDL_BlitScaled(plancheSprites, &Coordinate::dots_texture, win_surf,
			&dots[i]);
	}

	// Affichage Super Pacgommes
	for (int i=0;i<energizers.size();i++) {
		SDL_BlitScaled(plancheSprites, &Coordinate::energizer_texture, win_surf,
			&energizers[i]);
	}

	// Affichage du "SCORE"
	SDL_Rect positionLettre = Coordinate::alphabet_texture;

	for (int i: Coordinate::indexScore) {
		SDL_BlitScaled(plancheSprites, &Coordinate::alphabet[i], win_surf,
			&positionLettre);
		positionLettre.x += Coordinate::ALPHABET_TEXTURE_WIDTH;
	}
}

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError()
			<< std::endl;
		return EXIT_FAILURE;
	}

	// PacMan
	Player pacman = {
		Coordinate::pac_default_pos,
		Coordinate::pac_b[0],
		2,
		Person::NONE,
		Person::NONE,
		3
	};

	std::vector<Ghost> ghosts {
		// Red ghost
		{
			Coordinate::ghost_red_default_pos,
			Coordinate::ghost_red_l[0],
			1,
			Person::LEFT,
			Person::LEFT,
			1,
			Ghost::HUNTER,
			Ghost::BLINKY,
			true
		},

		// Blue ghost
		{
			Coordinate::ghost_blue_default_pos,
			Coordinate::ghost_blue_u[0],
			1,
			Person::UP,
			Person::UP,
			1,
			Ghost::WAIT,
			Ghost::INKY,
			false
		},

		// Pink ghost
		{
			Coordinate::ghost_pink_default_pos,
			Coordinate::ghost_pink_d[0],
			1,
			Person::DOWN,
			Person::UP,
			1,
			Ghost::WAIT,
			Ghost::PINKY,
			false
		},

		// Orange ghost
		{
			Coordinate::ghost_orange_default_pos,
			Coordinate::ghost_orange_u[0],
			1,
			Person::UP,
			Person::UP,
			1,
			Ghost::WAIT,
			Ghost::CLYDE,
			false
		}
	};

	init(pacman, ghosts[0], ghosts[2], ghosts[1],ghosts[3]);
	Interface interface = {pWindow, win_surf, plancheSprites};
	interface.titleScreen();

	Stats statsPac = {0, 0, 0};

	SDL_Rect* pac_in = nullptr;
	SDL_Rect pac_tampon;
	SDL_Rect* ghost_in = nullptr;
	SDL_Rect ghost_tampon;

	int ghostInited = 0;

	// Boucle principale
	bool quit = false;
	while (!quit) {
		int vitesse_debug; // <================================================= A SUPPRIMER

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

		// Debug vitesse
		else if (keys[SDL_SCANCODE_SPACE]) {
			if (vitesse_debug == 16)
				vitesse_debug = 0;
			else
				vitesse_debug = Interface::DELAY;
		}

		// On fait bouger PacMan
		pacman.move(walls, tunnels);
		pacman.checkPostion(dots, energizers, statsPac, ghosts);
		pacman.checkGhost(ghosts, statsPac);
		pacman.checkPelletActive(ghosts, statsPac);
		pacman.animation(count);

		Ghost::enableGhost(ghosts, count);

		for (int i = 0; i < ghosts.size(); i++) {
			ghosts[i].aleaMove(walls, tunnels);
			ghosts[i].animation(count);
		}

		// Affichage
		draw();

		pac_tampon = pacman.getEntityPic();
		pac_in = &(pac_tampon);
		SDL_BlitScaled(plancheSprites, pac_in, win_surf,
			&pacman.getEntityRect());

		for (int i = 0; i < ghosts.size(); i++) {
			ghost_tampon = ghosts[i].getEntityPic();
			ghost_in = &(ghost_tampon);
			SDL_BlitScaled(plancheSprites, ghost_in, win_surf,
				&ghosts[i].getEntityRect());
		}

		// Mise à jour du score et des vies
		std::vector<int> digits = statsPac.uncomposeNumber(statsPac.getScore());
		interface.drawScore(digits);
		interface.drawLives(pacman.getLives());

		SDL_UpdateWindowSurface(pWindow);

		// Limite à 60 FPS
		SDL_Delay(vitesse_debug);	// Utiliser SDL_GetTicks64() pour
									// plus de précision
	}
	SDL_Quit();

	return EXIT_SUCCESS;
}