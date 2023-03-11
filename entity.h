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
        Entity();       // default constructor
        Entity(
            float x,
            float y,
            float width,
            float heigh,
            EntityPicture entityPicture
        );   // alternate constructor
        Entity(const Entity& other);       // copy constructor

        ~Entity();  


};

#endif