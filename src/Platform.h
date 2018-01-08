#ifndef DOODLE_JUMP_PLATFORM_H
#define DOODLE_JUMP_PLATFORM_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "IPhysicsObject.h"
#include "IEntity.h"
#include "Sprite.h"
#include "Assets.h"
#include "consts.h"

class Platform : public IEntity
{
public:
    Platform();

    void updatePosition() override;

    EntityType getType() const override;

    const sf::Vector2f &getSize() const override;

    static void increment();

    static void reset();

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_position;
    sf::Vector2f m_size = PLATFORM_SPRITE_SIZE;
    Sprite m_platformSprite = Sprite(SpriteOptions{Assets::PLATFORM.length,
                                                   Assets::PLATFORM.data,
                                                   PLATFORM_SPRITE_SIZE,
                                                   false, true});

    static long long multiplier;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::FloatRect getBounds() const override;
};

#endif //DOODLE_JUMP_PLATFORM_H
