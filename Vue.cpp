#include "Vue.h"

Vue::Vue(int sizeX,int sizeY) : m_camera(sf::FloatRect(200,200,sizeX,sizeY)) , hitBox(200,200,sizeX,sizeY)//on génère sa hitbox
{
m_screenSizeX = sizeX;
m_screenSizeY = sizeY;


}

sf::View& Vue::getView()
{
    return this->m_camera;//renvoie la vue
}
void Vue::setPos(float posX,float posY)
{
    //remet en position la vue (par rapport à son centre)
    this->m_camera.setCenter(posX,posY);
    this->setPosition(posX-this->m_screenSizeX/2,posY - this->m_screenSizeY/2);

}

Vue::~Vue()
{
    //dtor
}
