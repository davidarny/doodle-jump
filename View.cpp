#include "SFML/Graphics.hpp"
#include "View.h"

View::View()
{
    m_view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
}

void View::followTo(const std::shared_ptr<Doodler> p_doodler)
{
    m_view.setCenter(WINDOW_WIDTH / 2, p_doodler->getPosition().y);
}

const sf::View &View::getView() const
{
    return m_view;
}
