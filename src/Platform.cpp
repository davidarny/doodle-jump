#include "Platform.h"

float Platform::multiplier = 1.f;

// TODO: switch to C++11 random library
Platform::Platform()
{
    m_shape.setSize(m_size);
    m_shape.setOrigin(m_size / 2.f);
    m_shape.setFillColor(sf::Color::Red);

    m_position.x = rand() % WINDOW_WIDTH;
    const float min = WINDOW_HEIGHT - multiplier * WINDOW_HEIGHT;
    const float max = -multiplier * WINDOW_HEIGHT;
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
    setRandomBonusSprites();
}

void Platform::updatePosition()
{
    m_shape.setPosition(m_position);
    m_p_sprite->setPosition(m_position);
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
        m_p_sprite = std::make_unique<Sprite>(Sprite({
                                                             Assets::PLATFORM_SPRING.length,
                                                             Assets::PLATFORM_SPRING.data,
                                                             PLATFORM_SPRING_SPRITE_SIZE,
                                                             false, true
                                                     }));
    } else
    {
        m_p_sprite = std::make_unique<Sprite>(Sprite({
                                                             Assets::PLATFORM_TRAMPOLINE.length,
                                                             Assets::PLATFORM_TRAMPOLINE.data,
                                                             PLATFORM_TRAMPOLINE_SPRITE_SIZE,
                                                             false, true
                                                     }));
    }
    m_p_sprite->setOrigin(getOrigin());
    m_p_sprite->setPosition(getPosition());
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
    multiplier = 1.f;
}

void Platform::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IS_DEBUG)
    {
        target.draw(m_shape, states);
    }
    target.draw(*m_p_sprite, states);
}
