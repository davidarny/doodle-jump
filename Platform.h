#ifndef DOODLE_JUMP_PLATFORM_H
#define DOODLE_JUMP_PLATFORM_H

#include "Entity.h"
#include "consts.h"

class Platform : public Entity
{
private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_position;

    const sf::Vector2f m_size = sf::Vector2f(30.f, 5.f);
    const unsigned m_outlineThickness = 2;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    Platform();

    ~Platform() override = default;

    void updatePosition() override;

    TYPES getType() const override;
};

#endif //DOODLE_JUMP_PLATFORM_H
