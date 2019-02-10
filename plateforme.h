#ifndef PLATEFORME_H
#define PLATEFORME_H
#include <SFML/Graphics.hpp>
#include "hitbox.h"
#include "Vue.h"
#include "generalTexture.h"
#include <vector>
#include "blocus_plateForme.h"
class plateforme //objet compos� d'un sprite avec une hitbox
                //, sert d'obstacle dans l'environement capable d'�tre mouvante ou d'infliger des degats(cela annule la possibilit� de bloqu� les entit�s)
{
    public:
        plateforme();
        plateforme(float posX,float posY,sf::Texture* texture,bool isMoving,std::string direction,float vit,bool isAttack,float domage);
        void draw(sf::RenderWindow& window,Vue& vue,std::vector<blocus_plateForme>& List);

        bool isMoving();
        bool isHiting();

        //permet de r�cup�rer les attributs de la plateforme
        float getPosX();
        float getPosY();
        float getSizeX();
        float getSizeY();
        float getVitX();
        float getVitY();
        float getDomage();
        std::string getDirection();
        hitBox& getColBox();

        void setDirection(std::string direction);//permet de diriger la plateforme vers une direction indiqu�

        virtual ~plateforme();
    protected:
    bool m_isMoving;//si elle bouge
    bool m_isAttack;//si elle inflige des d�gats

    float m_posX;
    float m_posY;
    float m_sizeX;
    float m_sizeY;
    float m_vitX;//vitesse de la plateforme
    float m_vitY;
    float m_baseVit;//vitesse de r�f�rence de la plateforme
    float m_moveColTime;//temps entre 2 mouvements
    float m_domage;

    std::string m_direction;//direction de la plateforme("up","down","left" ou "right")

    sf::Texture* m_texture;//texture
    sf::Sprite m_sprite;//sprite
    sf::Clock m_movingClock;//horloge pour controler le mouvment
    hitBox m_colBox;//hitbox de la plateforme



    private:
};

#endif // PLATEFORME_H
