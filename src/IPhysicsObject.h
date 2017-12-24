#ifndef DOODLE_JUMP_IPHYSICSOBJECT_H
#define DOODLE_JUMP_IPHYSICSOBJECT_H

#include <SFML/Graphics.hpp>
#include "consts.h"
#include "enums.h"

class IPhysicsObject
{
public:
    virtual const sf::Vector2f &getSize() const = 0;

    virtual EntityType getType() const = 0;

    virtual sf::FloatRect getBounds() const = 0;
};

#endif //DOODLE_JUMP_IPHYSICSOBJECT_H
