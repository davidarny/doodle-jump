#include "Platform.h"

long long Platform::multiplier = 1;

void Platform::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_platformSprite, states);
}

// TODO: switch to C++11 random library
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

    setPosition(m_position);
    setOrigin(m_size / 2.f);
}

void Platform::updatePosition(float)
{
    m_shape.setPosition(m_position);
    m_platformSprite.setPosition(m_position);
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

void Platform::reset()
{
    multiplier = 1;
}
