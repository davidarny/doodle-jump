#ifndef DOODLE_JUMP_IPHYSICSOBJECT_H
#define DOODLE_JUMP_IPHYSICSOBJECT_H

#include <SFML/Graphics.hpp>
#include "consts.h"

class IPhysicsObject
{
public:
    virtual const sf::Vector2f &getBounds() const = 0;

    virtual Types getType() const = 0;
};

#endif //DOODLE_JUMP_IPHYSICSOBJECT_H
