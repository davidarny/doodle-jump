#include "Doodler.h"

void Doodler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

Doodler::Doodler()
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
    checkCollision();
    setVerticalPosition(MOVE_SPEED, deltaTime);
    m_timeAccumulator += deltaTime * TIME_ACCELERATOR;
    double nextY = m_position.y - m_initialSpeed * m_timeAccumulator + 0.5 * G * std::pow(m_timeAccumulator, 2);
    const sf::Vector2f nextPosition = {m_position.x, static_cast<float>(nextY)};
    m_shape.setPosition(nextPosition);
    setFalling(static_cast<float>(nextY));
    setPosition(nextPosition);
}

void Doodler::checkCollision()
{
    const float currentBottomPosition = m_shape.getPosition().y + m_size.x / 2 + m_outlineThickness;
    const bool isAtZeroLevel = currentBottomPosition >= m_floor;
    const bool isGameOverLevel = m_floor == WINDOW_HEIGHT;
    if (isAtZeroLevel && m_isFalling && !isGameOverLevel)
    {
        m_timeAccumulator = 0;
    }
}

// TODO: fix side collision check
void Doodler::setVerticalPosition(const float nextX, const float deltaTime)
{
    const KeysMap &keysMap = p_m_keyboardState->getKeysMap();
    const bool isMaxRightPosition = m_position.x + m_size.x / 2 + m_outlineThickness < WINDOW_WIDTH;
    const bool isMaxLeftPosition = m_position.x - m_size.x / 2 - m_outlineThickness > 0;
    if (keysMap.at(sf::Keyboard::Right) && isMaxRightPosition)
    {
        m_position.x += nextX * deltaTime;
    } else if (keysMap.at(sf::Keyboard::Left) && isMaxLeftPosition)
    {
        m_position.x -= nextX * deltaTime;
    }
}

Types Doodler::getType() const
{
    return Types::Doodler;
}

const sf::Vector2f &Doodler::getBounds() const
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
    m_position.y = m_floor - m_size.x / 2 - m_outlineThickness;
}

void Doodler::setFalling(const float nextY)
{
    m_isFalling = getPosition().y - nextY <= 0;
}

void Doodler::addKeyboardState(const std::shared_ptr<KeyboardState> p_keyboardState)
{
    p_m_keyboardState = p_keyboardState;
}
