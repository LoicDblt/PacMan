#include <cstdlib>
#include <iostream>

#include "coordinate.h"
#include "person.h"
#include "stats.h"

#define DEBUG_LOIC false

/**
 * Affiche un message de débug d'El Loïco
 * @param message à afficher
*/
void debugLoic(std::string message) {
	if (DEBUG_LOIC)
		std::cout << message << std::endl;
}

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

// (Super) Pacgommes
std::vector<SDL_Rect> dots = Coordinate::dots;
std::vector<SDL_Rect> energizers = Coordinate::energizers;

int count;

void init() {
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 680, 972, SDL_WINDOW_SHOWN);

	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
	count = 0;

	// Init les murs avec mise à l'échelle
	for (int i=0; i<walls.size(); i++) {
		walls[i].x *= 4;
		walls[i].y = 4*(walls[i].y) + 100;
		walls[i].w *= 4;
		walls[i].h *= 4;
	}

	// Init les Pacgommes
	for (int i=0; i<dots.size(); i++) {
		dots[i].x = 4*(dots[i].x+1);
		dots[i].y = 4*(dots[i].y+1) + 100;
		dots[i].w *= 8;
		dots[i].h *= 8;
	}

	// Init les super Pacgommes
	for (int i=0; i<energizers.size(); i++) {
		energizers[i].x = 4*(energizers[i].x+1);
		energizers[i].y = 4*(energizers[i].y+1) + 100;
		energizers[i].w *= 4;
		energizers[i].h *= 4;
	}
}

// Fonction mettant à jour la surface de la fenêtre "win_surf"
void draw() {
	SDL_SetColorKey(plancheSprites, false, 0);
	SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

	// De quoi faire tourner le fantôme

	Person redGhost = {SDL_Rect{36, 136, 32, 32}, Coordinate::ghost_red_l[0], 1,
		Person::DOWN, 1}; // <=================================================== ERREUR ICI, il se fait reset à chaque appel

	SDL_Rect* ghost_in = nullptr; // La direction du fantôme à afficher
	// switch (count/132) {
	// 	// Droite
	// 	case 0:
	// 		ghost_in = &(Coordinate::ghost_red_r[0]);
	// 		ghost.x++;
	// 		break;

	// 	// Bas
	// 	case 1:
	// 		ghost_in = &(Coordinate::ghost_red_d[0]);
	// 		ghost.y++;
	// 		break;

	// 	// Gauche
	// 	case 2:
	// 		ghost_in = &(Coordinate::ghost_red_l[0]);
	// 		ghost.x--;
	// 		break;

	// 	// Haut
	// 	case 3:
	// 		ghost_in = &(Coordinate::ghost_red_u[0]);
	// 		ghost.y--;
	// 		break;

	// 	default:
	// 		break;
	// }

/************************ TEST FANTOME ****************************************/
	if (redGhost.ghostBehavior(walls)) {
		switch (redGhost.getDirection()) {
			case Person::RIGHT:
				debugLoic(">>> Going right : x = " +
					std::to_string(redGhost.getEntityRect().x));
				break;

			case Person::LEFT:
				redGhost.setEntityPic(Coordinate::ghost_red_l[0]);
				debugLoic(">>> Going left : x = " +
					std::to_string(redGhost.getEntityRect().x));
				break;

			case Person::UP:
				redGhost.setEntityPic(Coordinate::ghost_red_u[0]);
				debugLoic(">>> Going up : y = " +
					std::to_string(redGhost.getEntityRect().y));
				break;

			case Person::DOWN:
				redGhost.setEntityPic(Coordinate::ghost_red_d[0]);
				debugLoic(">>> Going down : y = " +
					std::to_string(redGhost.getEntityRect().y));
				break;

			default:
				break;
		}

		redGhost.move(walls);
	}

	SDL_Rect tampon;
	if (!((count/4)%2))
		tampon = redGhost.getEntityPic();

	ghost_in = &(tampon);

	// Couleur transparente
	SDL_SetColorKey(plancheSprites, true, 0);

	// Copie du sprite zoomé
	SDL_BlitScaled(plancheSprites, ghost_in, win_surf,
		&redGhost.getEntityRect());
/******************************************************************************/

	count = (count+1)%(512);

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

	// Test affichage score
	SDL_Rect positionLettre = Coordinate::alphabet_texture;

	// S
	SDL_BlitScaled(plancheSprites, &Coordinate::alphabet[18], win_surf,
		&positionLettre);
	positionLettre.x += ALPHABET_TEXTURE_WIDTH;

	// C
	SDL_BlitScaled(plancheSprites, &Coordinate::alphabet[2], win_surf,
		&positionLettre);
	positionLettre.x += ALPHABET_TEXTURE_WIDTH;

	// O
	SDL_BlitScaled(plancheSprites, &Coordinate::alphabet[14], win_surf,
		&positionLettre);
	positionLettre.x += ALPHABET_TEXTURE_WIDTH;

	// R
	SDL_BlitScaled(plancheSprites, &Coordinate::alphabet[17], win_surf,
		&positionLettre);
	positionLettre.x += ALPHABET_TEXTURE_WIDTH;

	// E
	SDL_BlitScaled(plancheSprites, &Coordinate::alphabet[4], win_surf,
		&positionLettre);
	positionLettre.x += ALPHABET_TEXTURE_WIDTH;
}

