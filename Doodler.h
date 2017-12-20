#ifndef DOODLE_JUMP_DOODLER_H
#define DOODLE_JUMP_DOODLER_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "IPhysicsObject.h"
#include "IEntity.h"
#include "consts.h"
#include "KeyboardState.h"

class Doodler : public IEntity
{
public:
    explicit Doodler(KeyboardState &m_keyboardState);

    ~Doodler() override = default;

    void updatePosition(float deltaTime) override;

    Types getType() const override;

    const sf::Vector2f &getBounds() const override;

private:
    KeyboardState &m_keyboardState;

    sf::Vector2f m_size = sf::Vector2f(35.f, 50.f);
    const float m_outlineThickness = 2;
    const float m_initialSpeed = 75.f;
    float m_timeAccumulator = 0.f;
    float m_floor = static_cast<float>(WINDOW_HEIGHT);
    bool m_isFalling = false;

    sf::Vector2f m_position = sf::Vector2f(WINDOW_WIDTH / 2, m_floor - m_size.x / 2 - m_outlineThickness);
    sf::RectangleShape m_shape;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void checkCollision() override;

    void setVerticalPosition(float nextX, float deltaTime);

    void setFloor(float nextFloor) override;

    void setFalling(float nextY);
};

#endif //DOODLE_JUMP_DOODLER_H
