#ifndef DOODLE_JUMP_ENGINE_H
#define DOODLE_JUMP_ENGINE_H

#include "consts.h"
#include "Doodler.h"
#include "IEntity.h"

class Engine : public sf::Drawable
{
public:
    explicit Engine(const std::shared_ptr<Doodler> &p_doodler);

    void checkCollision(Entities &entities);

    void addPlatforms(Entities &entities);

    void removePlatforms(Entities &entities);

    const std::function<bool(const std::shared_ptr<IEntity> &)> isDoodler();

private:
    sf::RectangleShape m_platformHitbox;
    sf::RectangleShape m_doodlerHitbox;

    const std::shared_ptr<Doodler> &m_p_doodler;

    float processCollision(const std::shared_ptr<IEntity> &p_entity);

    bool intersect(const std::shared_ptr<IEntity> &p_entity);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //DOODLE_JUMP_ENGINE_H