/**
 * DEPRECATED
 * Return 
 * true -> collision avec un mur
 * false -> il n'y a  pas de collision
*/
bool detectPacgomme(Stats &statsPac, SDL_Rect &pacman) {
	// Pacgomme detection
	for (int i=0; i<dots.size(); i++) {
		if (SDL_HasIntersection(&pacman, &dots[i])) {
			dots.erase(dots.begin()+i);
			statsPac.updateScore(DOT);
			std::cout << "Miam dot (#" << statsPac.getDots() << ") > "
				<< statsPac.getScore() << std::endl;
		}
	}

	// Super pacgomme detection
	for (int i=0; i<energizers.size(); i++) {
		if (SDL_HasIntersection(&pacman, &energizers[i])) {
			statsPac.updateScore(ENERGIZER);
			std::cout << "Miam energizer > " << statsPac.getScore()
				<< std::endl;

			energizers.erase(energizers.begin()+i);
		}
	}

	return false;
}


bool colliFantome(Person* pacman, SDL_Rect* pac) {
	pacman->pertePointDeVie();

	if (pacman->getPointsDeVie() == 0) {
		puts("PacMan est mort !");
		return true;
	}
	else
		printf("Il reste %d vies à PacMan\n", pacman->getPointsDeVie());

	// Reset PacMan à sa position d'origine
	pac->x = 324;
	pac->y = 744;
	pacman->setDirection(Person::NONE);
	pacman->setEntityPic(Coordinate::pac_b[0]);

	return false;
}

void animation(Person* pacman, SDL_Rect& tampon) {
	switch(pacman->getDirection()) {
		case Person::RIGHT:
			tampon = Coordinate::pac_r[1];
			break;

		case Person::LEFT:
			tampon = Coordinate::pac_l[1];
			break;

		case Person::UP:
			tampon = Coordinate::pac_u[1];
			break;

		case Person::DOWN:
			tampon = Coordinate::pac_d[1];
			break;

		default:
			break;
	}
	/*
	switch (phantom->getDirection()) {
		case Person::RIGHT:
			ghost_in = &(Coordinate::ghost_red_r[0]);
			ghost.x++;
			break;
		case Person::LEFT:
			ghost_in = &(Coordinate::ghost_red_d[0]);
			ghost.y++;
			break;
		case Person::UP:
			ghost_in = &(Coordinate::ghost_red_l[0]);
			ghost.x--;
			break;
		case Person::DOWN:
			ghost_in = &(Coordinate::ghost_red_u[0]);
			ghost.y--;
			break;

		default:
			break;
	}
	*/
}

