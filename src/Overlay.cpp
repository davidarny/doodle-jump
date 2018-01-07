#include "Overlay.h"
#include "consts.h"
#include "Assets.h"

Overlay::Overlay(StateMediator &stateMediator) : m_stateMediator(stateMediator)
{
    if (m_font.loadFromMemory(Assets::FONT.data, Assets::FONT.length))
    {
        createScore();
    } else
    {
        // TODO: handle error
        std::exit(EXIT_FAILURE);
    }
}

void Overlay::createScore()
{
    m_score.setFont(m_font);
    updateScoreString();
    m_score.setCharacterSize(GAME_SCORE_TEXT_SIZE);
    m_score.setFillColor(sf::Color::Black);
    const sf::FloatRect &bounds = m_score.getLocalBounds();
    m_score.setOrigin({bounds.left + bounds.width / 2, bounds.top + bounds.height / 2});
    m_score.setPosition(bounds.width / 2 + BASE_MARGIN / 2, bounds.height / 2 + BASE_MARGIN / 2);
}

void Overlay::updateScoreString()
{
    const auto score = static_cast<int>(m_stateMediator.getScore() * SCORE_MULTIPLIER);
    m_score.setString("Score: " + std::to_string(score));
}

void Overlay::updateScorePosition(const float nextY)
{
    const float y = nextY - WINDOW_HEIGHT / 2 + m_score.getLocalBounds().height / 2;
    m_score.setPosition(m_score.getPosition().x, y + BASE_MARGIN / 2);
}

void Overlay::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_score, states);
}
