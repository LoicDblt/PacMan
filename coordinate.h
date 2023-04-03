#ifndef COORDINATE_H
#define COORDINATE_H

#include <SDL.h>
#include <list>

class Coordinate
{
	private:
    
	public:
		/**
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

		inline static std::vector<SDL_Rect> pac_b{{3, 89, 16, 16}};
		inline static std::vector<SDL_Rect> pac_r{{20, 89, 15, 16}, {35, 89, 11, 16}};
		inline static std::vector<SDL_Rect> pac_l{{47, 89, 15, 16}, {63, 89, 11, 16}};
		inline static std::vector<SDL_Rect> pac_u{{75, 90, 16, 15}, {92, 94, 16, 11}};
		inline static std::vector<SDL_Rect> pac_d{{109, 90, 16, 15}, {126, 94, 16, 11}};

		inline static std::vector<SDL_Rect> ghost_red_r{{3, 123, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_red_l{{37, 123, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_red_u{{71, 124, 16, 15}};
		inline static std::vector<SDL_Rect> ghost_red_d{{105, 123, 16, 16}};

		inline static std::vector<SDL_Rect> ghost_pink_r{{3, 141, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_pink_l{{37, 141, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_pink_u{{71, 142, 16, 15}};
		inline static std::vector<SDL_Rect> ghost_pink_d{{105, 141, 16, 16}};

		inline static std::vector<SDL_Rect> ghost_blue_r{{3, 159, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_blue_l{{37, 159, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_blue_u{{71, 160, 16, 15}};
		inline static std::vector<SDL_Rect> ghost_blue_d{{105, 159, 16, 16}};

		inline static std::vector<SDL_Rect> ghost_orange_r{{3, 177, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_orange_l{{37, 177, 16, 16}};
		inline static std::vector<SDL_Rect> ghost_orange_u{{71, 178, 16, 15}};
		inline static std::vector<SDL_Rect> ghost_orange_d{{105, 177, 16, 16}};

	public:
		Coordinate(/* args */);
		~Coordinate();
};

#endif
