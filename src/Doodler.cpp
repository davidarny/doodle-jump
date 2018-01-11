#include "Doodler.h"

Doodler::Doodler(States &stateMediator) : m_states(stateMediator)
{
    setPosition(m_position);
}

void Doodler::updatePosition(const float deltaTime)
{
    setHorizontalPosition(MOVE_SPEED, deltaTime);
    updateTimeAccumulators(deltaTime);
    sf::Vector2f nextPosition = {m_position.x, getNextY()};
    setFallingState(nextPosition.y);
    setPosition(nextPosition);
    checkCollision();
    checkGameOver();
}

void Doodler::checkCollision()
{
    const bool shouldCheck = m_intersection != WINDOW_HEIGHT * 2;
    if (!shouldCheck || !m_isFalling)
    {
        return;
    }

    const float lhs = getPosition().y + getSize().y / 2;
    const float rhs = std::abs(std::abs(lhs) - std::abs(m_intersection));

    const bool isAtFloorLevel = int(lhs) == int(m_intersection) ||
                                std::ceil(lhs) == std::ceil(m_intersection) ||
                                std::floor(lhs) == std::floor(m_intersection) ||
                                (rhs < COLLISION_TOLERANCE && rhs > 0.f);

    if (isAtFloorLevel)
    {
        checkBonus();
        setNextY(m_intersection);
        resetTimeAccumulators();
    }
}

void Doodler::checkBonus()
{
    if (m_speed != DOODLER_SPEED)
    {
        m_speed = DOODLER_SPEED;
    }

    if (m_bonus == EType::PLATFORM_BONUS_SPRING)
    {
        m_speed = DOODLER_SPEED * 1.5f;
        m_bonus = EType::PLATFORM_DEFAULT;
    }

    if (m_bonus == EType::PLATFORM_BONUS_TRAMPOLINE)
    {
        m_speed = DOODLER_SPEED * 3;
        m_bonus = EType::PLATFORM_DEFAULT;
    }
}

void Doodler::setHorizontalPosition(const float nextX, const float deltaTime)
{
    const KeysMap &keysMap = m_states.getKeysMap();
    const sf::Vector2f &size = getSize();
    const sf::FloatRect bounds = getBoundingCoordinates();
    const bool isMaxRightPosition = bounds.width - size.x / 2 > WINDOW_WIDTH;
    const bool isMaxLeftPosition = bounds.left + size.x / 2 < 0;
    if (keysMap.at(sf::Keyboard::Right))
    {
        if (isMaxRightPosition)
        {
            m_position.x = 0.f;
        } else
        {
            m_position.x += nextX * deltaTime;
        }
    } else if (keysMap.at(sf::Keyboard::Left))
    {
        if (isMaxLeftPosition)
        {
            m_position.x = WINDOW_WIDTH;
        } else
        {
            m_position.x -= nextX * deltaTime;
        }
    }
}

EType Doodler::getType() const
{
    return EType::DOODLER;
}

const sf::Vector2f &Doodler::getSize() const
{
    return m_size;
}

void Doodler::setPlatformIntersection(float nextIntersection)
{
    if (!m_isFalling)
    {
        return;
    }
    m_intersection = nextIntersection;
}

void Doodler::setFallingState(const float nextY)
{
    m_isFalling = getPosition().y - nextY <= 0;
}

bool Doodler::getFallingState() const
{
    return m_isFalling;
}

void Doodler::setNextY(const float nextY)
{
    m_position.y = nextY - m_size.y / 2;
}

float Doodler::getNextY() const
{
    const float lhs = m_speed * m_jumpTimeAccumulator;
    const auto rhs = static_cast<float>(0.5 * G * std::pow(m_jumpTimeAccumulator, 2));
    return m_position.y - lhs + rhs;
}

sf::FloatRect Doodler::getBoundingCoordinates() const
{
    const sf::Vector2f &position = getPosition();
    const float left = position.x - m_size.x / 2;
    const float width = position.x + m_size.x / 2;
    const float top = position.y - m_size.x / 2;
    const float height = position.y + m_size.y / 2;
    return sf::FloatRect(left, top, width, height);
}

void Doodler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_spite, states);
}

void Doodler::eventHandler(const sf::Event &event)
{
    if (event.type != sf::Event::KeyPressed)
    {
        return;
    }
    if (event.key.code == sf::Keyboard::Left)
    {
        setScale({-1.f, 1.f});
    } else if (event.key.code == sf::Keyboard::Right)
    {
        setScale({1.f, 1.f});
    }
}

void Doodler::setBonusType(EType nextType)
{
    m_bonus = nextType;
}

void Doodler::resetTimeAccumulators()
{
    m_jumpTimeAccumulator = 0.f;
    m_fallTimeAccumulator = 0.f;
}

void Doodler::checkGameOver()
{
    const bool isOverDeadTime = m_fallTimeAccumulator / TIME_ACCELERATOR > DEAD_TIME;
    if (isOverDeadTime)
    {
        m_states.setState(EState::GAME_OVER);
        resetTimeAccumulators();
    }
}

void Doodler::updateTimeAccumulators(const float deltaTime)
{
    m_jumpTimeAccumulator += deltaTime * TIME_ACCELERATOR;
    if (m_isFalling)
    {
        m_fallTimeAccumulator += deltaTime * TIME_ACCELERATOR;
    }
}

