#include "Platform.h"

long long Platform::multiplier = 1;

void Platform::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

// TODO: use C++11 random library
Platform::Platform()
{
    m_position.x = rand() % WINDOW_WIDTH;
    long long min = WINDOW_HEIGHT - multiplier * WINDOW_HEIGHT;
    long long max = -multiplier * WINDOW_HEIGHT;
    m_position.y = min + (rand() % static_cast<int>(max - min + 1));

    const sf::FloatRect bounds = getBounds();
    const bool isOverRightSide = bounds.width > WINDOW_WIDTH;
    const bool isOverLeftSide = bounds.left < 0;

    if (isOverRightSide)
    {
        m_position.x -= m_size.x;
    }

    if (isOverLeftSide)
    {
        m_position.x += m_size.x;
    }

    m_shape.setSize(m_size);
    m_shape.setPosition(m_position);
    m_shape.setOrigin(m_size.x / 2, m_size.y / 2);
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(m_outlineThickness);

    m_size.x += m_outlineThickness;
    m_size.y += m_outlineThickness;

    setPosition(m_position);
}

void Platform::updatePosition(float)
{
    m_shape.setPosition(m_position);
    setPosition(m_position);
}

EntityType Platform::getType() const
{
    return EntityType::Platform;
}

const sf::Vector2f &Platform::getSize() const
{
    return m_size;
}

sf::FloatRect Platform::getBounds() const
{
    const float left = m_position.x - m_size.x / 2;
    const float right = m_position.x + m_size.x / 2;
    const float top = m_position.y - m_size.y / 2;
    const float bottom = m_position.y + m_size.y / 2;
    return sf::FloatRect(left, top, right, bottom);
}

void Platform::increment()
{
    ++multiplier;
}
