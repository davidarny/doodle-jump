#ifndef DOODLE_JUMP_ENGINE_H
#define DOODLE_JUMP_ENGINE_H

#include <functional>
#include "Doodler.h"
#include "IEntity.h"

class Engine
{
public:
    void checkCollision(Entities &entities);

private:
    std::shared_ptr<IEntity> m_p_doodler;

    const std::function<bool(const std::shared_ptr<IEntity> &)> m_isDoodler = [&](
        const std::shared_ptr<IEntity> &p_entity) -> bool {
        return p_entity->getType() == Types::Doodler;
    };

    const std::function<void(const std::shared_ptr<IEntity> &)> m_applyForEach = [&](
        const std::shared_ptr<IEntity> &p_entity) -> void {
        if (m_p_doodler == nullptr)
        {
            return;
        }
        if (m_isDoodler(p_entity))
        {
            return;
        }
        checkCollision(p_entity);
    };

    void checkCollision(const std::shared_ptr<IEntity> &p_entity);
};

#endif //DOODLE_JUMP_ENGINE_H
