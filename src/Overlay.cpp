#include <c++/7.2.0/cmath>
#include "Overlay.h"
#include "consts.h"
#include "Assets.h"

Overlay::Overlay(StateMediator &stateMediator) : m_stateMediator(stateMediator)
{
    if (m_font.loadFromMemory(Assets::FONT.data, Assets::FONT.length))
    {
        updateOverlayStrings(0.f);
        createScoreCounter();
        createFrameRateCounter();
    } else
    {
        // TODO: handle error
        std::exit(EXIT_FAILURE);
    }
}

void Overlay::createScoreCounter()
{
    m_score.setFont(m_font);
    m_score.setCharacterSize(GAME_SCORE_TEXT_SIZE);
    m_score.setFillColor(sf::Color::Black);
    m_score.setPosition(BASE_MARGIN / 2, 0);
}

void Overlay::createFrameRateCounter()
{
    m_fps.setFont(m_font);
    m_fps.setCharacterSize(GAME_SCORE_TEXT_SIZE);
    m_fps.setFillColor(sf::Color::Black);
    m_fps.setPosition(WINDOW_WIDTH - m_fps.getLocalBounds().width / 4, 0);
}

void Overlay::updateOverlay(float nextY, float deltaTime)
{
    updateOverlayPosition(nextY);
    updateOverlayStrings(deltaTime);
}

void Overlay::updateOverlayPosition(float nextY)
{
    const float scoreY = nextY - WINDOW_HEIGHT / 2;
    m_score.setPosition(m_score.getPosition().x, scoreY);

    const float fpsY = nextY - WINDOW_HEIGHT / 2;
    m_fps.setPosition(m_fps.getPosition().x, fpsY);
}

void Overlay::updateOverlayStrings(float deltaTime)
{
    const auto score = static_cast<int>(m_stateMediator.getScore() * SCORE_MULTIPLIER);
    m_score.setString("score: " + std::to_string(score));

    const auto fps = static_cast<int>(1 / deltaTime);
    m_fps.setString(std::to_string(fps));
}

void Overlay::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (IS_DEBUG)
    {
        target.draw(m_fps);
    }
    target.draw(m_score, states);
}
