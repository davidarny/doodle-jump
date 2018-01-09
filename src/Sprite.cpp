#include "Sprite.h"

Sprite::Sprite(const SpriteOptions &options)
{
    m_size = sf::Vector2f(options.size);

    if (!m_p_texture->loadFromMemory(options.data, options.length))
    {
        // TODO: handle error
        std::exit(EXIT_FAILURE);
    }
    m_p_texture->setRepeated(options.repeat);
    m_p_texture->setSmooth(options.smooth);
    m_p_sprite->setTexture(*m_p_texture);

    m_shape.setFillColor(sf::Color::Red);
    m_shape.setSize(options.size);

    setOrigin(options.size / 2.f);
}

const sf::Vector2f &Sprite::getSize() const
{
    return m_size;
}

sf::FloatRect Sprite::getBoundingCoordinates() const
{
    return sf::FloatRect(getPosition() - getSize() / 2.f, getSize());
}

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if (IS_DEBUG)
    {
        target.draw(m_shape, states);
    }
    target.draw(*m_p_sprite, states);
}

EntityType Sprite::getType() const
{
    return EntityType::Sprite;
}
