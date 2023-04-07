#include "person.h"
#include "coordinate.h"

#include <cstdlib>
#include <iostream>

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

// Format : {x, y, w, h}, on sélectionne avec un pixel de marge "noir" autour
// Carte
SDL_Rect src_bg =	{200, 3, 168, 216};	// x ,y, w, h (0, 0) [en haut à gauche]
SDL_Rect bg =		{4, 4, 672, 864};	// Mise à l'échelle x4

// Personnages (mise à l'échelle x2)
SDL_Rect ghost =	{34, 34, 32, 32};
SDL_Rect pac =		{34, 34, 32, 32};

/******************************************************************************/
/* Test de mur à la droite de PacMan */

SDL_Rect mur_droite_pacman = {516, 612, 32, 128}; // x, y, w, h
std::vector<SDL_Rect> walls = Coordinate::walls;


/******************************************************************************/

int count;

void init() {
	// Changer les tailles casse le jeu...
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);

	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
	count = 0;

	// Init les murs avec mise à l'échelle
	for(int i=0; i<walls.size(); i++){
		walls[i].x *= 4;
		walls[i].y *= 4;
		walls[i].w *= 4;
		walls[i].h *= 4;
	}

}

// Fonction mettant à jour la surface de la fenêtre "win_surf"
void draw() {
	SDL_SetColorKey(plancheSprites, false, 0);
	SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

	// De quoi faire tourner le fantôme
	SDL_Rect* ghost_in = nullptr; // La direction du fantôme à afficher
	switch (count/132) {
		// Droite
		case 0:
			ghost_in = &(Coordinate::ghost_red_r[0]);
			ghost.x++;
			break;

		// Bas
		case 1:
			ghost_in = &(Coordinate::ghost_red_d[0]);
			ghost.y++;
			break;

		// Gauche
		case 2:
			ghost_in = &(Coordinate::ghost_red_l[0]);
			ghost.x--;
			break;

		// Haut
		case 3:
			ghost_in = &(Coordinate::ghost_red_u[0]);
			ghost.y--;
			break;

		default:
			break;
	}
	count = (count+1)%(512);

	// Change entre les 2 sprites sources pour l'animation
	SDL_Rect ghost_in2 = *ghost_in;
	if ((count/4)%2)
		ghost_in2.x += 17; // Distance x entre la sprite de base et l'animation

	// Couleur transparente
	SDL_SetColorKey(plancheSprites, true, 0);

	// Copie du sprite zoomé
	SDL_BlitScaled(plancheSprites, &ghost_in2, win_surf, &ghost);
}

/**
 * Return 
 * true -> collision avec un mur
 * false -> il n'y a  pas de collision
*/
bool detectWalls() {
	for(int i=0; i<walls.size();i++)
		if(SDL_HasIntersection(&pac, &walls[i]))
			return true;
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
	pac->y = 644;
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
	Person pacman = {324, 644, 32, 32, Coordinate::pac_b[0], 1, Person::NONE, 3};

	SDL_Rect* pac_in = nullptr;
	SDL_Rect tampon;

	pac.x = pacman.getX();
	pac.y = pacman.getY();

	// Boucle principale
	bool quit = false;
	while (!quit) {

		int vitesse_debug; // <========================== A SUPPRIMER

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
			pacman.setDirection(Person::RIGHT);
			pacman.setEntityPic(Coordinate::pac_r[0]);
		}

		// Gauche
		else if (keys[SDL_SCANCODE_LEFT]) {
			pacman.setDirection(Person::LEFT);
			pacman.setEntityPic(Coordinate::pac_l[0]);
		}

		// Haut
		else if (keys[SDL_SCANCODE_UP]) {
			pacman.setDirection(Person::UP);
			pacman.setEntityPic(Coordinate::pac_u[0]);
		}

		// Bas
		else if (keys[SDL_SCANCODE_DOWN]) {
			pacman.setDirection(Person::DOWN);
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
		// Vu qu'on doit garder la direction de déplacement quand l'utilisateur
		// appuie pas sur une touche, on le sépare de l'entrée clavier
		switch(pacman.getDirection()) {
			case Person::RIGHT: {
				// On part du principe que le mouvement est possible
				// On simule le déplacement (il ne sera pas effectué)
				pac.x++;

				// On vérifie s'il y a une collision avec un mur
				if (detectWalls())
					pac.x--;

				break;
			}

			case Person::LEFT: {
				pac.x--;
				if (detectWalls())
					pac.x++;
				break;
			}

			case Person::UP: {
				pac.y--;
				if (detectWalls())
					pac.y++;
				break;
			}

			case Person::DOWN: {
				pac.y++;
				if (detectWalls())
					pac.y--;
				break;
			}

			default:
				break;
		}


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

/*******************************************************************/
		SDL_Rect gomme_droite_pacman = {364, 652, 8, 8};
		// Collision avec les points
		if (SDL_HasIntersection(&pac, &gomme_droite_pacman)) {
			std::cout << "Hop une pacgomme !" << count << std::endl;

			
			SDL_Rect noir = Coordinate::ghost_orange_d[0];

			SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

			SDL_Rect* sprite_gom = &(noir);

			SDL_Rect position_gom = {356, 644, 32, 32};

			// Copie du sprite zoomé
			SDL_BlitScaled(plancheSprites, sprite_gom, win_surf, &position_gom);
		}
/*******************************************************************/

		// pac_in => la sprite a afficher
		// pac => la position où le placer
		SDL_BlitScaled(plancheSprites, pac_in, win_surf, &pac);
		SDL_UpdateWindowSurface(pWindow);

		// ==> Limite à 60 FPS
		SDL_Delay(vitesse_debug); // Utiliser SDL_GetTicks64() pour plus de précision
	}
	SDL_Quit();

	return EXIT_SUCCESS;
}