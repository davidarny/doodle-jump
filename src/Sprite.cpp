#include "Sprite.h"

void Sprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*m_p_sprite, states);
}

Sprite::Sprite(const SpriteOptions &spriteOptions) : m_spriteOptions(spriteOptions)
{
    if (!m_p_texture->loadFromMemory(spriteOptions.data, spriteOptions.length))
    {
        // TODO: handle error
        std::exit(EXIT_FAILURE);
    }
    m_p_texture->setRepeated(spriteOptions.repeat);
    m_p_texture->setSmooth(spriteOptions.smooth);
    m_p_sprite->setTexture(*m_p_texture);
    setSize(spriteOptions.size);
    setOrigin(spriteOptions.size / 2.f);
}
