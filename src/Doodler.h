#ifndef DOODLE_JUMP_DOODLER_H
#define DOODLE_JUMP_DOODLER_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Assets.h"
#include "Sprite.h"
#include "IPhysicsObject.h"
#include "IEntity.h"
#include "consts.h"
#include "KeyboardState.h"
#include "States.h"

class Doodler : public IEntity
{
public:
    explicit Doodler(States &stateMediator);

    void updatePosition(float deltaTime) override;

    EType getType() const override;

    const sf::Vector2f &getSize() const override;

    bool getFallingState() const override;

    void setPlatformIntersection(float nextIntersection) override;

    void setBonusType(EType nextType);

    void eventHandler(const sf::Event &event) override;

private:
    float m_timeAccumulator = 0.f;
    bool m_isFalling = false;
    float m_speed = DOODLER_SPEED;
    float m_intersection = static_cast<float>(WINDOW_HEIGHT);
    EType m_bonus = EType::PLATFORM_DEFAULT;
    States &m_states;
    sf::Vector2f m_size = DOODLER_SPRITE_SIZE;
    sf::Vector2f m_position = sf::Vector2f(WINDOW_WIDTH / 2, m_intersection - m_size.x / 2);
    Sprite m_spite = Sprite({
                                Assets::DOODLER.length,
                                Assets::DOODLER.data,
                                DOODLER_SPRITE_SIZE,
                                false, true
                            });

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void setHorizontalPosition(float nextX, float deltaTime);

    void setFallingState(float nextY);

    void checkCollision() override;

    void checkBonus();

    sf::FloatRect getBoundingCoordinates() const override;

    float getNextY() const;

    void setNextY(float nextY);
};

#endif //DOODLE_JUMP_DOODLER_H
