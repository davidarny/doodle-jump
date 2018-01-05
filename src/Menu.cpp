#include "Menu.h"
#include "resources/opensans.h"

Menu::Menu(StateMediator &stateMediator) : m_stateMediator(stateMediator)
{
    if (m_font.loadFromMemory(OPEN_SANS.data, std::size(OPEN_SANS.data)))
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
    ButtonOptions buttonOptions;
    buttonOptions.size = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 10};
    buttonOptions.fillColor = sf::Color::Red;
    buttonOptions.outlineColor = sf::Color::Black;
    buttonOptions.outlineThickness = 2;
    buttonOptions.position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.5f};
    buttonOptions.font = sf::Font(m_font);
    buttonOptions.text = "Start game";
    buttonOptions.textSize = BUTTON_TEXT_SIZE;
    buttonOptions.textColor = sf::Color::White;

    m_startButton = Button(buttonOptions);
}

void Menu::createExitButton()
{
    const sf::RectangleShape &startButtonShape = m_startButton.getShape();
    const float topOffset = startButtonShape.getPosition().y + startButtonShape.getSize().y + BASE_MARGIN * 2;
    ButtonOptions buttonOptions;
    buttonOptions.size = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 10};
    buttonOptions.fillColor = sf::Color::Black;
    buttonOptions.outlineColor = sf::Color::Red;
    buttonOptions.outlineThickness = 2;
    buttonOptions.position = {WINDOW_WIDTH / 2, topOffset};
    buttonOptions.font = sf::Font(m_font);
    buttonOptions.text = "Exit game";
    buttonOptions.textSize = BUTTON_TEXT_SIZE;
    buttonOptions.textColor = sf::Color::White;

    m_exitButton = Button(buttonOptions);
}

void Menu::createRestartButton()
{
    ButtonOptions buttonOptions;
    buttonOptions.size = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 10};
    buttonOptions.fillColor = sf::Color::Red;
    buttonOptions.outlineColor = sf::Color::Black;
    buttonOptions.outlineThickness = 2;
    buttonOptions.position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.5f};
    buttonOptions.font = sf::Font(m_font);
    buttonOptions.text = "Restart game";
    buttonOptions.textSize = BUTTON_TEXT_SIZE;
    buttonOptions.textColor = sf::Color::White;

    m_restartButton = Button(buttonOptions);
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
    updateScoreString();
    m_score.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3);
}


void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    const State state = m_stateMediator.getState();
    switch (state)
    {
        case State::MainMenu:
            target.draw(m_startButton, states);
            break;
        case State::GameOver:
            target.draw(m_score, states);
            target.draw(m_restartButton, states);
            break;
        default:
            break;
    }
    target.draw(m_logo, states);
    target.draw(m_exitButton, states);
}

void Menu::eventHandler(sf::Event &event, const sf::Vector2f &mousePosition, const std::function<void()> &callback)
{
    if (event.type != sf::Event::MouseButtonPressed)
    {
        return;
    }
    const sf::FloatRect &startButtonBounds = m_startButton.getShape().getGlobalBounds();
    const sf::FloatRect &exitButtonBounds = m_exitButton.getShape().getGlobalBounds();
    const sf::FloatRect &restartButtonBounds = m_restartButton.getShape().getGlobalBounds();
    const State state = m_stateMediator.getState();
    if (startButtonBounds.contains(mousePosition) && state == State::MainMenu)
    {
        m_stateMediator.setState(State::Game);
    } else if (restartButtonBounds.contains(mousePosition) && state == State::GameOver)
    {
        m_stateMediator.setState(State::Game);
        callback();
    } else if (exitButtonBounds.contains(mousePosition))
    {
        std::exit(EXIT_SUCCESS);
    }
}

void Menu::updateScoreString()
{
    const auto score = static_cast<int>(m_stateMediator.getScore() * SCORE_MULTIPLIER);
    m_score.setString("Your score: " + std::to_string(score));
    updateScoreOrigin();
}


void Menu::updateScoreOrigin()
{
    const sf::FloatRect &bounds = m_score.getLocalBounds();
    m_score.setOrigin({bounds.left + bounds.width / 2, bounds.top + bounds.height / 2});
}
