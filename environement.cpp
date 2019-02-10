#include "environement.h"
sf::RenderWindow environement::m_window(sf::VideoMode(1024, 890), "leoin til valhalar - jeu");//création de la fenêtre(1024*890 avec pour nom leoin til valhalar - jeu
bool environement::m_theEnd(false);

environement::environement()
{

}
void environement::initiateWindow()
{
    //initialisation de la fenêtre
    m_window.setFramerateLimit(30);//charge la limite d'image par seconde
    //chargement de son icone
    sf::Image icon;
    icon.loadFromFile("data/image/icon.png"),
    m_window.setIcon(37,50,icon.getPixelsPtr());


}



environement::~environement()
{
    //dtor
}
