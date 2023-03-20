#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <SDL.h>

#include <iostream>

class Entity {
	private:
		float x_{0};
		float y_{0};
		float width_{0};
		float heigh_{0};
		SDL_Rect entityPicture_{};

	/* Constructors */
	public:
		// Default constructor
		Entity() = default;

		// Alternate constructor
		Entity(
			float x,
			float y,
			float width,
			float heigh,
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
			return x_;
		}
		inline float getY() const {
			return y_;
		}

	/* Setter */
	public:
		inline void setEntityPic(SDL_Rect entityPicture) {
			entityPicture_ = entityPicture;
		}
};

#endif