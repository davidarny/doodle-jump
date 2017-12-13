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

    if (m_position.x + m_size.x > WINDOW_WIDTH)
    {
        m_position.x -= m_size.x;
    }

    if (m_position.x - m_size.x < 0)
    {
        m_position.x += m_size.x;
    }

    m_shape.setSize(m_size);
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(m_outlineThickness);
}

void Platform::updatePosition()
{
    m_shape.setPosition(m_position);
}

TYPES Platform::getType() const
{
    return TYPES::PLATFORM;
}