int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Echec de l'initialisation de la SDL " << SDL_GetError()
			<< std::endl;
		return EXIT_FAILURE;
	}

	init();

	// ==> Position de base de PacMan
	// 336 = 84*4 (largeur jusqu'au centre, avec débord de 1, puis scale 4)
	// (30/2)/2 = 8 (/2 pour le scale, puis pour moitié largeur de PacMan)
	// 4 car 2 de marge sur pacman scale x2
	// d'où : 8+4 = 12
	// Ainsi, 336 - 12 = 324
	// Identique pour la hauteur
	Person pacman = {SDL_Rect{324, 744, 32, 32}, Coordinate::pac_b[0], 1,
		Person::NONE, 3};
	Stats statsPac = {0, 0, 0, 0};

	SDL_Rect* pac_in = nullptr;
	SDL_Rect tampon;

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
		else if (keys[SDL_SCANCODE_RIGHT]) {
			pacman.setWishDirection(Person::RIGHT);
			pacman.setEntityPic(Coordinate::pac_r[0]);
		}

		// Gauche
		else if (keys[SDL_SCANCODE_LEFT]) {
			pacman.setWishDirection(Person::LEFT);
			pacman.setEntityPic(Coordinate::pac_l[0]);
		}

		// Haut
		else if (keys[SDL_SCANCODE_UP]) {
			pacman.setWishDirection(Person::UP);
			pacman.setEntityPic(Coordinate::pac_u[0]);
		}

		// Bas
		else if (keys[SDL_SCANCODE_DOWN]) {
			pacman.setWishDirection(Person::DOWN);
			pacman.setEntityPic(Coordinate::pac_d[0]);
		}

		// Debug vitesse
		else if (keys[SDL_SCANCODE_SPACE]) {
			if (vitesse_debug == 16)
				vitesse_debug = 0;
			else
				vitesse_debug = 16;
		}

		// ==> On fait bouger PacMan
		pacman.move(walls);
		// ==> On vérifie si un pacgomme a été mangé
		detectPacgomme(statsPac, pacman.getEntityRect());

		// S'il y a une collision avce le fantôme rouge
		// if (SDL_HasIntersection(&pac, &ghost))
		// 	quit = colliFantome(&pacman, &pac);

		// Recharge la tête adaptée à la direction de PacMan
		if (!((count/4)%2))
			tampon = pacman.getEntityPic();

		// Animation de PacMan
		if ((count/4)%2)
			animation(&pacman, tampon);

		pac_in = &(tampon);

		// Affichage
		draw();

		// pac_in => la sprite a afficher
		// pac => la position où le placer
		SDL_BlitScaled(plancheSprites, pac_in, win_surf,
			&pacman.getEntityRect());

		// Récupère le score, le décomposer et trie les chiffres
		std::vector<int> digits = statsPac.uncomposeNumber(statsPac.getScore());
		std::reverse(digits.begin(), digits.end());

		// Si le score est nul, on affiche quand même 0
		if (digits.size() == 0)
			digits.push_back(0);

		// Créé un rectangle rempli, à la taille exacte du score à afficher
		SDL_Rect rect = {25, 50,
			static_cast<int>(ALPHABET_TEXTURE_WIDTH*digits.size()),
			Coordinate::number_texture.h};
		SDL_Color color = {0, 0, 0, 255};
		SDL_Surface* surface = SDL_CreateRGBSurface(0, rect.w, rect.h,
			32, 0, 0, 0, 0);
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, color.r,
			color.g, color.b));
		SDL_BlitScaled(surface, NULL, win_surf, &rect);
		SDL_FreeSurface(surface);
	
		// Affiche le score
		SDL_Rect positionDigit = Coordinate::number_texture;
		for (int i: digits) {
			SDL_BlitScaled(plancheSprites, &Coordinate::number[i], win_surf,
				&positionDigit);
			positionDigit.x += ALPHABET_TEXTURE_WIDTH;
		}

		// Affichage débug
		if (DEBUG_LOIC) {
			std::cout << "Score : " << statsPac.getScore() << std::endl;
			for (int i: digits)
				std::cout << i << ' ';
			std::cout << std::endl;
		}

		SDL_UpdateWindowSurface(pWindow);

		// ==> Limite à 60 FPS
		SDL_Delay(vitesse_debug);	// Utiliser SDL_GetTicks64() pour
									// plus de précision
	}
	SDL_Quit();

	return EXIT_SUCCESS;
}