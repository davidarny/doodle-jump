#include "Platform.h"

long long Platform::multiplier = 1;

// TODO: switch to C++11 random library
Platform::Platform()
{
    m_shape.setSize(m_size);

    m_position.x = rand() % WINDOW_WIDTH;
    long long min = WINDOW_HEIGHT - multiplier * WINDOW_HEIGHT;
    long long max = -multiplier * WINDOW_HEIGHT;
    m_position.y = min + (rand() % static_cast<int>(max - min + 1));

    updatePosition();

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

    updatePosition();
    setOrigin(m_size / 2.f);
}

void Platform::updatePosition()
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
    const sf::Vector2f &position = m_shape.getPosition();
    const float left = position.x - m_size.x / 2;
    const float right = position.x + m_size.x / 2;
    const float top = position.y - m_size.y / 2;
    const float bottom = position.y + m_size.y / 2;
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

void Platform::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_platformSprite, states);
}
