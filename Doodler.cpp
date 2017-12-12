#include "Doodler.h"

void Doodler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_circle, states);
}

Doodler::Doodler()
{
    m_circle.setRadius(m_radius);
    m_circle.setOrigin(m_radius, m_radius);
    m_circle.setPosition(m_position);
    m_circle.setFillColor(sf::Color::Red);
    m_circle.setOutlineColor(sf::Color::Black);
    m_circle.setOutlineThickness(m_outlineThickness);
}

void Doodler::updatePosition(float deltaTime)
{
    checkCollision();
    m_timeAccumulator += deltaTime * TIME_ACCELERATOR;
    double nextY = m_position.y - m_initialSpeed * m_timeAccumulator + 0.5 * G * std::pow(m_timeAccumulator, 2);
    const sf::Vector2f nextPosition = {m_circle.getPosition().x, static_cast<float>(nextY)};
    m_circle.setPosition(nextPosition);
}

void Doodler::checkCollision()
{
    const float currentBottomPosition = m_circle.getPosition().y + m_radius + m_outlineThickness;
    const bool isAtZeroLevel = currentBottomPosition > WINDOW_HEIGHT;
    if (isAtZeroLevel)
    {
        m_timeAccumulator = 0;
    }
}
