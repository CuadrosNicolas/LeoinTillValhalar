#ifndef PERSO_H
#define PERSO_H
#include <SFML/Graphics.hpp>
#include "plateforme.h"
#include "generalTexture.h"
#include "Vue.h"
#include "piece.h"
#include "checkpoint.h"
#include "pixelCoordTab.h"
#include "fonction.h"
#include "coordTab.h"
#include "adversaire.h"


class perso
{
    public:
        perso();
        perso(float posX,float posY);// constructeur du personnage en fonction de sa position
        void event();//g�re les evenement clavier/souris
        void setEtat(std::string& etat);
        void gravity(std::vector<plateforme>& obs);//applique la gravit�
        void mouv(std::vector<plateforme>& obs);//g�re les mouvements
        bool update(std::vector<plateforme>& obs,
                    sf::RenderWindow& window,Vue& view,std::vector<piece>& pieceList,std::vector<checkpoint>& checkList,std::vector<adversaire*>& advList);//update via les autres methodes ( event , gravity  et mouv)
        void draw(sf::RenderWindow& screen);//dessin du personnage dans la fenetre "screen"
        void kill();//permet de tuer le joueur(le fait retourner au dernier checkpoint)
        void hit(int dommage);//permet d'infliger des dommages au joueur
        void setScore(int score);//permet d'initialiser le score du joueur
        void updateScore(sf::RenderWindow& window,Vue& view);//permet de mettre � jour le score du joueur(l'affichage)
        void updateAnim();//permet de mettre � jour l'animation du joueur
        void changeLevel();//permet de d�finir si le joueur est en train de changer de niveau
        void setPos(float posX,float posY);//permet d'initialiser la position du joueur au d�but d'un niveau
        void setVictory();

        bool isEnd();
        //recup�rateur des atributs de l'objets
        float getSizeX();//recupere la taille X
        float getSizeY();//recupere la taille Y
        float getPosX();//recupere la position X
        float getPosY();//recupere la position Y
        hitBox& getBox();//recup�re la hitbox
        sf::Sprite& getSprite();//recup�re le sprite
        int getScore();

        virtual ~perso();


    protected:




                int m_animAv;

        bool m_isChangeLevel;
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

        //coordonn�es du fernier checkpoint touch�
        float m_checkPointX;
        float m_checkPointY;
        //temps entre 2 action
        float m_DomageBlink;//clignotement du jouer
        float m_HitCouldown;//entre 2 possibilit� d'�tre attaqu�
        float m_mouvTime;//entre 2 mouvements

        int m_score;//score du joueur
        int m_life;//sant� du joueur
        int m_lifeMax;//sant� maximum du jouer
        int m_dommage;//dommage du joueur
        int m_live;//nombre de vie du joueur


        bool m_dead;
        bool m_jumpActive;//si le jump est actif
        bool m_mouvR;//si mouvement droite
        bool m_mouvL;//si mouvement gauche
        bool m_attack;
        bool m_colD;
        bool m_beHit;
        bool m_colorChange;
        bool m_end;

        //etat actuel du joueur
        std::string m_etat;
        //d�claration des diff�rente type d'�tat du jouer
        std::string m_run_right;
        std::string m_run_left;
        std::string m_wait_right;
        std::string m_wait_left;
        std::string m_jump_right;
        std::string m_jump_left;
        std::string m_attack_left;
        std::string m_attack_right;

        //matrice contenant les diff�rentes animations en fonction de leur nom et de la frame actuel
        std::map<std::string,std::vector<pixelCoordTab> > m_animMapTab;
        //tableau de coordonn�e de la position de la hitbox de l'arme du joueur en fonction de l'animation
        std::map<std::string,std::vector<coordTab> > m_weaponBoxTab;
        //diff�rent temps d'animation de chaque animation
        std::map<std::string,float> m_animTimeTab;
        //orientation du joueur
        std::string m_orientation;
        sf::Sprite m_sprite;//sprite
        //sprite de la barre de vie
        sf::Sprite m_lifeBoard;//contour
        sf::Sprite m_lifeLigne;//ligne

        sf::Text m_scoreText;//score du joueur affichable
        sf::Text m_lifeText;//nombre de vie affichable
        sf::Texture* m_texture;//texture

        //diff�rente horloge permettant de g�rer le jouer
        sf::Clock m_applyforceClock;//clock de l'application des forces
        sf::Clock m_animClock;//horloge d'animaition
        sf::Clock m_domageClock;//horloge de d�gat
        sf::Clock m_domageBlinckClock;//horloge qui g�re le clignotement du jouer lorsqu'il est touch�
        sf::Clock m_fallingClock;//horloge permettant de controler le temps de chute du joueur
        sf::Clock m_mouvClock;//horloge g�rant l'intervalle de temps entre 2 d�placement


        //diff�rente hitbox du jouer
        hitBox m_colBox;//box de collision avec les plateformes
        hitBox m_weaponBox;//hitbox de l'arme
        hitBox m_dommageBox;//hitbox de collision avec les adversaires
        //pointeur vers le dernier checkpoint atteint
        checkpoint* m_check;








    private:
};

#endif // PERSO_H
