#ifndef DOODLE_JUMP_OVERLAY_H
#define DOODLE_JUMP_OVERLAY_H

#include "StateMediator.h"

class Overlay : public sf::Drawable
{
public:
    explicit Overlay(StateMediator &stateMediator);

    void updateOverlay(float nextY, float deltaTime);

private:
    StateMediator &m_stateMediator;
    sf::Font m_font;
    sf::Text m_score;
    sf::Text m_fps;

    void createScoreCounter();

    void createFrameRateCounter();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void updateOverlayPosition(float nextY);

    void updateOverlayStrings(float deltaTime);
};

#endif //DOODLE_JUMP_OVERLAY_H
