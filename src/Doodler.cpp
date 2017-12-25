#include "Doodler.h"

void Doodler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

Doodler::Doodler(const std::shared_ptr<KeyboardState> &p_keyboardState) : m_p_keyboardState(p_keyboardState)
{
    m_shape.setSize(m_size);
    m_shape.setOrigin(m_size.x / 2, m_size.x / 2);
    m_shape.setPosition(m_position);
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(m_outlineThickness);

    m_size.x += m_outlineThickness;
    m_size.y += m_outlineThickness;
}

void Doodler::updatePosition(const float deltaTime)
{
    const float dtPhysics = deltaTime / MAX_PRECISION_COUNT;
    for (unsigned i = 0; i < MAX_PRECISION_COUNT; ++i)
    {
        setVerticalPosition(MOVE_SPEED, dtPhysics);
        m_timeAccumulator += dtPhysics * TIME_ACCELERATOR;
        const float nextY = getNextY();
        const sf::Vector2f nextPosition = {m_position.x, nextY};
        m_shape.setPosition(nextPosition);
        setFallingState(nextY);
        setPosition(nextPosition);
        checkCollision();
    }
}

void Doodler::checkCollision()
{
    const float currentBottomPosition = getBounds().height;
    const bool isAtZeroLevel = m_areFuzzyEqual(currentBottomPosition, m_floor);
    const bool isGameOverLevel = m_areFuzzyEqual(m_floor, WINDOW_HEIGHT);
    if (isAtZeroLevel && m_isFalling && !isGameOverLevel)
    {
        setNextY();
        m_timeAccumulator = 0;
    }
}

void Doodler::setVerticalPosition(const float nextX, const float deltaTime)
{
    const KeysMap &keysMap = m_p_keyboardState->getKeysMap();
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
    m_position.y = m_floor - m_size.y / 2 - m_outlineThickness;
}

float Doodler::getNextY() const
{
    const float lhs = m_initialSpeed * m_timeAccumulator;
    const auto rhs = static_cast<const float>(0.5 * G * std::pow(m_timeAccumulator, 2));
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
