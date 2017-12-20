#include "Engine.h"

void Engine::checkCollision(Entities &entities)
{
    m_shouldSetFloor = false;

    m_p_doodler = *std::find_if(entities.begin(), entities.end(), m_isDoodler);
    std::for_each(entities.begin(), entities.end(), m_applyForEach);

    if (m_shouldSetFloor)
    {
        m_p_doodler->setFloor(m_floor);
    } else
    {
        m_p_doodler->setFloor(WINDOW_HEIGHT);
    }
}

void Engine::processCollision(const std::shared_ptr<IEntity> &p_entity)
{
    if (doesIntersect(p_entity) && !m_shouldSetFloor)
    {
        m_shouldSetFloor = true;
        m_floor = p_entity->getPosition().y - p_entity->getBounds().y;
    }
}

// TODO: adjust intersection check
bool Engine::doesIntersect(const std::shared_ptr<IEntity> &p_entity) const
{
    return !(m_p_doodler->getPosition().x + m_p_doodler->getBounds().x < p_entity->getPosition().x ||
             p_entity->getPosition().x + p_entity->getBounds().x < m_p_doodler->getPosition().x ||
             m_p_doodler->getPosition().y + m_p_doodler->getBounds().y < p_entity->getBounds().y ||
             p_entity->getPosition().y + p_entity->getBounds().y < m_p_doodler->getPosition().y);
}
