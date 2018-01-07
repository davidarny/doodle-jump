#ifndef DOODLE_JUMP_ENTITY_H
#define DOODLE_JUMP_ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "IPhysicsObject.h"
#include "consts.h"

class IEntity : public IPhysicsObject, public sf::Drawable, public sf::Transformable
{
public:
    virtual void updatePosition(float deltaTime) { (void) &deltaTime; };

    virtual void updatePosition() {};

    virtual void setFloor(float nextFloor) { (void) &nextFloor; };

    virtual bool getFallingState() const { return false; };

    virtual void eventHandler(const sf::Event &event) { (void) &event; };

private:
    virtual void checkCollision() {};
};

using Entities = std::vector<std::shared_ptr<IEntity>>;

#endif //DOODLE_JUMP_ENTITY_H
