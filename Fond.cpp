#include "Fond.h"

Fond::Fond(Vue& view) : m_vertexArray(sf::Quads,4)
{

    m_vue = &view;
    this->m_vertexArray[0].position = sf::Vector2f(this->m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y +  this->m_vue->getView().getSize().y/2);
    this->m_vertexArray[1].position = sf::Vector2f(this->m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y -  this->m_vue->getView().getSize().y/2);
    this->m_vertexArray[2].position = sf::Vector2f(this->m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y -  this->m_vue->getView().getSize().y/2);
    this->m_vertexArray[3].position = sf::Vector2f(this->m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y + this->m_vue->getView().getSize().y/2);


    this->m_vertexArray[0].texCoords = sf::Vector2f(0,890);
    this->m_vertexArray[1].texCoords = sf::Vector2f(0,0);
    this->m_vertexArray[2].texCoords = sf::Vector2f(1024,0);
    this->m_vertexArray[3].texCoords = sf::Vector2f(1024,890);
    m_text = &generalTexture::textureList["SunSet"];//appliquaction la texture de fond (SunSet)
}
void Fond::update(sf::RenderWindow& window)
{
    //remet en position le fond en fonction de la vue du jeu
    this->m_vertexArray[0].position = sf::Vector2f(this->m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y +  this->m_vue->getView().getSize().y/2);
    this->m_vertexArray[1].position = sf::Vector2f(m_vue->getView().getCenter().x -  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y -  this->m_vue->getView().getSize().y/2);
    this->m_vertexArray[2].position = sf::Vector2f(m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y -  this->m_vue->getView().getSize().y/2);
    this->m_vertexArray[3].position = sf::Vector2f(m_vue->getView().getCenter().x +  this->m_vue->getView().getSize().x/2,
                                             this->m_vue->getView().getCenter().y + this->m_vue->getView().getSize().y/2);
    window.draw(this->m_vertexArray,m_text);
}

Fond::~Fond()
{
    //dtor
}
