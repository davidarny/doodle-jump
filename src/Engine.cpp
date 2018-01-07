#include "Engine.h"
#include "Platform.h"

void Engine::checkCollision(Entities &entities)
{
    m_shouldSetFloor = false;

    m_p_doodler = *std::find_if(entities.begin(), entities.end(), isDoodler());

    std::for_each(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_entity) -> void {
        if (m_p_doodler == nullptr || isDoodler()(p_entity) || !shouldProcess(p_entity))
        {
            return;
        }
        processCollision(p_entity);
    });

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
    if (doesIntersect(p_entity) && m_p_doodler->getFallingState() && !m_shouldSetFloor)
    {
        m_shouldSetFloor = true;
        m_floor = p_entity->getPosition().y;
    }
}

bool Engine::doesIntersect(const std::shared_ptr<IEntity> &p_entity) const
{
    sf::FloatRect rhs(p_entity->getPosition(), p_entity->getSize());
    sf::FloatRect lhs(m_p_doodler->getPosition(), m_p_doodler->getSize());
    return lhs.intersects(rhs);
}

void Engine::addPlatforms(Entities &entities)
{
    long long int index = std::find_if(entities.begin(), entities.end(), isDoodler()) - entities.begin();
    if (std::size(entities) >= PLATFORM_COUNT * 2 + 1)
    {
        return;
    }
    if (!m_p_doodler->getFallingState())
    {
        Platform::increment();
    }
    for (size_t i = 0; i < PLATFORM_COUNT; ++i)
    {
        std::shared_ptr<Platform> p_platform = std::make_shared<Platform>(Platform());
        entities.push_back(p_platform);
    }
    std::swap(entities.at(static_cast<unsigned long long>(index)), entities.back());
}

void Engine::removePlatforms(Entities &entities)
{
    size_t index = 0;
    entities.erase(
        std::remove_if(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_entity) -> bool {
            const bool isNotPlatform = p_entity->getType() != EntityType::Platform;
            const bool isNotFirstPart = index > PLATFORM_COUNT;
            if (isNotPlatform || m_p_doodler == nullptr || isNotFirstPart)
            {
                return false;
            }
            const float doodlerY = m_p_doodler->getPosition().y;
            const float platformY = p_entity->getPosition().y;
            const float distance = std::abs(doodlerY - platformY);
            const bool isUnderDoodler = doodlerY < platformY;
            ++index;
            return distance > WINDOW_HEIGHT / 2 && isUnderDoodler;
        }),
        entities.end()
    );
}

const std::function<bool(const std::shared_ptr<IEntity> &)> Engine::isDoodler()
{
    return [](const std::shared_ptr<IEntity> &p_entity) -> bool {
        return p_entity != nullptr && p_entity->getType() == EntityType::Doodler;
    };
}

void Engine::reset()
{
    m_shouldSetFloor = false;
    m_floor = static_cast<float>(WINDOW_HEIGHT);
}

bool Engine::shouldProcess(const std::shared_ptr<IEntity> &p_entity)
{
    const float doodlerY = m_p_doodler->getPosition().y;
    const float platformY = p_entity->getPosition().y;
    const float distance = std::abs(doodlerY - platformY);
    return distance <= MAX_PROCESS_DISTANCE;
}
