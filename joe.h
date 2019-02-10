#ifndef JOE_H
#define JOE_H
#include "adversaire.h"
#include "generalTexture.h"
#include "plateforme.h"
#include "Vue.h"
#include <iostream>
//adversaire allant de gauche � droite(d�limit� par des blocusAdv)
//au contact du joueur il se pr�pare � attaqu�
//une fois en train d'attaqu� il inflige des d�gats au contact du joueur
//assez lent mais inflige beaucoup de d�gats
//ensuite il reprend ses mouvements
//
class joe : public adversaire
{
    public:
        joe(float posX,float posY);
        void updateCollision(std::vector<plateforme>& plList,Vue& vue,std::vector<blocusAdv>& BadvList);//mise � jour des collisions avec les plateforms et blocus d'adversaire
        void mouv(std::vector<plateforme>& obs);//mouvement horizontaux de l'adversaire
        std::vector<int> update(hitBox& colBox,bool persoIsHiting,int persoDommage,hitBox& persoWeaponBox);//mise � jour avec les collisions avec le joueur
        void hit(int dommage);//permet de recevoir des d�g�ts
        void updateAnim();//mise � jour de l'animation
        void updateOrientation();//mise � jour de l'orientation en fonction de sa vitesse
        void kill();//permet de tuer l'adversaire
        void gravity(std::vector<plateforme>& obs);//mouvement verticaux de l'adversaire(relatif � la gravit�)
        virtual ~joe();
    protected:






        int m_life;//sant� de l'adversaire
        int m_animAv;//avancement de l'animation
        int m_point;//point donnant � sa mort

        bool m_goToBeat;//si il se prepare � attaquer
        bool m_isBeating;//si il attaque
        bool m_colD;//si il est en collision avec le sol
        bool m_beHit;//si il peut recevoir des d�g�ts
        bool m_colorChange;//si il peut changer de couleur lors de son clignotement
        bool m_isAlive;//si il est en vie
        bool m_isDying;//si il est en train de mourrir
        bool m_givePoint;//si il peut donner des points(lors de sa mort)


        //temps entre 2 actions
        float m_HitCouldown;//entre 2 possibilit�s de recevoir des d�g�s
        float m_DomageBlink;//entre 2 clignotement

        float m_beatTime;//temps d'attauqe
        float m_goToBeatTime;//temps de pr�paration de l'attaque

        float m_attractionForce;//force actuel de la gravit�
        float m_force;//force max de la gravit�
        float m_applyforce;//temps entre 2 applications de la gravit�
        float m_vitesse;//vitesse de l'adversaire
        float m_animTime;//temps d'animation

        std::string m_orientation;//orientation (gauche ou droite)

        //horloge permettant de g�rer l'adversaire
        sf::Clock m_domageBlinckClock;
        sf::Clock m_domageClock;
        sf::Clock m_applyforceClock;
        sf::Clock m_animTimeClock;
        sf::Clock m_beatClock;
        sf::Clock m_deathClock;

    private:
};

#endif // JOE_H
