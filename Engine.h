#ifndef DOODLE_JUMP_ENGINE_H
#define DOODLE_JUMP_ENGINE_H

#include <functional>
#include "Doodler.h"
#include "IEntity.h"

template<typename T, class R>
using Lambda = std::function<T(const std::shared_ptr<R> &)>;

class Engine
{
public:
    void checkCollision(Entities &entities);

private:
    std::shared_ptr<IEntity> m_p_doodler;
    bool m_shouldSetFloor = false;
    float m_floor = WINDOW_HEIGHT;

    const Lambda<bool, IEntity> m_isDoodler = [&](const std::shared_ptr<IEntity> &p_entity) -> bool {
        return p_entity->getType() == Types::Doodler;
    };

    const Lambda<void, IEntity> m_applyForEach = [&](const std::shared_ptr<IEntity> &p_entity) -> void {
        if (m_p_doodler == nullptr || m_isDoodler(p_entity))
        {
            return;
        }
        processCollision(p_entity);
    };

    void processCollision(const std::shared_ptr<IEntity> &p_entity);

    bool doesIntersect(const std::shared_ptr<IEntity> &p_entity) const;
};

#endif //DOODLE_JUMP_ENGINE_H
