#ifndef LASER_H
#define LASER_H
#include "environement.h"
#include "generalTexture.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vue.h"

//entité graphique affochable doté d'une hitBox
//rectangle texturé formant un laser se dirigeant vers la gauche
//inflige des dégats au contacts du joueur
//utilisé uniquement par le panda
//
class laser
{
    public:
        laser(float posX,float posY,int sizeL,sf::Color color);
        void update(Vue& vue);//remet en position les points qui le compose pour s'aligné avec la partie gauche de l'écran
        void draw();//dessine le laser à l'écran
        void setPos(float posX,float posY);//remet en position son origine
        bool LaserCol(hitBox& box);//renvoie si il y a collision avec la hitbox envoyé en paramètre
        virtual ~laser();
    protected:
        sf::Sprite m_cercle;//sprite qui signe l'origine du laser
        sf::Texture m_cercleText;//texture du cercle
        sf::Color m_color;//couleur du laser
        sf::VertexArray m_vertexAray;//tableau de vertex qui compose le laser
        sf::Vector2f m_origin;//coordonnées de l'origine du laser
        float m_size;//épaisseur du laser
        hitBox m_box;//hitbox du laser
        sf::Texture* m_texture;//texture du laser
    private:
};

#endif // LASER_H
