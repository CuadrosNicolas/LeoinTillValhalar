#ifndef VUE_H
#define VUE_H
#include <SFML/Graphics.hpp>
#include "hitbox.h"
class Vue : public hitBox //objet g�rent la vue en couplant une sf::View avec une hitbox pour afficher uniquement les objets pr�sent � l'�cran
{
    public:
        Vue(int sizeX,int sizeY);
        void setPos(float posX,float posY);
        sf::View& getView();
        virtual ~Vue();
    protected:
        sf::View m_camera;
        int m_screenSizeX;
        int m_screenSizeY;

    private:
};

#endif // VUE_H
