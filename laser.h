#ifndef LASER_H
#define LASER_H
#include "environement.h"
#include "generalTexture.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vue.h"

//entit� graphique affochable dot� d'une hitBox
//rectangle textur� formant un laser se dirigeant vers la gauche
//inflige des d�gats au contacts du joueur
//utilis� uniquement par le panda
//
class laser
{
    public:
        laser(float posX,float posY,int sizeL,sf::Color color);
        void update(Vue& vue);//remet en position les points qui le compose pour s'align� avec la partie gauche de l'�cran
        void draw();//dessine le laser � l'�cran
        void setPos(float posX,float posY);//remet en position son origine
        bool LaserCol(hitBox& box);//renvoie si il y a collision avec la hitbox envoy� en param�tre
        virtual ~laser();
    protected:
        sf::Sprite m_cercle;//sprite qui signe l'origine du laser
        sf::Texture m_cercleText;//texture du cercle
        sf::Color m_color;//couleur du laser
        sf::VertexArray m_vertexAray;//tableau de vertex qui compose le laser
        sf::Vector2f m_origin;//coordonn�es de l'origine du laser
        float m_size;//�paisseur du laser
        hitBox m_box;//hitbox du laser
        sf::Texture* m_texture;//texture du laser
    private:
};

#endif // LASER_H
