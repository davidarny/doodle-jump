#ifndef DOODLE_JUMP_SPRITE_H
#define DOODLE_JUMP_SPRITE_H

#include <SFML/Graphics.hpp>

struct SpriteOptions
{
    const unsigned length;
    const unsigned char *data;
    const sf::Vector2f &size;
    const sf::Vector2f &scale;
    const bool repeat;
    const bool smooth;
};

class Sprite : public sf::RectangleShape
{
public:
    explicit Sprite(const SpriteOptions &spriteOptions);

private:
    std::unique_ptr<sf::Sprite> m_p_sprite = std::make_unique<sf::Sprite>(sf::Sprite());
    std::unique_ptr<sf::Texture> m_p_texture = std::make_unique<sf::Texture>(sf::Texture());
    const SpriteOptions &m_spriteOptions;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};

#endif //DOODLE_JUMP_SPRITE_H
