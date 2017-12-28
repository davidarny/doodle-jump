#include "Menu.h"
#include "opensans.h"

Menu::Menu(StateMediator &stateMediator) : m_stateMediator(stateMediator)
{
    if (m_font.loadFromMemory(OpenSans, std::size(OpenSans)))
    {
        initStartButton();
        initExitButton();
        initLogo();
    } else
    {
        // TODO: handle error
        std::exit(0);
    }
}

// TODO: add on click handler
void Menu::initStartButton()
{
    const sf::Vector2f size = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 10};
    sf::RectangleShape &shape = m_startButton.m_shape;
    shape.setSize(size);
    shape.setFillColor(sf::Color::Red);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(2);
    shape.setOrigin(size.x / 2, size.y / 2);
    shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.5f);

    sf::Text &text = m_startButton.m_text;
    text.setFont(m_font);
    text.setString("Start game");
    text.setCharacterSize(m_startButton.m_textSize);
    text.setFillColor(sf::Color::White);
    const sf::FloatRect &bounds = text.getLocalBounds();
    const sf::Vector2f origin = {bounds.left + bounds.width / 2, bounds.top + bounds.height / 2};
    text.setOrigin(origin);
    text.setPosition(shape.getPosition());
}

void Menu::initExitButton()
{
    sf::RectangleShape &exitButtonShape = m_exitButton.m_shape;
    const sf::RectangleShape &startButtonShape = m_startButton.m_shape;
    const float topOffset = startButtonShape.getPosition().y + startButtonShape.getSize().y + BASE_MARGIN * 2;
    const sf::Vector2f size = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 10};
    exitButtonShape.setSize(size);
    exitButtonShape.setFillColor(sf::Color::Black);
    exitButtonShape.setOutlineColor(sf::Color::Red);
    exitButtonShape.setOutlineThickness(2);
    exitButtonShape.setOrigin(size.x / 2, size.y / 2);
    exitButtonShape.setPosition(WINDOW_WIDTH / 2, topOffset);

    sf::Text &text = m_exitButton.m_text;
    text.setFont(m_font);
    text.setString("Exit game");
    text.setCharacterSize(m_exitButton.m_textSize);
    text.setFillColor(sf::Color::White);
    const sf::FloatRect &bounds = text.getLocalBounds();
    const sf::Vector2f origin = {bounds.left + bounds.width / 2, bounds.top + bounds.height / 2};
    text.setOrigin(origin);
    text.setPosition(exitButtonShape.getPosition());
}

void Menu::initLogo()
{
    m_logo.setFont(m_font);
    m_logo.setString(WINDOW_TITLE);
    m_logo.setCharacterSize(LOGO_TEXT_SIZE);
    m_logo.setFillColor(sf::Color::Black);
    const sf::FloatRect &bounds = m_logo.getLocalBounds();
    const sf::Vector2f origin = {bounds.left + bounds.width / 2, bounds.top + bounds.height / 2};
    m_logo.setOrigin(origin);
    m_logo.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 8);
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_startButton.m_shape, states);
    target.draw(m_startButton.m_text, states);
    target.draw(m_exitButton.m_shape, states);
    target.draw(m_exitButton.m_text, states);
    target.draw(m_logo, states);
}

void Menu::eventHandler(sf::Event &event, const sf::Vector2f &mousePosition)
{
    if (event.type != sf::Event::MouseButtonPressed)
    {
        return;
    }
    const sf::FloatRect &startButtonBounds = m_startButton.m_shape.getGlobalBounds();
    const sf::FloatRect &exitButtonBounds = m_exitButton.m_shape.getGlobalBounds();
    if (startButtonBounds.contains(mousePosition))
    {
        m_stateMediator.setState(State::Game);
    } else if (exitButtonBounds.contains(mousePosition))
    {
        std::exit(0);
    }
}
