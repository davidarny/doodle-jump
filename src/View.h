#ifndef DOODLE_JUMP_VIEW_H
#define DOODLE_JUMP_VIEW_H

#include <SFML/Graphics.hpp>
#include "Doodler.h"

class View
{
public:
    View();

    sf::View &getView();

    void followTo(const std::shared_ptr<IEntity> &p_doodler);

private:
    sf::View m_view;
};

#endif //DOODLE_JUMP_VIEW_H
