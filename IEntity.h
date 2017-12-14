#ifndef DOODLE_JUMP_ENTITY_H
#define DOODLE_JUMP_ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "IPhysicsObject.h"
#include "consts.h"

using KeysMap = std::map<sf::Keyboard::Key, bool>;

class IEntity : public IPhysicsObject, public sf::Drawable, public sf::Transformable
{
public:
    KeysMap m_keysMap;

    virtual void updatePosition(float deltaTime) { (void) &deltaTime; };

private:
    virtual void checkCollision() {};
};

using Entities = std::vector<std::shared_ptr<IEntity>>;

#endif //DOODLE_JUMP_ENTITY_H
