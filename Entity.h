#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include "hitBox.h"
#include "generalTexture.h"
#include "pixelCoordTab.h"
#include <fstream>
#include <sstream>
#include <iostream>


class Entity
{
    public:

        Entity();// constructeur de l'entité sans argument
        Entity(float posX,float posY);// constructeur de l'entité avec position X et Y
        std::map<std::string,std::vector<pixelCoordTab> > loadAnim(const char* chemin);//chargment d'animation pour le personnage en fonction du fichier "chemin"
        bool ToggleBox();// active ou desative l'affichage des hitboxs
        bool toglleFlyMod();//active ou desative le mode vol du personnage

        //recupérateur des atributs de l'objets
        float getSizeX();//recupere la taille X
        float getSizeY();//recupere la taille Y
        float getPosX();//recupere la position X
        float getPosY();//recupere la position Y
        hitBox& getBox();//recupère la hitbox
        sf::Sprite& getSprite();//recupère le sprite

        void update();//mise a jour de l'entité
        void draw(sf::RenderWindow& screen);
        void setPosition(float posX,float posY);//change la position
        void move(float movX,float movY);//bouge l'entité

        void kill();
        void hit(int dommage);
        int getDommage();
        int getPoint();

        std::string getOrientation();
        virtual ~Entity();


    protected:

        int m_animAv;

        float m_applyforce;//lapse de temps pour l'application des forces verticales
        float m_jumpForce;//jump force pendant l'application des forces
        float m_attractionForce;//force d'attraction pendant l'application des force
        float m_jumpForceTotale;//force du jump
        float m_vitesseTour;//vitesse
        float m_posX;//position x
        float m_posY;//position y
        float m_flyModToggleTime;//temps du toggle
        float m_toggleBoxTime;
        float m_vitesse;//vitesse de 1 pixel
        float m_sizeX;//taille X du sprite
        float m_sizeY;//taille Y du sprite
        float m_force;//force maximale
        int m_life;
        int m_lifeMax;
        int m_point;
        int m_dommage;
        float m_HitCouldown;

        bool m_jumpActive;//si le jump est actif
        bool m_mouvU;//si mouvement haut
        bool m_mouvD;//si mouvement bas
        bool m_mouvR;//si mouvement droite
        bool m_mouvL;//si mouvement gauche
        bool m_drawBoxToggle;//si les hitBoxs sont dessinnés
        bool m_flyMod;//si le flymod est activé
        bool m_attack;
        bool m_colD;
        bool m_colUp;

        std::string m_etat;
        std::string m_run_right;
        std::string m_run_left;
        std::string m_wait_right;
        std::string m_wait_left;
        std::string m_jump_right;
        std::string m_jump_left;
        std::string m_attack_left;
        std::string m_attack_right;
        std::map<std::string,std::vector<pixelCoordTab> > m_animMapTab;
        std::map<std::string,float> m_animTimeTab;
        std::string m_orientation;
        sf::Sprite m_sprite;//sprite
        sf::Texture* m_texture;//texture
        sf::Clock m_toggleClockFlyMod;//clock du toggle fly
        sf::Clock m_toggleClockBox;
        sf::Clock m_applyforceClock;//clock de l'application des forces
        sf::Clock m_animClock;
        sf::Clock m_domageClock;



        hitBox m_colBox;//box de collision de degat






    private:
};

#endif // ENTITY_H
