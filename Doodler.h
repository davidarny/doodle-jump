#ifndef DOODLE_JUMP_DOODLER_H
#define DOODLE_JUMP_DOODLER_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "IPhysicsObject.h"
#include "IEntity.h"
#include "consts.h"

class Doodler : public IEntity
{
public:
    Doodler();

    ~Doodler() override = default;

    void updatePosition(float deltaTime) override;

    TYPES getType() const override;

    sf::Vector2f getBounds() const override;

private:
    const sf::Vector2f m_size = sf::Vector2f(35.f, 50.f);
    const float m_outlineThickness = 2;
    const float m_initialSpeed = 75.f;
    float m_timeAccumulator = 0.f;

    sf::Vector2f m_position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - m_size.x / 2 - m_outlineThickness);
    sf::RectangleShape m_shape;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void checkCollision() override;

    void setVerticalPosition(float nextX, float deltaTime);
};

#endif //DOODLE_JUMP_DOODLER_H
