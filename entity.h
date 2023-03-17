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
		// default constructor
		Entity() = default;

		// alternate constructor
		Entity(
			float x,
			float y,
			float width,
			float heigh,
			SDL_Rect entityPicture
		);

		// copy constructor
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
};

#endif