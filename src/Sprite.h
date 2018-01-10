#ifndef DOODLE_JUMP_SPRITE_H
#define DOODLE_JUMP_SPRITE_H

#include <SFML/Graphics.hpp>
#include "IPhysicsObject.h"

struct SpriteOptions
{
    const size_t length;
    const unsigned char *data;
    const sf::Vector2f size;
    const bool repeat;
    const bool smooth;
};

class Sprite : public IPhysicsObject, public sf::Drawable, public sf::Transformable
{
public:
    explicit Sprite(const SpriteOptions &options);

    const sf::Vector2f &getSize() const override;

    EType getType() const override;

    sf::FloatRect getBoundingCoordinates() const override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Vector2f m_size;
    sf::RectangleShape m_shape;
    std::unique_ptr<sf::Sprite> m_p_sprite = std::make_unique<sf::Sprite>(sf::Sprite());
    std::unique_ptr<sf::Texture> m_p_texture = std::make_unique<sf::Texture>(sf::Texture());

};

#endif //DOODLE_JUMP_SPRITE_H
