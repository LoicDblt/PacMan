#include <SDL.h>

#include <cstdlib>
#include <iostream>

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;

SDL_Rect src_bg = {200, 3, 168, 216};	// x ,y, w, h (0,0) [en haut à gauche]s
SDL_Rect bg = {4, 4, 672, 864};			// Mise à l'échelle x4

SDL_Rect ghost_r = {3, 123, 16, 16};
SDL_Rect ghost_l = {37, 123, 16, 16};
SDL_Rect ghost_d = {105, 123, 16, 16};
SDL_Rect ghost_u = {71, 123, 16, 16};
SDL_Rect ghost = {34, 34, 32, 32};	// Mise à l'échelle x2

int count;

void init() {
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 700, 900, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

	plancheSprites = SDL_LoadBMP("./pacman_sprites.bmp");
	count = 0;
}


// Fonction mettant à jour la surface de la fenetre "win_surf"
void draw() {
	SDL_SetColorKey(plancheSprites, false, 0);
	SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);

	// De quoi faire tourner le fantôme
	SDL_Rect* ghost_in = nullptr;
	switch (count/128) {
		case 0:
			ghost_in = &(ghost_r);
			ghost.x++;
			break;
		case 1:
			ghost_in = &(ghost_d);
			ghost.y++;
			break;
		case 2:
			ghost_in = &(ghost_l);
			ghost.x--;
			break;
		case 3:
			ghost_in = &(ghost_u);
			ghost.y--;
			break;
	}
	count =(count+1)%(512);

	// Change entre les 2 sprites sources pour une jolie animation
	SDL_Rect ghost_in2 = *ghost_in;
	if ((count/4)%2)
		ghost_in2.x += 17;

	// Couleur transparente
	SDL_SetColorKey(plancheSprites, true, 0);

	// Copie du sprite zoomé
	SDL_BlitScaled(plancheSprites, &ghost_in2, win_surf, &ghost);
}



int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError()
			<< std::endl;
		return EXIT_FAILURE;
	}

	init();

	// Boucle principale
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
		if (keys[SDL_SCANCODE_ESCAPE])
			quit = true;
		else if (keys[SDL_SCANCODE_LEFT])
			puts("LEFT");
		else if (keys[SDL_SCANCODE_RIGHT])
			puts("RIGHT");
		else if (keys[SDL_SCANCODE_UP])
			puts("UP");
		else if (keys[SDL_SCANCODE_DOWN])
			puts("DOWN");

		// Affichage
		draw();
		SDL_UpdateWindowSurface(pWindow);

		// Limite à 60 FPS
		SDL_Delay(16); // Utiliser SDL_GetTicks64() pour plus de précisions
	}
	SDL_Quit(); // On quitte SDL

	return EXIT_SUCCESS;
}