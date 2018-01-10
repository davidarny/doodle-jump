#include "Engine.h"
#include "Platform.h"

Engine::Engine(const std::shared_ptr<Doodler> &p_doodler) : m_p_doodler(p_doodler)
{
    m_doodlerHitbox.setFillColor(sf::Color::Blue);
    m_platformHitbox.setFillColor(sf::Color::Green);
}

void Engine::checkCollision(Entities &entities)
{
    std::vector<float> intersections;

    std::for_each(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_entity) -> void {
        if (isDoodler()(p_entity))
        {
            return;
        }
        intersections.push_back(processCollision(p_entity));
    });

    const float min = *std::min_element(intersections.begin(), intersections.end());

    m_p_doodler->setPlatformIntersection(min);
}

float Engine::processCollision(const std::shared_ptr<IEntity> &p_entity)
{
    if (intersect(p_entity) && m_p_doodler->getFallingState())
    {
        return p_entity->getPosition().y - p_entity->getSize().y / 4;
    }
    return WINDOW_HEIGHT * 2.f;
}

bool Engine::intersect(const std::shared_ptr<IEntity> &p_entity)
{
    const sf::Vector2f &doodlerSize = m_p_doodler->getSize();
    const sf::Vector2f &doodlerPosition = m_p_doodler->getPosition();
    const sf::Vector2f &platformSize = p_entity->getSize();
    const sf::Vector2f &platformPosition = p_entity->getPosition();
    const sf::Vector2f &offset = sf::Vector2f({doodlerSize.x * 0.25f, 0});

    sf::FloatRect rhs(platformPosition - platformSize * 0.5f, platformSize);
    sf::FloatRect lhs;

    const bool isReflected = m_p_doodler->getScale().x == -1.f;
    if (!isReflected)
    {
        lhs = sf::FloatRect(doodlerPosition - doodlerSize * 0.5f + offset * 0.25f, doodlerSize - offset);
    } else
    {
        lhs = sf::FloatRect(doodlerPosition - doodlerSize * 0.5f + offset, doodlerSize - offset * 1.25f);
    }

    const bool isOverPlatform = lhs.top + doodlerSize.y < rhs.top + platformSize.y;
    const bool intersects = lhs.intersects(rhs) && isOverPlatform;

    if (intersects && IS_DEBUG)
    {
        m_doodlerHitbox.setPosition(lhs.left, lhs.top);
        m_doodlerHitbox.setSize({lhs.width, lhs.height});

        m_platformHitbox.setPosition(rhs.left, rhs.top);
        m_platformHitbox.setSize({rhs.width, rhs.height});
    }

    return intersects;
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
        Platform::incrementMultiplier();
    }
    for (size_t i = 0; i < PLATFORM_COUNT; ++i)
    {
        entities.push_back(std::make_shared<Platform>(Platform()));
    }
    std::swap(entities.at(static_cast<unsigned long long>(index)), entities.back());
}

void Engine::removePlatforms(Entities &entities)
{
    size_t index = 0;
    entities.erase(
        std::remove_if(entities.begin(), entities.end(), [&](const std::shared_ptr<IEntity> &p_entity) -> bool {
            const bool isNotPlatform = p_entity->getType() == EType::DOODLER;
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
        return p_entity != nullptr && p_entity->getType() == EType::DOODLER;
    };
}

void Engine::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_doodlerHitbox, states);
    target.draw(m_platformHitbox, states);
}
