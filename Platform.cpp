#include "Platform.h"

void Platform::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

// TODO: use C++11 random library
Platform::Platform()
{
    m_position.x = rand() % WINDOW_WIDTH;
    m_position.y = rand() % WINDOW_HEIGHT;

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
    m_shape.setOrigin(m_size.x / 2, m_size.y / 2);
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(m_outlineThickness);

    m_size.x += m_outlineThickness;
    m_size.y += m_outlineThickness;
}

void Platform::updatePosition(float)
{
    m_shape.setPosition(m_position);
    setPosition(m_position);
}

Types Platform::getType() const
{
    return Types::Platform;
}

const sf::Vector2f &Platform::getSize() const
{
    return m_size;
}

sf::FloatRect Platform::getBounds() const
{
    const float left = m_position.x - m_size.x / 2 - m_outlineThickness;
    const float right = m_position.x + m_size.x / 2 + m_outlineThickness;
    const float top = m_position.y - m_size.y / 2 - m_outlineThickness;
    const float bottom = m_position.y + m_size.y / 2 + m_outlineThickness;
    return sf::FloatRect(left, top, right, bottom);
}
