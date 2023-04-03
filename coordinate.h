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
		*/
		
		inline static std::vector<SDL_Rect> pac_b{{3, 89, 14, 15}};
		inline static std::vector<SDL_Rect> pac_r{{20, 89, 14, 15}, {35, 89, 10, 15}};
		inline static std::vector<SDL_Rect> pac_l{{47, 89, 14, 15}, {63, 89, 10, 15}};
		inline static std::vector<SDL_Rect> pac_d{{109, 89, 16, 16}, {126, 94, 16, 11}};
		inline static std::vector<SDL_Rect> pac_u{{75, 89, 16, 16}, {92, 94, 16, 11}};
		
		inline static std::vector<SDL_Rect> ghost_red_r{{3, 123, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_red_l{{37, 123, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_red_d{{105, 123, 18, 15}};
		inline static std::vector<SDL_Rect> ghost_red_u{{71, 123, 15, 15}};

		inline static std::vector<SDL_Rect> ghost_pink_r{{3, 142, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_pink_l{{37, 142, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_pink_d{{105, 142, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_pink_u{{71, 142, 15, 15}};

		inline static std::vector<SDL_Rect> ghost_blue_r{{3, 159, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_blue_l{{37, 159, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_blue_d{{105, 159, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_blue_u{{71, 159, 15, 15}};

		inline static std::vector<SDL_Rect> ghost_orange_r{{3, 177, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_orange_l{{37, 177, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_orange_d{{105, 177, 15, 15}};
		inline static std::vector<SDL_Rect> ghost_orange_u{{71, 177, 15, 15}};
	
	public:
		Coordinate(/* args */);
		~Coordinate();
};

#endif