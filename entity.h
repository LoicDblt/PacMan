#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>
#include <SDL.h>


class Entity {
	private:
		SDL_Rect entityPicture_{};

	protected:
		SDL_Rect entityRect_{};

	/* Constructors */
	public:
		// Default constructor
		Entity() = default;

		// Alternate constructor
		Entity(
			SDL_Rect entityRect,
			SDL_Rect entityPicture
		);

		// Copy constructor
		Entity(const Entity& other);

		~Entity();

	/* Getter */
	public:
		inline SDL_Rect getEntityPic() const {
			return entityPicture_;
		}
		inline float getX() const {
			return entityRect_.x;
		}
		inline float getY() const {
			return entityRect_.y;
		}
		inline SDL_Rect& getEntityRect() {
			return entityRect_;
		}

	/* Setter */
	public:
		inline void setEntityPic(SDL_Rect entityPicture) {
			entityPicture_ = entityPicture;
		}
};

#endif