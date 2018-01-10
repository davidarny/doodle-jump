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

    EntityType getType() const override;

    const sf::Vector2f &getSize() const override;

    static void incrementMultiplier();

    static void resetMultiplier();

private:
    EntityType m_type = EntityType::Platform;
    sf::Vector2f m_position;
    sf::Vector2f m_size = PLATFORM_SPRITE_SIZE;
    std::unique_ptr<Sprite> m_p_sprite = std::make_unique<Sprite>(Sprite({
                                                                             Assets::PLATFORM.length,
                                                                             Assets::PLATFORM.data,
                                                                             PLATFORM_SPRITE_SIZE,
                                                                             false, true
                                                                         }));

    static float multiplier;

    void setRandomBonusSprites();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::FloatRect getBoundingCoordinates() const override;
};

#endif //DOODLE_JUMP_PLATFORM_H
