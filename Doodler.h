#ifndef DOODLE_JUMP_DOODLER_H
#define DOODLE_JUMP_DOODLER_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Entity.h"
#include "consts.h"

class Doodler : public Entity
{
private:
    const unsigned m_radius = 25;
    const unsigned m_outlineThickness = 2;
    const float m_initialSpeed = 75.f;
    float m_timeAccumulator = 0.f;

    sf::Vector2f m_position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - m_radius - m_outlineThickness);
    sf::CircleShape m_circle;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void checkCollision() override;

    void setVerticalPosition(float nextX, float deltaTime);

public:
    Doodler();

    ~Doodler() override = default;

    void updatePosition(float deltaTime) override;
};

#endif //DOODLE_JUMP_DOODLER_H
