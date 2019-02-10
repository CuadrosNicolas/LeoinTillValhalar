#include "blackScreen.h"
blackScreen::blackScreen()
{

}
blackScreen::blackScreen(Vue& view) : m_vertexArrayTop(sf::Quads,4),m_vertexArrayBot(sf::Quads,4)
{

    m_vue = &view;
    m_isOpen = false;
    m_isClose = true;
    m_goToOpen = false;
    m_goToClose = false;
    m_openTime = 2;
    m_centerY = 890/2;
    m_posY = 890/2;

    this->m_vertexArrayTop[0].position = sf::Vector2f(this->m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y -  this->m_vue->getView().getSize().y/2);
    this->m_vertexArrayTop[1].position = sf::Vector2f(m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y -  this->m_vue->getView().getSize().y/2);
    this->m_vertexArrayTop[2].position = sf::Vector2f(m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y -  this->m_vue->getView().getSize().y/2 + this->m_posY);
    this->m_vertexArrayTop[3].position = sf::Vector2f(m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y - this->m_vue->getView().getSize().y/2 + this->m_posY);

    this->m_vertexArrayBot[0].position = sf::Vector2f(this->m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y +  this->m_vue->getView().getSize().y/2);
    this->m_vertexArrayBot[1].position = sf::Vector2f(m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y +  this->m_vue->getView().getSize().y/2);
    this->m_vertexArrayBot[2].position = sf::Vector2f(m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y +  this->m_vue->getView().getSize().y/2 - this->m_posY );
    this->m_vertexArrayBot[3].position = sf::Vector2f(m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y + this->m_vue->getView().getSize().y/2 - this->m_posY);

    sf::Color black(0,0,0);
    this->m_vertexArrayTop[0].color = black;
    this->m_vertexArrayTop[1].color = black;
    this->m_vertexArrayTop[2].color = black;
    this->m_vertexArrayTop[3].color = black;

    this->m_vertexArrayBot[0].color = black;
    this->m_vertexArrayBot[1].color = black;
    this->m_vertexArrayBot[2].color = black;
    this->m_vertexArrayBot[3].color = black;

}
void blackScreen::update(sf::RenderWindow& window)
{

    this->m_vertexArrayTop[0].position = sf::Vector2f(this->m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y -  this->m_vue->getView().getSize().y/2);
    this->m_vertexArrayTop[1].position = sf::Vector2f(m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y -  this->m_vue->getView().getSize().y/2);
    this->m_vertexArrayTop[2].position = sf::Vector2f(m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y -  this->m_vue->getView().getSize().y/2 + this->m_posY);
    this->m_vertexArrayTop[3].position = sf::Vector2f(m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y - this->m_vue->getView().getSize().y/2 + this->m_posY);

    this->m_vertexArrayBot[0].position = sf::Vector2f(this->m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y +  this->m_vue->getView().getSize().y/2);
    this->m_vertexArrayBot[1].position = sf::Vector2f(m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y +  this->m_vue->getView().getSize().y/2);
    this->m_vertexArrayBot[2].position = sf::Vector2f(m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y +  this->m_vue->getView().getSize().y/2 - this->m_posY );
    this->m_vertexArrayBot[3].position = sf::Vector2f(m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y + this->m_vue->getView().getSize().y/2 - this->m_posY);




     if(this->m_goToOpen)//si il est en train de s'ouvrir
     {
        this->m_posY -= 10;//écartement des points des rectangles
        if(this->m_posY <= 0)//si il sont au bout
        {
        this->m_isOpen = true;// l'écran noir est ouvert
        this->m_goToOpen = false;//et qu'il ne s'ouvre plus
        }

     }     if(this->m_goToClose)//si il est en train de se fermer
     {

        this->m_posY += 10;//rapprochement des points des rectangles
        if(this->m_posY >= this->m_centerY)//si il sont au centre de l'écran
        {
        this->m_isClose = true;//l'écran noir est fermé
        this->m_goToClose = false;//et qu'il ne se ferme plus
        }

     }





    //on dessine les rectangles si il n'est pas ouvert
if(!this->m_isOpen)
{
    window.draw(this->m_vertexArrayTop);
    window.draw(this->m_vertexArrayBot);
}
}

void blackScreen::close()//l'écran
{       this->m_isOpen = false;//il n'est plus ouvert
        this->m_goToClose = true;//il est en train de se fermer
}
void blackScreen::open()//ouvre l'écran
{
    this->m_isClose = false;//il n'est plus fermé
    this->m_goToOpen = true;//il est en train de s'ouvrir

}
//on renvoie si il est ouvert ou fermé
bool blackScreen::isOpen()
{
    return this->m_isOpen;
}
bool blackScreen::isClose()
{
    return this->m_isClose;
}
blackScreen::~blackScreen()
{
    //dtor
}
