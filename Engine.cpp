#include "Engine.h"

void Engine::checkCollision(Entities &entities)
{
    m_p_doodler = *std::find_if(entities.begin(), entities.end(), m_isDoodler);
    std::for_each(entities.begin(), entities.end(), m_applyForEach);
}

void Engine::checkCollision(const std::shared_ptr<IEntity> &p_entity)
{
    (void) &p_entity;
    // TODO: do stuff
}
