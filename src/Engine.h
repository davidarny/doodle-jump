#ifndef DOODLE_JUMP_ENGINE_H
#define DOODLE_JUMP_ENGINE_H

#include "consts.h"
#include "Doodler.h"
#include "IEntity.h"

class Engine
{
public:
    explicit Engine(const std::shared_ptr<IEntity> &p_doodler);

    void checkCollision(Entities &entities);

    void addPlatforms(Entities &entities);

    void removePlatforms(Entities &entities);

    const std::function<bool(const std::shared_ptr<IEntity> &)> isDoodler();

    void reset();

private:
    bool m_shouldSetFloor = false;
    float m_floor = static_cast<float>(WINDOW_HEIGHT);
    const std::shared_ptr<IEntity> &m_p_doodler;

    bool processCollision(const std::shared_ptr<IEntity> &p_entity);

    bool intersect(const std::shared_ptr<IEntity> &p_entity) const;
};

#endif //DOODLE_JUMP_ENGINE_H
