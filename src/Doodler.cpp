#include "Doodler.h"

Doodler::Doodler(StateMediator &stateMediator) : m_stateMediator(stateMediator)
{
    m_shape.setSize(m_size);
    m_shape.setOrigin(m_size / 2.f);
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setPosition(m_position);

    setPosition(m_position);
    setOrigin(m_size / 2.f);
}

void Doodler::updatePosition(const float deltaTime)
{
    setHorizontalPosition(MOVE_SPEED, deltaTime);
    m_timeAccumulator += deltaTime * TIME_ACCELERATOR;
    const sf::Vector2f nextPosition = {m_position.x, getNextY()};
    setFallingState(nextPosition.y);
    m_shape.setPosition(nextPosition);
    m_doodlerSprite.setPosition(nextPosition);
    setPosition(nextPosition);
    checkCollision();
    if (m_timeAccumulator / TIME_ACCELERATOR > DEAD_TIME)
    {
        m_stateMediator.setState(State::GameOver);
        m_timeAccumulator = 0.f;
    }
}

void Doodler::checkCollision()
{
    const bool shouldCheck = m_floor != -1.f;
    if (!shouldCheck || !m_isFalling)
    {
        return;
    }
    const bool isAtFloorLevel = areFuzzyEqual()(getBounds().height, m_floor);
    if (isAtFloorLevel)
    {
        setNextY(m_floor);
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
    if (IS_DEBUG)
    {
        target.draw(m_shape, states);
    }
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
        m_doodlerSprite.setScale({-1, 1});
    } else if (event.key.code == sf::Keyboard::Right)
    {
        m_doodlerSprite.setScale({1.f, 1.f});
    }
}
