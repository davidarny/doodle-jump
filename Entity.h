#ifndef DOODLE_JUMP_ENTITY_H
#define DOODLE_JUMP_ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>

class Entity : public sf::Drawable, public sf::Transformable
{
private:
    virtual void checkCollision() = 0;

public:
    virtual void updatePosition(float deltaTime) = 0;
};

using Entities = std::vector<std::shared_ptr<Entity>>;

#endif //DOODLE_JUMP_ENTITY_H
