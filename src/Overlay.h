#ifndef DOODLE_JUMP_OVERLAY_H
#define DOODLE_JUMP_OVERLAY_H

#include "States.h"

class Overlay : public sf::Drawable
{
public:
    explicit Overlay(States &stateMediator);

    void updateOverlay(float nextY, float deltaTime);

private:
    States &m_states;
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
