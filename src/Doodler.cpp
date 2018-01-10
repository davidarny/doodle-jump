#include "Doodler.h"

Doodler::Doodler(States &stateMediator) : m_states(stateMediator)
{
    setPosition(m_position);
}

void Doodler::updatePosition(const float deltaTime)
{
    setHorizontalPosition(MOVE_SPEED, deltaTime);
    m_timeAccumulator += deltaTime * TIME_ACCELERATOR;
    sf::Vector2f nextPosition = {m_position.x, getNextY()};
    setFallingState(nextPosition.y);
    setPosition(nextPosition);
    checkCollision();

    const bool isOverDeadTime = m_timeAccumulator / TIME_ACCELERATOR > DEAD_TIME;
    if (isOverDeadTime)
    {
        m_states.setState(EState::GAME_OVER);
        m_timeAccumulator = 0.f;
    }
}

void Doodler::checkCollision()
{
    const bool shouldCheck = m_floor != WINDOW_HEIGHT * 2;
    if (!shouldCheck || !m_isFalling)
    {
        return;
    }

    const float lhs = getPosition().y + getSize().y / 2;
    const float rhs = std::abs(std::abs(lhs) - std::abs(m_floor));

    const bool isAtFloorLevel = int(lhs) == int(m_floor) ||
                                std::ceil(lhs) == std::ceil(m_floor) ||
                                std::floor(lhs) == std::floor(m_floor) ||
                                (rhs < COLLISION_TOLERANCE && rhs > 0.f);

    if (isAtFloorLevel)
    {
        setNextY(m_floor);
        m_timeAccumulator = 0.f;
    }
}

void Doodler::setHorizontalPosition(const float nextX, const float deltaTime)
{
    const KeysMap &keysMap = m_states.getKeysMap();
    const sf::FloatRect bounds = getBoundingCoordinates();
    const bool isMaxRightPosition = bounds.width > WINDOW_WIDTH;
    const bool isMaxLeftPosition = bounds.left < 0;
    if (keysMap.at(sf::Keyboard::Right) && !isMaxRightPosition)
    {
        m_position.x += nextX * deltaTime;
    } else if (keysMap.at(sf::Keyboard::Left) && !isMaxLeftPosition)
    {
        m_position.x -= nextX * deltaTime;
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

void Doodler::setPlatformIntersection(float nextFloor)
{
    if (!m_isFalling)
    {
        return;
    }
    m_floor = nextFloor;
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
    const float lhs = m_initialSpeed * m_timeAccumulator;
    const auto rhs = static_cast<float>(0.5 * G * std::pow(m_timeAccumulator, 2));
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
