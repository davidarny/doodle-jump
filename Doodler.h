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
    Doodler();

    ~Doodler() override = default;

    void updatePosition(float deltaTime) override;

    Types getType() const override;

    const sf::Vector2f &getBounds() const override;

    void addKeyboardState(std::shared_ptr<KeyboardState> p_keyboardState);

    bool getFallingState() const override;

    void setFallingState(float nextY);

    void setFloor(float nextFloor) override;

private:
    std::shared_ptr<KeyboardState> m_p_keyboardState;

    sf::Vector2f m_size = sf::Vector2f(35.f, 50.f);
    const float m_outlineThickness = 2;
    const float m_initialSpeed = 75.f;
    float m_timeAccumulator = 0.f;
    float m_floor = static_cast<float>(WINDOW_HEIGHT);
    bool m_isFalling = false;

    sf::Vector2f m_position = sf::Vector2f(WINDOW_WIDTH / 2, m_floor - m_size.x / 2 - m_outlineThickness);
    sf::RectangleShape m_shape;

    const Lambda<bool(float, float)> m_areCloseAbsolute = [&](float lhs, float rhs) -> bool {
        constexpr float tolerance = 0.001f;
        return std::abs(lhs - rhs) < tolerance;
    };

    const Lambda<bool(float, float)> m_areCloseRelative = [&](float lhs, float rhs) -> bool {
        constexpr float tolerance = 0.001f;
        return std::abs((lhs - rhs) / rhs) < tolerance;
    };

    const Lambda<bool(float, float)> m_areFuzzyEqual = [&](float lhs, float rhs) -> bool {
        if (std::abs(rhs) > 1.f)
        {
            return m_areCloseRelative(lhs, rhs);
        }
        return m_areCloseAbsolute(lhs, rhs);
    };

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void checkCollision() override;

    void setVerticalPosition(float nextX, float deltaTime);
};

#endif //DOODLE_JUMP_DOODLER_H
