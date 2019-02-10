#ifndef BLACKSCREEN_H
#define BLACKSCREEN_H
#include <SFML/Graphics.hpp>
#include "Vue.h"
#include "generalTexture.h"

//�cran noir qui peux se fermer ou s'ouvrir pour symboliser les transitions
class blackScreen
{
    public:
        blackScreen();
        blackScreen(Vue& view);
        void update(sf::RenderWindow& window);//mise � jour de l'�cran
        void open();//ouvre l'�cran
        void close();//ferme l'�cran
        bool isOpen();//renvoie si il est ouvert
        bool isClose();//renvoie si il est ferm�
        virtual ~blackScreen();
    protected:
        bool m_isOpen;//si il est ouvert
        bool m_isClose;//si il est ferm�
        bool m_goToOpen;//si il est en train de s'ouvrir
        bool m_goToClose;//si il est en train de se fermer
        float m_openTime;//temps d'ouvertur

        float m_centerY;//centre de fermetur
        float m_posY;//position verticale des points qui permettent la fermeture de l'�cran
        Vue* m_vue;//vue du jeu
        sf::VertexArray m_vertexArrayTop;//rectangle haut
        sf::VertexArray m_vertexArrayBot;//rectangle bas
    private:
};

#endif // BLACKSCREEN_H
