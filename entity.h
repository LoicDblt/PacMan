#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <SDL.h>

using EntityPicture = std::vector<SDL_Rect>;

class Entity
{
	private:
		float x_{0};
		float y_{0};
		float width_{0};
		float heigh_{0};
		EntityPicture entityPicture_{};

	public:
		// default constructor
		Entity();

		// alternate constructor
		Entity(		
			float x,
			float y,
			float width,
			float heigh,
			EntityPicture entityPicture
		);

		// copy constructor
		Entity(const Entity& other);

		~Entity();
};

#endif