#ifndef DOODLE_JUMP_MENU_H
#define DOODLE_JUMP_MENU_H

#include <SFML/Graphics.hpp>
#include "StateMediator.h"
#include "consts.h"

struct Button
{
    sf::RectangleShape m_shape;
    sf::Text m_text;
    const unsigned m_textSize{BUTTON_TEXT_SIZE};
};

// TODO: refactor code
// delegate init of text to setText(...params)
// delegate init of rect to setRect(...params)
class Menu : public sf::Drawable
{
public:
    explicit Menu(StateMediator &stateMediator);

    void eventHandler(sf::Event &event, const sf::Vector2f &mousePosition);

private:
    StateMediator &m_stateMediator;

    sf::Font m_font;

    sf::Text m_logo;

    Button m_startButton;
    Button m_exitButton;

    void initStartButton();

    void initExitButton();

    void initLogo();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //DOODLE_JUMP_MENU_H
