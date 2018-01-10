#ifndef DOODLE_JUMP_MENU_H
#define DOODLE_JUMP_MENU_H

#include <SFML/Graphics.hpp>
#include "States.h"
#include "Sprite.h"
#include "consts.h"

class Menu : public sf::Drawable
{
public:
    explicit Menu(States &stateMediator);

    void eventHandler(sf::Event &event, const sf::Vector2f &mousePosition, const std::function<void()> &callback);

    void updateMenu();

private:
    States &m_states;
    sf::Font m_font;
    sf::Text m_logo;
    sf::Text m_score;
    std::unique_ptr<Sprite> m_p_startButton;
    std::unique_ptr<Sprite> m_p_exitButton;
    std::unique_ptr<Sprite> m_p_restartButton;

    void createStartButton();

    void createRestartButton();

    void createExitButton();

    void createLogo();

    void createScore();

    void updateScoreOrigin();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //DOODLE_JUMP_MENU_H
