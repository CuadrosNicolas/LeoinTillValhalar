#ifndef PANDA_H
#define PANDA_H
#include "adversaire.h"
#include "generalTexture.h"
#include "plateforme.h"
#include "Vue.h"
#include <iostream>
#include "BlackBird.h"
#include "laser.h"
///adversaire sp�ciale utilis� comme boss de fin
///sa mort signifie la fin d'une partie
///compos� de diff�rente pattern qui s'enchaine apr�s le contact avec le joueur
///attaque au corps � corps,s'asseois(l'empechant d'�tre attaqu�) et fais tomb� une pluis de blackBird,vole de gauche � droite puis envoie un laser qui �llimine instantanement le joueur
///recommence � chaque contact avec le joueur une fois termin�
class panda : public adversaire
{
    public:
        panda(float posX,float posY);
        void updateCollision(std::vector<plateforme>& plList,Vue& vue,std::vector<blocusAdv>& BadvList);//mise � jour des collisions avec les plateforms et blocus d'adversaire
        std::vector<int> update(hitBox& colBox,bool persoIsHiting,int persoDommage,hitBox& persoWeaponBox);//mise � jour avec les collisions avec le joueur
        void hit(int dommage);
        void kill();
        void gravity(std::vector<plateforme>& obs);//mouvement verticaux de l'adversaire(relatif � la gravit�)
        virtual ~panda();
    protected:
        bool m_isActive;
        bool m_isAttack;
        bool m_isPausing;
        bool m_isBlocking;
        bool m_colD;
        bool m_isDead;
        bool m_givePoint;
        bool m_isFlying;
        bool m_isFlyingTAdvBlocus;
        bool m_goToBeat;
        bool m_goToFly;
        bool m_isGoToLaser;
        bool m_isLaser;

        int m_life;//sant� de l'adversaire
        int m_point;//point donnant � sa mort
        int m_animAv;

        float m_pauseTime;
        float m_laserTime;
        float m_goToLaserTime;
        float m_attackTime;
        float m_attractionForce;//force actuel de la gravit�
        float m_force;//force max de la gravit�
        float m_applyforce;//temps entre 2 applications de la gravit�
        float m_goToBeatTime;
        float m_goToFlyTime;


        sf::Clock m_applyforceClock;
        sf::Clock m_controlClock;
        hitBox m_spawn;
        laser m_laser;



        bool m_beHit;//si il peut recevoir des d�g�ts
        bool m_colorChange;//si il peut changer de couleur lors de son clignotement

        //temps entre 2 actions
        float m_HitCouldown;//entre 2 possibilit�s de recevoir des d�g�ts
        float m_DomageBlink;//entre 2 clignotement

        //horloge permettant de g�rer l'adversaire
        sf::Clock m_domageBlinckClock;
        sf::Clock m_domageClock;
        std::map<std::string,std::vector<coordTab> > m_laserPos;
        std::string m_etat;
        std::vector<BlackBird> m_blackBirdList;

        hitBox m_dommageBox;



    private:
};

#endif // PANDA_H
