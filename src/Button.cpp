#include "Button.h"

Button::Button(ButtonOptions &buttonOptions)
{
    m_shape.setSize(buttonOptions.size);
    m_shape.setPosition(buttonOptions.position);
    m_shape.setOrigin(buttonOptions.size.x / 2, buttonOptions.size.y / 2);
    m_shape.setFillColor(buttonOptions.fillColor);
    m_shape.setOutlineColor(buttonOptions.outlineColor);
    m_shape.setOutlineThickness(buttonOptions.outlineThickness);

    m_p_font = std::make_shared<sf::Font>(sf::Font(buttonOptions.font));
    m_text.setFont(*m_p_font);
    m_text.setString(buttonOptions.text);
    m_text.setCharacterSize(buttonOptions.textSize);
    m_text.setFillColor(buttonOptions.textColor);
    const sf::FloatRect &bounds = m_text.getLocalBounds();
    const sf::Vector2f origin = {bounds.left + bounds.width / 2, bounds.top + bounds.height / 2};
    m_text.setOrigin(origin);
    m_text.setPosition(buttonOptions.position);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
    target.draw(m_text, states);
}

const sf::RectangleShape &Button::getShape() const
{
    return m_shape;
}

Button::Button() = default;
