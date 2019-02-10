#include "laser.h"

        laser::laser(float posX,float posY,int sizeL,sf::Color color) : m_vertexAray(sf::Quads,8)
        {
            m_origin = sf::Vector2f(posX,posY);
            m_cercle.setTexture(generalTexture::textureList["bambou_laser_1"]);
            m_cercleText = generalTexture::textureList["bambou_laser_1"];
            m_color = color;
            m_size = sizeL;
            m_box = hitBox(posX,posY,10,10);
            m_box.setPositionToRight(posX,posY);
            m_texture = &generalTexture::textureList["laser_1"];
            for(int e = 0;e<m_vertexAray.getVertexCount();e++)
                m_vertexAray[e].color = color;
            float sizeX = m_texture->getSize().x;
            float sizeY = m_texture->getSize().y;






            m_vertexAray[0].position = sf::Vector2f(posX,posY);
            m_vertexAray[1].position = sf::Vector2f(posX,posY);

            m_vertexAray[2].position = sf::Vector2f(posX - 10,posY + m_size/2);
            m_vertexAray[3].position = sf::Vector2f(posX - 10,posY - m_size/2);
            m_vertexAray[4].position = sf::Vector2f(posX - 10,posY + m_size/2);
            m_vertexAray[5].position = sf::Vector2f(posX - 10,posY - m_size/2);

            m_vertexAray[6].position = sf::Vector2f(posX - 10,posY + m_size/2);
            m_vertexAray[7].position = sf::Vector2f(posX - 10,posY - m_size/2);

            m_vertexAray[0].texCoords = sf::Vector2f(sizeX,sizeY/2);
            m_vertexAray[1].texCoords = sf::Vector2f(sizeX,sizeY/2);
            m_vertexAray[2].texCoords = sf::Vector2f(0,0);
            m_vertexAray[3].texCoords = sf::Vector2f(0,sizeY);

            m_vertexAray[4].texCoords = sf::Vector2f(sizeX,sizeY);
            m_vertexAray[5].texCoords = sf::Vector2f(sizeX,0);
            m_vertexAray[6].texCoords = sf::Vector2f(0,0);
            m_vertexAray[7].texCoords = sf::Vector2f(0,sizeY);



        }
        void laser::update(Vue& vue)
        {
            this->m_vertexAray[6].position = sf::Vector2f(this->m_origin.x - vue.getView().getCenter().x - vue.getSizeX()/2,this->m_origin.y - this->m_size/2);
            this->m_vertexAray[7].position = sf::Vector2f(this->m_origin.x - vue.getView().getCenter().x - vue.getSizeX()/2,this->m_origin.y + this->m_size/2);
            this->m_box.reSize(this->m_origin.x - vue.getSizeX()/2,this->m_size);
            this->m_box.setPositionToRight(this->m_origin.x,this->m_origin.y);

        }
    void laser::setPos(float posX,float posY)
    {

        this->m_origin = sf::Vector2f(posX,posY);
                m_cercle.setPosition(this->m_origin.x - this->m_cercleText.getSize().x/2,this->m_origin.y - this->m_cercleText.getSize().y/2);
            m_vertexAray[0].position = this->m_origin;
            m_vertexAray[1].position = this->m_origin;
            m_vertexAray[2].position = sf::Vector2f(this->m_origin.x - 10,this->m_origin.y + m_size/2);
            m_vertexAray[3].position = sf::Vector2f(this->m_origin.x - 10,this->m_origin.y - m_size/2);
            m_vertexAray[4].position = sf::Vector2f(this->m_origin.x - 10,this->m_origin.y + m_size/2);
            m_vertexAray[5].position = sf::Vector2f(this->m_origin.x - 10,this->m_origin.y - m_size/2);

    }
    void laser::draw()
    {
            environement::m_window.draw(this->m_cercle);
            environement::m_window.draw(this->m_vertexAray,this->m_texture);
    }
        bool laser::LaserCol(hitBox& box)
        {
            return this->m_box.boxCollision(box);

        }
laser::~laser()
{
    //dtor
}
