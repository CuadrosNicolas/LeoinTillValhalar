#include "button.h"
button::button()
{

}
button::button(float posX,float posY,std::string nom) : m_box(posX,posY,generalTexture::textureList[nom].getSize().x,generalTexture::textureList[nom].getSize().y)
{

    m_sprite.setPosition(posX,posY);
    m_sprite.setTexture(generalTexture::textureList[nom]);//initialisation de sa texture
}
bool button::update(sf::RenderWindow& window)
{
    window.draw(this->m_sprite);//dessine dans la fen�tre le bouton
    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(window)));//r�cup�ration des coordonn�es de la souris dans la fenetre
    this->m_sprite.setColor(sf::Color(255,255,255));
    if(this->m_box.pointCollision(worldPos.x,worldPos.y))//si elle est en collision avec le bouton
    {
        this->m_sprite.setColor(sf::Color(255,0,255));//changement sa couleur en violet
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))//et si le bouton gauche est enfonc� de la souris on revoie qu'il est pr�ss�
            return true;
    }
    else
        return false;

}
button::~button()
{
    //dtor
}
