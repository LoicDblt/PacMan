#ifndef COORDINATE_H
#define COORDINATE_H

#include <list>
#include <SDL.h>

#define ALPHABET_TEXTURE_WIDTH 18

class Coordinate {
	public:
		/*
		 * =============== PERSONNAGES ========================
		 * La terminaison de chaque coordonnées à
		 * son sens (voir ci-dessous):
		 * b -> "base"
		 * r -> "right"
		 * l -> "left"
		 * d -> "down"
		 * u -> "up"
		 * Format (x, y, w, h)
		*/
		// Coordonnées de Pacman
		inline static std::vector<SDL_Rect> pac_b{{3, 89, 16, 16}};
		inline static std::vector<SDL_Rect> pac_r{{20, 89, 15, 16},
			{35, 89, 11, 16}};
		inline static std::vector<SDL_Rect> pac_l{{47, 89, 15, 16},
			{63, 89, 11, 16}};
		inline static std::vector<SDL_Rect> pac_u{{75, 90, 16, 15},
			{92, 94, 16, 11}};
		inline static std::vector<SDL_Rect> pac_d{{109, 90, 16, 15}, 
			{126, 94, 16, 11}};

		// Coordonnées du Fantôme Rouge
		inline static std::vector<SDL_Rect> ghost_red_r{{3, 123, 16, 16},
			{20, 123, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_red_l{{37, 123, 16, 16},
			{54, 123, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_red_u{{71, 123, 16, 16},
			{88, 123, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_red_d{{105, 123, 16, 16},
			{122, 123, 16, 16}};

		// Coordonnées du Fantôme Rose
		inline static std::vector<SDL_Rect> ghost_pink_r{{3, 142, 16, 16},
			{20, 142, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_pink_l{{37, 142, 16, 16},
			{54, 142, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_pink_u{{71, 142, 16, 16},
			{88, 142, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_pink_d{{105, 142, 16, 16},
			{122, 142, 16, 16}};

		// Coordonnées du Fantôme Bleu
		inline static std::vector<SDL_Rect> ghost_blue_r{{3, 159, 16, 16},
			{20, 159, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_blue_l{{37, 159, 16, 16},
			{54, 159, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_blue_u{{71, 159, 16, 16},
			{88, 159, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_blue_d{{105, 159, 16, 16},
			{122, 159, 16, 16}};

		// Coordonnées du Fantôme Orange
		inline static std::vector<SDL_Rect> ghost_orange_r{{3, 177, 16, 16},
			{20, 177, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_orange_l{{37, 177, 16, 16},
			{54, 177, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_orange_u{{71, 177, 16, 16},
			{88, 177, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_orange_d{{105, 177, 16, 16},
			{122, 177, 16, 16}};

		/*
		 * =============== MURS ===============================
		*/
		inline static std::vector<SDL_Rect> walls{ // Coordonnées (x, y, w, h)
			/********** Murs de bordure **********/
			// Zone haut gauche
			{1, 7, 8, 68},		// Rectangle - Gauche - V

			// Zone haut droite
			{161, 7, 8, 768},	// Rectangle - Droite - V

			// Zone bas gauche
			{1, 143, 8, 68},	// Rectangle - Gauche - V

			// Zone bas droite
			{161, 143, 8, 68},	// Rectangle - Gauche - V

			// Zone haut total
			{1, 1, 168, 8},		// Bordure - Haut - H

			// Zone bas total
			{1, 209, 168, 8},	// Bordure - Bas - H

			// Zone milieu gauche
			{1, 73, 40, 32},	// Bordure sortie - Haut
			{1, 113, 40, 32},	// Bordure sortie - Bas

			// Zone milieu droite
			{129, 73, 40, 32},	// Bordure sortie - Haut
			{129, 113, 40, 32},	// Bordure sortie - Bas


			/*********** Murs internes ***********/
			// Zone haut gauche
			{17, 17, 24, 24},	// Carré - Haut gauche
			{49, 17, 24, 24},	// Carré - Haut droite
			{17, 49, 24, 16},	// Rectangle - Bas gauche
			{49, 49, 8, 56},	// Rectangle - Double forme - V
			{55, 73, 18, 8},	// Rectangle - Double forme - H

			// Zone haut droite
			{97, 17, 24, 24},	// Carré - Haut gauche
			{129, 17, 24, 24},	// Carré - Haut droite
			{129, 49, 24, 16},	// Rectangle - Bas droite
			{113, 49, 8, 56},	// Rectangle - Double forme - V
			{97, 73, 18, 8},	// Rectangle - Double forme - H

			// Zone bas gauche
			{33, 159, 8, 24},	// Rectangle - Haut gauche - Double forme - V
			{17, 153, 24, 8},	// Rectangle - Haut gauche - Double forme - H
			{7, 169, 18, 16},	// Rectangle - Accolé à gauche
			{49, 169, 8, 26},	// Rectangle - Bas gauche - Double forme - V
			{17, 193, 56, 8},	// Rectangle - Bas gauche - Double forme - H
			{49, 153, 24, 8},	// Rectangle - Haut droite
			{49, 113, 8, 32},	// Rectangle - Haut centre

			// Zone bas droite
			{129, 159, 8, 26},	// Rectangle - Haut droite - Double forme V
			{129, 153, 24, 8},	// Rectangle - Haut droite - Double forme - H
			{145, 169, 18, 16},	// Rectangle - Accolé à droite
			{113, 169, 8, 26},	// Rectangle - Bas droite - Double forme - V
			{97, 193, 56, 8},	// Rectangle - Bas droite - Double forme - H
			{97, 153, 24, 8},	// Rectangle - Haut gauche
			{113, 113, 8, 32},	// Rectangle - Haut centre

			// Zone haut centre
			{81, 7, 8, 34},		// Rectangle - Haut
			{81, 63, 8, 18},	// Rectangle - Haut - Double forme - V
			{65, 49, 40, 16},	// Rectangle - Haut - Double forme - H

			// Zone milieu centre
			{65, 89, 8, 32},	// Rectangle - Cage gauche
			{97, 89, 8, 32},	// Rectangle - Cage droite
			{71, 113, 28, 8},	// Rectangle - Cage bas
			{71, 89, 8, 8},		// Rectangle - Porte gauche
			{91, 89, 8, 8},		// Rectangle - Porte droite

			// Zone bas centre
			{81, 143, 8, 18},	// Rectangle - Haut - Double forme - V
			{65, 129, 40, 16},	// Rectangle - Haut - Double forme - H
			{81, 183, 8, 18},	// Rectangle - Bas - Double forme - V
			{65, 169, 40, 16},	// Rectangle - Bas - Double forme - H
		};

		/*
		 * =============== PACGOMME "dots" ====================
		*/
		inline static SDL_Rect dots_texture {4, 81, 2, 2};
		inline static std::vector<SDL_Rect> dots{
			// ==== LIGNE L1 ======
			{11, 11, 1, 1},
			{19, 11, 1, 1},
			{27, 11, 1, 1},
			{35, 11, 1, 1},
			{43, 11, 1, 1},
			{51, 11, 1, 1},
			{59, 11, 1, 1},
			{67, 11, 1, 1},
			{75, 11, 1, 1},
			{91, 11, 1, 1},
			{99, 11, 1, 1},
			{107, 11, 1, 1},
			{115, 11, 1, 1},
			{123, 11, 1, 1},
			{131, 11, 1, 1},
			{139, 11, 1, 1},
			{147, 11, 1, 1},
			{155, 11, 1, 1},

			// ====== LIGNE L2 =======
			/* Ligne complète qui peut être utilisé
			comme référence. */
			{11, 43, 1, 1},
			{19, 43, 1, 1},
			{27, 43, 1, 1},
			{35, 43, 1, 1},
			{43, 43, 1, 1},
			{51, 43, 1, 1},
			{59, 43, 1, 1},
			{67, 43, 1, 1},
			{75, 43, 1, 1},
			{83, 43, 1, 1},
			{91, 43, 1, 1},
			{99, 43, 1, 1},
			{107, 43, 1, 1},
			{115, 43, 1, 1},
			{123, 43, 1, 1},
			{131, 43, 1, 1},
			{139, 43, 1, 1},
			{147, 43, 1, 1},
			{155, 43, 1, 1},

			// ======= LIGNE L3 ===========
			{11, 67, 1, 1},
			{19, 67, 1, 1},
			{27, 67, 1, 1},
			{35, 67, 1, 1},
			{43, 67, 1, 1},
			{59, 67, 1, 1},
			{67, 67, 1, 1},
			{75, 67, 1, 1},
			{91, 67, 1, 1},
			{99, 67, 1, 1},
			{107, 67, 1, 1},
			{123, 67, 1, 1},
			{131, 67, 1, 1},
			{139, 67, 1, 1},
			{147, 67, 1, 1},
			{155, 67, 1, 1},

			// ======== LIGNE L4 ============
			{11, 147, 1, 1},
			{19, 147, 1, 1},
			{27, 147, 1, 1},
			{35, 147, 1, 1},
			{43, 147, 1, 1},
			{51, 147, 1, 1},
			{59, 147, 1, 1},
			{67, 147, 1, 1},
			{75, 147, 1, 1},
			{91, 147, 1, 1},
			{99, 147, 1, 1},
			{107, 147, 1, 1},
			{115, 147, 1, 1},
			{123, 147, 1, 1},
			{131, 147, 1, 1},
			{139, 147, 1, 1},
			{147, 147, 1, 1},
			{155, 147, 1, 1},

			// ========= LIGNE L5 ==============
			{19, 163, 1, 1},
			{27, 163, 1, 1},
			{43, 163, 1, 1},
			{51, 163, 1, 1},
			{59, 163, 1, 1},
			{67, 163, 1, 1},
			{75, 163, 1, 1},
			{91, 163, 1, 1},
			{99, 163, 1, 1},
			{107, 163, 1, 1},
			{115, 163, 1, 1},
			{123, 163, 1, 1},
			{139, 163, 1, 1},
			{147, 163, 1, 1},

			// ========= LIGNE 6 =================
			{11, 187, 1, 1},
			{19, 187, 1, 1},
			{27, 187, 1, 1},
			{35, 187, 1, 1},
			{43, 187, 1, 1},
			{59, 187, 1, 1},
			{67, 187, 1, 1},
			{75, 187, 1, 1},
			{91, 187, 1, 1},
			{99, 187, 1, 1},
			{107, 187, 1, 1},
			{123, 187, 1, 1},
			{131, 187, 1, 1},
			{139, 187, 1, 1},
			{147, 187, 1, 1},
			{155, 187, 1, 1},

			// =========== LIGNE 7 ==================
			{11, 203, 1, 1},
			{19, 203, 1, 1},
			{27, 203, 1, 1},
			{35, 203, 1, 1},
			{43, 203, 1, 1},
			{51, 203, 1, 1},
			{59, 203, 1, 1},
			{67, 203, 1, 1},
			{75, 203, 1, 1},
			{83, 203, 1, 1},
			{91, 203, 1, 1},
			{99, 203, 1, 1},
			{107, 203, 1, 1},
			{115, 203, 1, 1},
			{123, 203, 1, 1},
			{131, 203, 1, 1},
			{139, 203, 1, 1},
			{147, 203, 1, 1},
			{155, 203, 1, 1},

			// =========== Colonne 1 ===========
			{11, 19, 1, 1},
			{11, 35, 1, 1},
			{11, 51, 1, 1},
			{11, 59, 1, 1},
			{11, 155, 1, 1},
			{11, 195, 1, 1},

			// ============ Colonne 2 ===========
			{27, 171, 1, 1},
			{27, 179, 1, 1},

			// ============ Colonne 3 ===========
			{43, 19, 1, 1},
			{43, 27, 1, 1},
			{43, 35, 1, 1},
			{43, 51, 1, 1},
			{43, 59, 1, 1},
			{43, 75, 1, 1},
			{43, 83, 1, 1},
			{43, 91, 1, 1},
			{43, 99, 1, 1},
			{43, 107, 1, 1},
			{43, 115, 1, 1},
			{43, 123, 1, 1},
			{43, 131, 1, 1},
			{43, 139, 1, 1},
			{43, 155, 1, 1},
			{43, 171, 1, 1},
			{43, 179, 1, 1},

			// ============= Colonne 4 ============
			{59, 51, 1, 1},
			{59, 59, 1, 1},
			{59, 171, 1, 1},
			{59, 179, 1, 1},

			// ============= Colonnne 5 ============
			{75, 19, 1, 1},
			{75, 27, 1, 1},
			{75, 35, 1, 1},
			{75, 155, 1, 1},
			{75, 195, 1, 1},

			/* A partir d'ici symétrie */
			// ============== Colonne 6 ============
			{91, 19, 1, 1},
			{91, 27, 1, 1},
			{91, 35, 1, 1},
			{91, 19, 1, 1},
			{91, 155, 1, 1},
			{91, 19, 1, 1},

			// =============== Colonne 7 ============
			{107, 51, 1, 1},
			{107, 59, 1, 1},
			{107, 171, 1, 1},
			{107, 179, 1, 1},

			// =============== Colonne 8 ==========
			{123, 19, 1, 1},
			{123, 27, 1, 1},
			{123, 35, 1, 1},
			{123, 51, 1, 1},
			{123, 59, 1, 1},
			{123, 75, 1, 1},
			{123, 83, 1, 1},
			{123, 91, 1, 1},
			{123, 99, 1, 1},
			{123, 107, 1, 1},
			{123, 115, 1, 1},
			{123, 123, 1, 1},
			{123, 131, 1, 1},
			{123, 139, 1, 1},
			{123, 155, 1, 1},
			{123, 171, 1, 1},
			{123, 179, 1, 1},

			// ============ Colonne 9 ===========
			{139, 171, 1, 1},
			{139, 179, 1, 1},

			// ============ Colonne 10 ==========
			{155, 19, 1, 1},
			{155, 35, 1, 1},
			{155, 51, 1, 1},
			{155, 59, 1, 1},
			{155, 155, 1, 1},
			{155, 195, 1, 1}
		};

		/*
		 * =============== SUPER PACGOMME "energizer" =========
		*/
		inline static SDL_Rect energizer_texture {9, 79, 7, 7};
		inline static std::vector<SDL_Rect> energizers{
			{8, 24, 7, 7},
			{8, 160, 7, 7},
			{152, 24, 7, 7},
			{152, 160, 7, 7}
		};


		/*
		 * =============== ALPHABET ===========================
		*/
		inline static SDL_Rect alphabet_texture {25, 25, ALPHABET_TEXTURE_WIDTH,
			18};
		inline static std::vector<SDL_Rect> alphabet{
			/****** A - O (première colonne) *****/
			{11, 60, 9, 9},
			{19, 60, 9, 9},
			{27, 60, 9, 9},
			{35, 60, 9, 9},
			{43, 60, 9, 9},
			{51, 60, 9, 9},
			{59, 60, 9, 9},
			{67, 60, 9, 9},
			{75, 60, 9, 9},
			{83, 60, 9, 9},
			{91, 60, 9, 9},
			{99, 60, 9, 9},
			{107, 60, 9, 9},
			{115, 60, 9, 9},
			{123, 60, 9, 9},

			/****** P - Z (seconde colonne) ******/
			{3, 68, 9, 9},
			{11, 68, 9, 9},
			{19, 68, 9, 9},
			{27, 68, 9, 9},
			{35, 68, 9, 9},
			{43, 68, 9, 9},
			{51, 68, 9, 9},
			{59, 68, 9, 9},
			{67, 68, 9, 9},
			{75, 68, 9, 9},
			{83, 68, 9, 9}
		};
};

#endif
