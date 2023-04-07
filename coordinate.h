#ifndef COORDINATE_H
#define COORDINATE_H

#include <SDL.h>
#include <list>

class Coordinate
{
	private:

	public:
		/**
		 * =============== PERSONNAGE ========================
		 * La terminaison de chaque coordonnées à
		 * son sens (voir ci-dessous):
		 * b -> "base"
		 * r -> "right"
		 * l -> "left"
		 * d -> "down"
		 * u -> "up"
		 * 
		 * Format (x, y, w, h)
		*/
		// Coordonnées de Pacman
		inline static std::vector<SDL_Rect> pac_b{{3, 89, 16, 16}};
		inline static std::vector<SDL_Rect> pac_r{{20, 89, 15, 16}, {35, 89, 11, 16}};
		inline static std::vector<SDL_Rect> pac_l{{47, 89, 15, 16}, {63, 89, 11, 16}};
		inline static std::vector<SDL_Rect> pac_u{{75, 90, 16, 15}, {92, 94, 16, 11}};
		inline static std::vector<SDL_Rect> pac_d{{109, 90, 16, 15}, {126, 94, 16, 11}};
	
		// Coordonnées du Fantôme Rouge
		inline static std::vector<SDL_Rect> ghost_red_r{{3, 123, 16, 16}, {20, 123, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_red_l{{37, 123, 16, 16}, {54, 123, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_red_u{{71, 123, 16, 16}, {88, 123, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_red_d{{105, 123, 16, 16}, {122, 123, 16, 16}};

		// Coordonnées du Fantôme Rose
		inline static std::vector<SDL_Rect> ghost_pink_r{{3, 142, 16, 16}, {20, 142, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_pink_l{{37, 142, 16, 16}, {54, 142, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_pink_u{{71, 142, 16, 16}, {88, 142, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_pink_d{{105, 142, 16, 16},{122, 142, 16, 16}};

		// Coordonnées du Fantôme Bleu
		inline static std::vector<SDL_Rect> ghost_blue_r{{3, 159, 16, 16}, {20, 159, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_blue_l{{37, 159, 16, 16}, {54, 159, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_blue_u{{71, 159, 16, 16}, {88, 159, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_blue_d{{105, 159, 16, 16}, {122, 159, 16, 16}};

		// Coordonnées du Fantôme Orange
		inline static std::vector<SDL_Rect> ghost_orange_r{{3, 177, 16, 16}, {20, 177, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_orange_l{{37, 177, 16, 16}, {54, 177, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_orange_u{{71, 177, 16, 16}, {88, 177, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_orange_d{{105, 177, 16, 16}, {122, 177, 16, 16}};

		/**
		 * =============== MURS ===============================
		*/
		inline static std::vector<SDL_Rect> walls{ // Coordonnées (x, y, w, h)
			/********** Murs de bordure **********/
			// Zone haut gauche
			{1, 7, 8, 68},		// Rectangle - Gauche - Vertical

			// Zone haut droite
			{161, 7, 8, 768},	// Rectangle - Droite - Vertical

			// Zone bas gauche
			{1, 143, 8, 68},	// Rectangle - Gauche - Vertical

			// Zone bas droite
			{161, 143, 8, 68},	// Rectangle - Gauche - Vertical

			// Zone haut total
			{1, 1, 168, 8},		// Bordure - Haut - Horizontal

			// Zone bas total
			{1, 209, 168, 8},	// Bordure - Bas - Horizontal

			// Zone milieu gauche
			{1, 73, 40, 32},	// Bordure sortie - Haut
			{1, 113, 40, 32},	// Bordure sortie - Bas

			// Zone milieu droite
			{129, 73, 40, 32},	// Bordure sortie - Haut
			{129, 113, 40, 32},	// Bordure sortie - Bas


			/********** Murs internes **********/
			// Zone haut gauche
			{17, 17, 24, 24},	// Carré - Haut gauche
			{49, 17, 24, 24},	// Carré - Haut droite
			{17, 49, 24, 16},	// Rectangle - Bas gauche
			{49, 49, 8, 56},	// Rectangle - Double forme - Vertical
			{55, 73, 18, 8},	// Rectangle - Double forme - Horizontal

			// Zone haut droite
			{97, 17, 24, 24},	// Carré - Haut gauche
			{129, 17, 24, 24},	// Carré - Haut droite
			{129, 49, 24, 16},	// Rectangle - Bas droite
			{113, 49, 8, 56},	// Rectangle - Double forme - Vertical
			{97, 73, 18, 8},	// Rectangle - Double forme - Horizontal

			// Zone bas gauche
			{33, 159, 8, 24},	// Rectangle - Haut gauche - Double forme - Vertical
			{17, 153, 24, 8},	// Rectangle - Haut gauche - Double forme - Horizontal
			{7, 169, 18, 16},	// Rectangle - Accolé à gauche
			{49, 169, 8, 26},	// Rectangle - Bas gauche - Double forme - Vertical
			{17, 193, 56, 8},	// Rectangle - Bas gauche - Double forme - Horizontal
			{49, 153, 24, 8},	// Rectangle - Haut droite
			{49, 113, 8, 32},	// Rectangle - Haut centre

			// Zone bas droite
			{129, 159, 8, 26},	// Rectangle - Haut droite - Double forme Vertical
			{129, 153, 24, 8},	// Rectangle - Haut droite - Double forme - Horizontal
			{145, 169, 18, 16},	// Rectangle - Accolé à droite
			{113, 169, 8, 26},	// Rectangle - Bas droite - Double forme - Vertical
			{97, 193, 56, 8},	// Rectangle - Bas droite - Double forme - Horizontal
			{97, 153, 24, 8},	// Rectangle - Haut gauche
			{113, 113, 8, 32},	// Rectangle - Haut centre

			// Zone haut centre
			{81, 7, 8, 34},		// Rectangle - Haut
			{81, 63, 8, 18},	// Rectangle - Haut - Double forme - Vertical
			{65, 49, 40, 16},	// Rectangle - Haut - Double forme - Horizontal

			// Zone milieu centre
			{65, 89, 8, 32},	// Rectangle - Cage gauche
			{97, 89, 8, 32},	// Rectangle - Cage droite
			{71, 113, 28, 8},	// Rectangle - Cage bas
			{71, 89, 8, 8},		// Rectangle - Porte gauche
			{91, 89, 8, 8},		// Rectangle - Porte droite

			// Zone bas centre
			{81, 143, 8, 18},	// Rectangle - Haut - Double forme - Vertical
			{65, 129, 40, 16},	// Rectangle - Haut - Double forme - Horizontal
			{81, 183, 8, 18},	// Rectangle - Bas - Double forme - Vertical
			{65, 169, 40, 16},	// Rectangle - Bas - Double forme - Horizontal
		};
		

	public:
		Coordinate(/* args */);
		~Coordinate();
};

#endif
