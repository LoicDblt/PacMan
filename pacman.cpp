#include "person.h"
#include "coordinate.h"

#include <cstdlib>
#include <iostream>

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

// Format : {x, y, w, h}, on sélectionne avec un pixel de marge "noir" autour

SDL_Rect src_bg =	{200, 3, 168, 216};	// x ,y, w, h (0, 0) [en haut à gauche]
SDL_Rect bg =		{4, 4, 672, 864};	// Mise à l'échelle x4

//SDL_Rect ghost_r =	{3, 123, 16, 16};
SDL_Rect ghost_r = Coordinate::ghost_red_r[0];
SDL_Rect ghost_l =	{37, 123, 16, 16};
SDL_Rect ghost_d =	{105, 123, 16, 16};
SDL_Rect ghost_u =	{71, 123, 16, 16};
SDL_Rect ghost =	{34, 34, 32, 32};	// Mise à l'échelle x2

SDL_Rect pac_n =	{3, 89, 16, 16};

SDL_Rect pac_r =	{20, 89, 15, 16};
SDL_Rect pac_ra =	{35, 89, 11, 16};

SDL_Rect pac_l =	{47, 89, 16, 16};
SDL_Rect pac_d =	{109, 90, 16, 16};
SDL_Rect pac_u =	{75, 90, 16, 16};
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
			ghost_in = &(ghost_r);
			ghost.x++;
			break;

		// Bas
		case 1:
			ghost_in = &(ghost_d);
			ghost.y++;
			break;

		// Gauche
		case 2:
			ghost_in = &(ghost_l);
			ghost.x--;
			break;

		// Haut
		case 3:
			ghost_in = &(ghost_u);
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
	// d'où : 8+4 = 12 🤯
	// Ainsi, 336 - 12 = 324
	// Identique pour la hauteur
	Person pacou = {324, 644, 30, 30, pac_n, 1, Person::NONE};

	SDL_Rect* pac_in = nullptr;
	SDL_Rect tampon = pacou.getEntityPic();	// On ne peut pas récupérer
											// l'adresse temporaire

	pac_in = &(tampon);

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
			puts("RIGHT");
			pacou.setDirection(Person::RIGHT);
			pacou.setEntityPic(pac_r);
		}

		// Bas
		else if (keys[SDL_SCANCODE_DOWN]) {
			puts("DOWN");
			pacou.setDirection(Person::DOWN);
			pacou.setEntityPic(pac_d);
		}

		// Gauche
		else if (keys[SDL_SCANCODE_LEFT]) {
			puts("LEFT");
			pacou.setDirection(Person::LEFT);
			pacou.setEntityPic(pac_l);
		}

		// Haut
		else if (keys[SDL_SCANCODE_UP]) {
			puts("UP");
			pacou.setDirection(Person::UP);
			pacou.setEntityPic(pac_u);
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

		// Recharge la tête adaptée à la direction de pacou
		tampon = pacou.getEntityPic();

		// ==> Animation
		// Codé en dur pour tester
		// if ((count/4)%2)
			// tampon = pac_ra;

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