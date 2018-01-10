#include <locale>
#include "Menu.h"
#include "Assets.h"

Menu::Menu(States &stateMediator) : m_states(stateMediator)
{
    if (m_font.loadFromMemory(Assets::FONT.data, Assets::FONT.length))
    {
        createLogo();
        createScore();
        createStartButton();
        createRestartButton();
        createExitButton();
    } else
    {
        // TODO: handle error
        std::exit(EXIT_FAILURE);
    }
}

void Menu::createStartButton()
{
    m_p_startButton = std::make_unique<Sprite>(Sprite({
                                                          Assets::PLAY_BUTTON.length,
                                                          Assets::PLAY_BUTTON.data,
                                                          BUTTON_SPRITE_SIZE,
                                                          false, true
                                                      }));
    m_p_startButton->setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.5f});
}

void Menu::createExitButton()
{
    const float topOffset = m_p_startButton->getPosition().y + m_p_startButton->getSize().y + BASE_MARGIN * 2;
    m_p_exitButton = std::make_unique<Sprite>(Sprite({
                                                         Assets::CANCEL_BUTTON.length,
                                                         Assets::CANCEL_BUTTON.data,
                                                         BUTTON_SPRITE_SIZE,
                                                         false, true
                                                     }));
    m_p_exitButton->setPosition({WINDOW_WIDTH / 2, topOffset});
}

void Menu::createRestartButton()
{
    m_p_restartButton = std::make_unique<Sprite>(Sprite({
                                                            Assets::RESTART_BUTTON.length,
                                                            Assets::RESTART_BUTTON.data,
                                                            BUTTON_SPRITE_SIZE,
                                                            false, true
                                                        }));
    m_p_restartButton->setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.5f});
}

void Menu::createLogo()
{
    m_logo.setFont(m_font);
    m_logo.setString(WINDOW_TITLE);
    m_logo.setCharacterSize(LOGO_TEXT_SIZE);
    m_logo.setFillColor(sf::Color::Black);
    const sf::FloatRect &bounds = m_logo.getLocalBounds();
    m_logo.setOrigin({bounds.left + bounds.width / 2, bounds.top + bounds.height / 2});
    m_logo.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8);
}

void Menu::createScore()
{
    m_score.setFont(m_font);
    m_score.setCharacterSize(SCORE_TEXT_SIZE);
    m_score.setFillColor(sf::Color::Black);
    updateMenu();
    m_score.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3);
}


void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    const EState state = m_states.getState();
    switch (state)
    {
        case EState::MAIN_MENU:
            target.draw(*m_p_startButton, states);
            break;
        case EState::GAME_OVER:
            target.draw(m_score, states);
            target.draw(*m_p_restartButton, states);
            break;
        default:
            break;
    }
    target.draw(m_logo, states);
    target.draw(*m_p_exitButton, states);
}

void Menu::eventHandler(sf::Event &event, const sf::Vector2f &mousePosition, const std::function<void()> &callback)
{
    if (event.type != sf::Event::MouseButtonPressed)
    {
        return;
    }
    const sf::FloatRect &startButtonBounds = m_p_startButton->getBoundingCoordinates();
    const sf::FloatRect &exitButtonBounds = m_p_exitButton->getBoundingCoordinates();
    const sf::FloatRect &restartButtonBounds = m_p_restartButton->getBoundingCoordinates();
    const EState state = m_states.getState();
    if (startButtonBounds.contains(mousePosition) && state == EState::MAIN_MENU)
    {
        m_states.setState(EState::GAME_PROCESS);
    } else if (restartButtonBounds.contains(mousePosition) && state == EState::GAME_OVER)
    {
        m_states.setState(EState::GAME_PROCESS);
        callback();
    } else if (exitButtonBounds.contains(mousePosition))
    {
        std::exit(EXIT_SUCCESS);
    }
}

void Menu::updateMenu()
{
    const auto score = static_cast<int>(m_states.getScore() * SCORE_MULTIPLIER);
    m_score.setString("your score: " + std::to_string(score));
    updateScoreOrigin();
}


void Menu::updateScoreOrigin()
{
    const sf::FloatRect &bounds = m_score.getLocalBounds();
    m_score.setOrigin({bounds.left + bounds.width / 2, bounds.top + bounds.height / 2});
}
