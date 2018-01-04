#ifndef DOODLE_JUMP_BUTTON_H
#define DOODLE_JUMP_BUTTON_H

#include <SFML/Graphics.hpp>
#include <memory>

struct ButtonOptions
{
    sf::Vector2f size;
    sf::Vector2f position;
    std::string text;
    unsigned textSize;
    sf::Color fillColor;
    sf::Color outlineColor;
    unsigned outlineThickness;
    sf::Color textColor;
    sf::Font font;
};

class Button : public sf::Drawable
{
public:
    Button();

    explicit Button(ButtonOptions &buttonOptions);

    const sf::RectangleShape &getShape() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::RectangleShape m_shape;
    sf::Text m_text;
    std::shared_ptr<sf::Font> m_p_font;
};

#endif //DOODLE_JUMP_BUTTON_H
