#include "Platform.h"

float Platform::multiplier = 1.f;

// TODO: switch to C++11 random library
Platform::Platform()
{
    setRandomBonusSprites();

    m_shape.setSize(m_size);
    m_shape.setOrigin(m_size / 2.f);
    m_shape.setFillColor(sf::Color::Red);

    const float minX = m_size.x / 2;
    const float maxX = WINDOW_WIDTH - m_size.x / 2;
    m_position.x = minX + (rand() % static_cast<int>(maxX - minX + 1));
    const float minY = WINDOW_HEIGHT - multiplier * WINDOW_HEIGHT;
    const float maxY = -multiplier * WINDOW_HEIGHT;
    m_position.y = minY + (rand() % static_cast<int>(maxY - minY + 1));

    updatePosition();
}

void Platform::updatePosition()
{
    setPosition(m_position);
}

void Platform::setRandomBonusSprites()
{
    if (rand() % PLATFORM_COUNT != 0)
    {
        return;
    }
    if (rand() % 3 > 0)
    {
        m_size = PLATFORM_SPRING_SPRITE_SIZE;
        m_p_sprite = std::make_unique<Sprite>(Sprite({
                                                             Assets::PLATFORM_SPRING.length,
                                                             Assets::PLATFORM_SPRING.data,
                                                             PLATFORM_SPRING_SPRITE_SIZE,
                                                             false, true
                                                     }));
    } else
    {
        m_size = PLATFORM_TRAMPOLINE_SPRITE_SIZE;
        m_p_sprite = std::make_unique<Sprite>(Sprite({
                                                             Assets::PLATFORM_TRAMPOLINE.length,
                                                             Assets::PLATFORM_TRAMPOLINE.data,
                                                             PLATFORM_TRAMPOLINE_SPRITE_SIZE,
                                                             false, true
                                                     }));
    }
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
    const sf::Vector2f &position = getPosition();
    const float left = position.x - m_size.x / 2;
    const float width = position.x + m_size.x / 2;
    const float top = position.y - m_size.y / 2;
    const float height = position.y + m_size.y / 2;
    return sf::FloatRect(left, top, width, height);
}

void Platform::increment()
{
    ++multiplier;
}

void Platform::reset()
{
    multiplier = 1.f;
}

void Platform::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if (IS_DEBUG)
    {
        target.draw(m_shape, states);
    }
    target.draw(*m_p_sprite, states);
}
