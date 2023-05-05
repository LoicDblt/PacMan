#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <SDL.h>

class Entity {
	/* Variables */
	private:
		SDL_Rect entityPicture_{};

	protected:
		SDL_Rect entityRect_{};


	/* Constructeurs et destructeur */
	public:
		Entity(void) = default;
		~Entity(void) = default;
		Entity(
			SDL_Rect entityRect,
			SDL_Rect entityPicture
		);


	/* Getter */
	public:
		inline SDL_Rect getEntityPic(void) const {
			return entityPicture_;
		}

		inline float getX(void) const {
			return entityRect_.x;
		}

		inline float getY(void) const {
			return entityRect_.y;
		}

		inline SDL_Rect& getEntityRect(void) {
			return entityRect_;
		}


	/* Setter */
	public:
		inline void setEntityPic(SDL_Rect entityPicture) {
			entityPicture_ = entityPicture;
		}
};

#endif