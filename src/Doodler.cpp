#include "Doodler.h"

Doodler::Doodler(StateMediator &stateMediator) : m_stateMediator(stateMediator)
{
    m_shape.setSize(m_size);
    m_shape.setOrigin(m_size / 2.f);
    m_shape.setPosition(m_position);

    setPosition(m_position);
    setOrigin(m_size / 2.f);
}

void Doodler::updatePosition(const float deltaTime)
{
    const float dtPhysics = deltaTime / MAX_PRECISION_COUNT;
    for (unsigned i = 0; i < MAX_PRECISION_COUNT; ++i)
    {
        setHorizontalPosition(MOVE_SPEED, dtPhysics);
        m_timeAccumulator += dtPhysics * TIME_ACCELERATOR;
        const float nextY = getNextY();
        const sf::Vector2f nextPosition = {m_position.x, nextY};
        m_shape.setPosition(nextPosition);
        setFallingState(nextY);
        setPosition(nextPosition);
        m_doodlerSprite.setPosition(nextPosition);
        checkCollision();
    }
    if (m_timeAccumulator / TIME_ACCELERATOR > DEAD_TIME)
    {
        m_stateMediator.setState(State::GameOver);
        m_timeAccumulator = 0.f;
    }
}

void Doodler::checkCollision()
{
    const float currentBottomPosition = getBounds().height;
    const bool isAtZeroLevel = areFuzzyEqual()(currentBottomPosition, m_floor);
    const bool isGameOverLevel = areFuzzyEqual()(m_floor, WINDOW_HEIGHT);
    if (isAtZeroLevel && m_isFalling && !isGameOverLevel)
    {
        setNextY();
        m_timeAccumulator = 0;
    }
}

void Doodler::setHorizontalPosition(const float nextX, const float deltaTime)
{
    const KeysMap &keysMap = m_stateMediator.getKeysMap();
    const sf::FloatRect bounds = getBounds();
    const bool isMaxRightPosition = bounds.width < WINDOW_WIDTH;
    const bool isMaxLeftPosition = bounds.left > 0;
    if (keysMap.at(sf::Keyboard::Right) && isMaxRightPosition)
    {
        m_position.x += nextX * deltaTime;
    } else if (keysMap.at(sf::Keyboard::Left) && isMaxLeftPosition)
    {
        m_position.x -= nextX * deltaTime;
    }
}

EntityType Doodler::getType() const
{
    return EntityType::Doodler;
}

const sf::Vector2f &Doodler::getSize() const
{
    return m_size;
}

void Doodler::setFloor(const float nextFloor)
{
    if (!m_isFalling)
    {
        return;
    }
    m_floor = nextFloor;
}

void Doodler::setFallingState(float nextY)
{
    m_isFalling = getPosition().y - nextY <= 0;
}

bool Doodler::getFallingState() const
{
    return m_isFalling;
}

void Doodler::setNextY()
{
    m_position.y = m_floor - m_size.y / 2;
}

float Doodler::getNextY() const
{
    const float lhs = m_initialSpeed * m_timeAccumulator;
    const auto rhs = static_cast<float>(0.5 * G * std::pow(m_timeAccumulator, 2));
    return m_position.y - lhs + rhs;
}

sf::FloatRect Doodler::getBounds() const
{
    const sf::Vector2f &position = m_shape.getPosition();
    const float left = position.x - m_size.x / 2;
    const float right = position.x + m_size.x / 2;
    const float top = position.y - m_size.y / 2;
    const float bottom = position.y + m_size.y / 2;
    return sf::FloatRect(left, top, right, bottom);
}

const std::function<bool(float, float)> Doodler::areCloseAbsolute()
{
    return [](float lhs, float rhs) -> bool {
        constexpr float tolerance = 0.001f;
        return std::abs(lhs - rhs) < tolerance;
    };
}

const std::function<bool(float, float)> Doodler::areFuzzyEqual()
{
    return [&](float lhs, float rhs) -> bool {
        if (std::abs(rhs) > 1.f)
        {
            return areCloseRelative()(lhs, rhs);
        }
        return areCloseAbsolute()(lhs, rhs);
    };
}

const std::function<bool(float, float)> Doodler::areCloseRelative()
{
    return [](float lhs, float rhs) -> bool {
        constexpr float tolerance = 0.001f;
        return std::abs((lhs - rhs) / rhs) < tolerance;
    };
}

void Doodler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_doodlerSprite, states);
}

void Doodler::eventHandler(const sf::Event &event)
{
    if (event.type != sf::Event::KeyPressed)
    {
        return;
    }
    if (event.key.code == sf::Keyboard::Left)
    {
        m_doodlerSprite.setScale({-DOODLER_SCALE.x, DOODLER_SCALE.y});
    } else if (event.key.code == sf::Keyboard::Right)
    {
        m_doodlerSprite.setScale(DOODLER_SCALE);
    }
}
