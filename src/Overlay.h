#ifndef DOODLE_JUMP_OVERLAY_H
#define DOODLE_JUMP_OVERLAY_H

#include "StateMediator.h"

class Overlay : public sf::Drawable
{
public:
    explicit Overlay(StateMediator &stateMediator);

    void updateScoreString();

    void updateScorePosition(float nextY);

private:
    StateMediator &m_stateMediator;
    sf::Font m_font;
    sf::Text m_score;

    void createScore();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //DOODLE_JUMP_OVERLAY_H
