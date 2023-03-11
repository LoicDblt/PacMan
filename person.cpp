#include "person.h"

Person::Person(){};

Person::Person(
    float x,
    float y,
    float width,
    float heigh,
    EntityPicture entityPicture,
    float speed,
    Direction direction
):
    Entity{x,y,width,heigh,entityPicture},
    speed_{speed},
    direction_{direction}
{};