#include "SFML/Graphics.hpp"
#include "View.h"

View::View()
{
    m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
}

void View::followTo(const std::shared_ptr<Doodler> p_doodler)
{
    m_view.setCenter(p_doodler->getPosition());
}

const sf::View &View::getView() const
{
    return m_view;
}
