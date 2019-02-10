#include "plateforme.h"

plateforme::plateforme()
{

}
plateforme::plateforme(float posX,float posY,sf::Texture* texture,bool isMoving,std::string direction,float vit,bool isAttack,float domage) : m_colBox(posX,posY,0,0)
{
m_posX = posX;
m_posY = posY;

m_texture = texture;
m_sprite.setTexture(*(m_texture));
m_colBox = hitBox(posX,posY,m_texture->getSize().x,m_texture->getSize().y);
this->m_sprite.setPosition(posX,posY);

this->m_sizeX = m_texture->getSize().x;
this->m_sizeY = m_texture->getSize().y;
m_isMoving = isMoving;
m_vitX = 0;
m_vitY = 0;
m_baseVit = vit;
if(m_isMoving)
    this->setDirection(direction);

m_movingClock.restart();
m_moveColTime = 0.5;

m_isAttack = isAttack;
m_domage = domage;


}
void plateforme::setDirection(std::string direction)
{
    //test les different type de mouvement à lui appliquer
    if(direction == "up")
    {
        this->m_vitX = 0;
        this->m_vitY = -this->m_baseVit;
    }
    if(direction == "down")
    {
        this->m_vitX = 0;
        this->m_vitY = this->m_baseVit;
    }
    if(direction == "left")
    {
        this->m_vitY = 0;
        this->m_vitX = -this->m_baseVit;
    }
    if(direction == "right")
    {
        this->m_vitY = 0;
        this->m_vitX = this->m_baseVit;
    }

}
void plateforme::draw(sf::RenderWindow& window,Vue& vue,std::vector<blocus_plateForme>& List)
{
    //si elle bouge
    if(this->m_isMoving)
    {
        //la bouge avec les valeurs de sa vitesse
        this->m_sprite.move(this->m_vitX,this->m_vitY);
        this->m_colBox.moveHB(this->m_vitX,this->m_vitY);

        for(int e=0;e<List.size();e++)//test les collisions avec les blocus plateformes
        {
            if(this->m_colBox.boxCollision(List[e]) == true && this->m_movingClock.getElapsedTime().asSeconds() > this->m_moveColTime)
            {
                this->setDirection(List[e].getType());
                this->m_movingClock.restart();
            }
        }
    }
    if(this->m_colBox.boxCollision(vue))//si la plateforme est à l'écran , on l'affiche
        window.draw(this->m_sprite);
}
//différents récupérateur de l'objets
hitBox& plateforme::getColBox()
{
    return this->m_colBox;
}
std::string plateforme::getDirection()
{
    return this->m_direction;
}
float plateforme::getPosX()
{
    return this->m_sprite.getPosition().x;
}
float plateforme::getPosY()
{
    return this->m_sprite.getPosition().y;
}
float plateforme::getSizeX()
{
    return this->m_sizeX;
}
float plateforme::getSizeY()
{
    return this->m_sizeY;
}
float plateforme::getVitX()
{
    return this->m_vitX;
}
float plateforme::getVitY()
{
    return this->m_vitY;
}
bool plateforme::isMoving()
{
    return this->m_isMoving;
}
bool plateforme::isHiting()
{
    return this->m_isAttack;
}
float plateforme::getDomage()
{
    return this->m_domage;
}
plateforme::~plateforme()
{
    //dtor
}
