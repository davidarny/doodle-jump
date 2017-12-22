#ifndef DOODLE_JUMP_PLATFORM_H
#define DOODLE_JUMP_PLATFORM_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "IPhysicsObject.h"
#include "IEntity.h"
#include "consts.h"

class Platform : public IEntity
{
public:
    Platform();

    ~Platform() override = default;

    void updatePosition(float) override;

    Types getType() const override;

    const sf::Vector2f &getSize() const override;

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_position;

    sf::Vector2f m_size = sf::Vector2f(30.f, 5.f);
    const unsigned m_outlineThickness = 2;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::FloatRect getBounds() const;
};

#endif //DOODLE_JUMP_PLATFORM_H
