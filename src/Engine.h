#ifndef DOODLE_JUMP_ENGINE_H
#define DOODLE_JUMP_ENGINE_H

#include "consts.h"
#include "Doodler.h"
#include "IEntity.h"

class Engine
{
public:
    void checkCollision(Entities &entities);

    void addPlatforms(Entities &entities);

    void removePlatforms(Entities &entities);

private:
    std::shared_ptr<IEntity> m_p_doodler;
    bool m_shouldSetFloor{false};
    float m_floor{static_cast<float>(WINDOW_HEIGHT)};

    const std::function<bool(const std::shared_ptr<IEntity> &)> isDoodler();

    void processCollision(const std::shared_ptr<IEntity> &p_entity);

    bool doesIntersect(const std::shared_ptr<IEntity> &p_entity) const;
};

#endif //DOODLE_JUMP_ENGINE_H
