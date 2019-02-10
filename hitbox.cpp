#include "hitbox.h"

hitBox::hitBox()
{



}
hitBox::hitBox(float posX,float posY,float sizeX,float sizeY)
{
    m_posX = posX;
    m_posY = posY;
    m_sizeX = sizeX;
    m_sizeY = sizeY;


        m_lineUp.setSize(sf::Vector2f(this->m_sizeX,1));
        m_lineUp.setPosition(this->m_posX,this->m_posY);

        m_lineDown.setSize(sf::Vector2f(this->m_sizeX + 1 ,1));
        m_lineDown.setPosition(this->m_posX,this->m_posY + this->m_sizeY);

        m_lineLeft.setSize(sf::Vector2f(1,this->m_sizeY));
        m_lineLeft.setPosition(this->m_posX,this->m_posY);

        m_lineRight.setSize(sf::Vector2f(1,this->m_sizeY));
        m_lineRight.setPosition(this->m_posX + this->m_sizeX,this->m_posY);



        m_Red = sf::Color(255,0,0);
        m_White = sf::Color(255,255,255);


        m_animTime = 0.1;
        m_clock.restart();

}
void hitBox::reSize(float sizeX,float sizeY)//redimmensinone la hitBox
{
    this->m_sizeX = sizeX;
    this->m_sizeY = sizeY;

    this->m_lineUp.setSize(sf::Vector2f(this->m_sizeX,1));
    this->m_lineDown.setSize(sf::Vector2f(this->m_sizeX + 1 ,1));
    this->m_lineLeft.setSize(sf::Vector2f(1,this->m_sizeY));
    this->m_lineRight.setSize(sf::Vector2f(1,this->m_sizeY));

}
void hitBox::moveHB(float posX,float posY)//bouge la hitbox de posX,posY coordonn�es
{
    if(this->m_clock.getElapsedTime().asSeconds() > this->m_animTime)
        this->lineSetWhite();
    this->m_posX = this->m_posX + posX;
    this->m_posY = this->m_posY + posY;


                this->m_lineUp.setPosition(this->m_posX,this->m_posY);
            this->m_lineDown.setPosition(this->m_posX,this->m_posY + this->m_sizeY );
            this->m_lineLeft.setPosition(this->m_posX,this->m_posY  );
        this->m_lineRight.setPosition(this->m_posX + this->m_sizeX,this->m_posY );
}
void hitBox::setPosition(float posX,float posY)//remet en position la hitbox par rapport � son coin sup�rieur gauche
{
    if(this->m_clock.getElapsedTime().asSeconds() > this->m_animTime)
        this->lineSetWhite();

    this->m_posX = posX;
    this->m_posY = posY;
            this->m_lineUp.setPosition(this->m_posX,this->m_posY);
            this->m_lineDown.setPosition(this->m_posX,this->m_posY + this->m_sizeY );
            this->m_lineLeft.setPosition(this->m_posX,this->m_posY  );
        this->m_lineRight.setPosition(this->m_posX + this->m_sizeX,this->m_posY );
}
void hitBox::setPositionByCenter(float posX,float posY)//remet en postion la hitbox par rapport � son centre
{
    if(this->m_clock.getElapsedTime().asSeconds() > this->m_animTime)
        this->lineSetWhite();

    this->m_posX = posX - this->m_sizeX/2;
    this->m_posY = posY - this->m_sizeY/2;
            this->m_lineUp.setPosition(this->m_posX,this->m_posY);
            this->m_lineDown.setPosition(this->m_posX,this->m_posY + this->m_sizeY );
            this->m_lineLeft.setPosition(this->m_posX,this->m_posY  );
        this->m_lineRight.setPosition(this->m_posX + this->m_sizeX,this->m_posY );
}
void hitBox::setPositionToRight(float posX,float posY)
{

        if(this->m_clock.getElapsedTime().asSeconds() > this->m_animTime)
        this->lineSetWhite();

    this->m_posX = posX - this->m_sizeX;
    this->m_posY = posY - this->m_sizeY/2;
            this->m_lineUp.setPosition(this->m_posX,this->m_posY);
            this->m_lineDown.setPosition(this->m_posX,this->m_posY + this->m_sizeY );
            this->m_lineLeft.setPosition(this->m_posX,this->m_posY  );
        this->m_lineRight.setPosition(this->m_posX + this->m_sizeX,this->m_posY );


}
bool hitBox::boxCollision(hitBox& box)
{

                if(box.getPosX() + box.getSizeX() < this->m_posX //trop a gauche
       || box.getPosX() > this->m_posX + this->m_sizeX //trop a droite
       || box.getPosY() + box.getSizeY() < this->m_posY //trop en haut
       || box.getPosY() > this->m_posY + this->m_sizeY)//trop en bas
    {
        return false;
    }
    else
        return true;


}
bool hitBox::pointCollision(float pointX,float pointY)
{
    if(pointX >= this->m_posX //trop a droite
       && pointX < this->m_posX + this->m_sizeX//trop a gauche
       && pointY >= this->m_posY//trop en bas
       && pointY <= this->m_posY + this->m_sizeY)//trop en haut
    {
        return true;
    }
    else
        return false;


}
void hitBox::drawBox(sf::RenderWindow& window)
{


    window.draw(m_lineUp);
    window.draw(m_lineDown);
    window.draw(m_lineLeft);
    window.draw(m_lineRight);



}
void hitBox::lineSetRed()
{
    this->m_clock.restart();
    this->m_lineUp.setFillColor(this->m_Red);
    this->m_lineDown.setFillColor(this->m_Red);
    this->m_lineLeft.setFillColor(this->m_Red);
    this->m_lineRight.setFillColor(this->m_Red);



}
void hitBox::lineSetWhite()
{
    this->m_lineUp.setFillColor(this->m_White);
    this->m_lineDown.setFillColor(this->m_White);
    this->m_lineLeft.setFillColor(this->m_White);
    this->m_lineRight.setFillColor(this->m_White);
}



float hitBox::getPosX()
{
    return this->m_posX;
}

float hitBox::getPosY()
{
    return this->m_posY;
}
float hitBox::getSizeX()
{
    return this->m_sizeX;
}
float hitBox::getSizeY()
{
    return this->m_sizeY;
}



hitBox::~hitBox()
{
    //dtor
}
