#ifndef DOODLE_JUMP_ENTITY_H
#define DOODLE_JUMP_ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "consts.h"

using KeysMap = std::map<sf::Keyboard::Key, bool>;

class Entity : public sf::Drawable, public sf::Transformable
{
private:
    virtual void checkCollision() {};

public:
    KeysMap m_keysMap;

    virtual void updatePosition(float) {};

    virtual void updatePosition() {};

    virtual TYPES getType() const = 0;
};

using Entities = std::vector<std::shared_ptr<Entity>>;

#endif //DOODLE_JUMP_ENTITY_H
