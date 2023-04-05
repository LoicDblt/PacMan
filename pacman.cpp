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
/* Test de mur à la droite de Pacou */

SDL_Rect mur_droite_pacou = {516, 612, 32, 128}; // x, y, w, h

/******************************************************************************/

int count;

void init() {
	// Changer les tailles casse le jeu...
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
	count = 0;
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

bool colliFantome(Person* pacou, SDL_Rect* pac) {
	pacou->pertePointDeVie();

	if (pacou->getPointsDeVie() == 0) {
		puts("Pacou est mort !");
		return true;
	}
	else 
		printf("Il reste %d vies à Pacou\n", pacou->getPointsDeVie());

	// Reset pacou à sa position d'origine
	pac->x = 324;
	pac->y = 644;
	pacou->setDirection(Person::NONE);
	pacou->setEntityPic(Coordinate::pac_b[0]);

	return false;
}

void animation(Person* pacou, SDL_Rect& tampon) {
	switch(pacou->getDirection()) {
		case Person::RIGHT:
			tampon = Coordinate::pac_r[1];
			break;

		case Person::DOWN:
			tampon = Coordinate::pac_d[1];
			break;

		case Person::LEFT:
			tampon = Coordinate::pac_l[1];
			break;

		case Person::UP:
			tampon = Coordinate::pac_u[1];
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

/******************************************************************************/

	/****************************/
	/*		Ajout de Pacou		*/

	// ==> Position de base de Pacou
	// 336 = 84*4 (largeur jusqu'au centre, avec débord de 1, puis scale 4)
	// (30/2)/2 = 8 (/2 pour le scale, puis pour moitié largeur de pacou)
	// 4 de marge de bordure de carte (car scale x4)
	// d'où : 8+4 = 12 
	// Ainsi, 336 - 12 = 324
	// Identique pour la hauteur
	Person pacou = {324, 644, 30, 30, Coordinate::pac_b[0], 1, Person::NONE, 3};

	SDL_Rect* pac_in = nullptr;
	SDL_Rect tampon;

	/*
		Pourquoi 12 ? 🤷‍♂️ (336 = la moitié de la carte en largeur)
		Peut être le pixel ciblé où on va mettre pacman, 1 pixel de
		débort du cadre à gauche et la même à droite
	*/
	pac.x = pacou.getX();
	pac.y = pacou.getY();

	/****************************/

	// Boucle principale
	bool quit = false;
	while (!quit) {

/******************************************************************************/
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
			pacou.setDirection(Person::RIGHT);
			pacou.setEntityPic(Coordinate::pac_r[0]);
		}

		// Bas
		else if (keys[SDL_SCANCODE_DOWN]) {
			pacou.setDirection(Person::DOWN);
			pacou.setEntityPic(Coordinate::pac_d[0]);
		}

		// Gauche
		else if (keys[SDL_SCANCODE_LEFT]) {
			pacou.setDirection(Person::LEFT);
			pacou.setEntityPic(Coordinate::pac_l[0]);
		}

		// Haut
		else if (keys[SDL_SCANCODE_UP]) {
			pacou.setDirection(Person::UP);
			pacou.setEntityPic(Coordinate::pac_u[0]);
		}

/******************************************************************************/

		/*
			==> Pour le mur à l'extrémité droite (x)
			672 - 4*4*2 - 8*4 (8px = largeur mur, 4 = largeur hors du cadre, x2
			vu que bordures droite et gauche, le tout scale x4)

			==> Pour le mur à l'extrémité basse (y)
			864 - 4*4*2 - 8*4 (8px = largeur mur, 4 = largeur hors du cadre, x2
		*/
		if (
			pac.x > 608 || pac.x < 36 ||
			pac.y > 800 || pac.y < 36
		)
			puts("Pacou est sorti de la carte !");

		if (SDL_HasIntersection(&pac, &mur_droite_pacou))
			puts("Et paf un mur !");

		// ==> On fait bouger Pacou
		// Vu qu'on doit garder la direction de déplacement quand l'utilisateur
		// appuie pas sur une touche, on le sépare de l'entrée clavier
		switch(pacou.getDirection()) {
			case Person::RIGHT: {
				// On part du principe que le mouvement est possible
				// On simule le déplacement (il ne sera pas affiché)
				bool canMove = true;
				pac.x++;

				// On vérifie qu'il reste bien dans le cadre (bord extrême)
				if (pac.x > 608)
					canMove = false;

				// On vérifie s'il y a une collision avec un mur
				else if (SDL_HasIntersection(&pac, &mur_droite_pacou))
					canMove = false;

				// Si le mouvement n'est pas faisable, on annule le déplacement
				if (canMove == false)
					pac.x--;
				break;
			}

			case Person::DOWN: {
				bool canMove = true;
				pac.y++;

				if (pac.y > 800)
					canMove = false;

				else if (SDL_HasIntersection(&pac, &mur_droite_pacou))
					canMove = false;

				if (canMove == false)
					pac.y--;
				break;
			}

			case Person::LEFT: {
				bool canMove = true;
				pac.x--;

				if (pac.x < 36)
					canMove = false;

				else if (SDL_HasIntersection(&pac, &mur_droite_pacou))
					canMove = false;

				if (canMove == false)
					pac.x++;
				break;
			}

			case Person::UP: {
				bool canMove = true;
				pac.y--;

				if (pac.y < 36)
					canMove = false;

				else if (SDL_HasIntersection(&pac, &mur_droite_pacou))
					canMove = false;

				if (canMove == false)
					pac.y++;
				break;
			}

			default:
				break;
		}

/******************************************************************************/

	// S'il y a une collision avce le fantôme rouge
	if (SDL_HasIntersection(&pac, &ghost))
		quit = colliFantome(&pacou, &pac);

/******************************************************************************/
		// Recharge la tête adaptée à la direction de pacou
		if (!((count/4)%2))
			tampon = pacou.getEntityPic();

		// Animation de Pacou
		if ((count/4)%2)
			animation(&pacou, tampon);

		pac_in = &(tampon);

		// Affichage
		draw();

		SDL_BlitScaled(plancheSprites, pac_in, win_surf, &pac);
		SDL_UpdateWindowSurface(pWindow);

		// ==> Limite à 60 FPS
		// SDL_Delay(16); // Utiliser SDL_GetTicks64() pour plus de précision
	}
	SDL_Quit();

	return EXIT_SUCCESS;
}