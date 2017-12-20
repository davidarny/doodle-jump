#ifndef DOODLE_JUMP_VIEW_H
#define DOODLE_JUMP_VIEW_H

#include <SFML/Graphics.hpp>
#include "Doodler.h"

class View
{
public:
    View();

    const sf::View &getView() const;

    void followTo(std::shared_ptr<Doodler> p_doodler);

private:
    sf::View m_view;
};

#endif //DOODLE_JUMP_VIEW_H
