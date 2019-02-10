#ifndef GENERALTEXTURE_H
#define GENERALTEXTURE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "fonction.h"
class generalTexture//classe permettant de charger les texture du jeu
{
    public:
        generalTexture();
        //chargement d'une texture avec couleur de fond
        static sf::Texture load(std::string nom);

        //initialisation des textures
        static void initiate();

        //différente texture du jeu
        static sf::Texture persoText;
        static sf::Font TextFont;
        static sf::Color m_maskColor;
        //liste des textures en fonction de leur nom (charger avec textureList.txt)
        static std::map<std::string ,sf::Texture> textureList;
        //liste récupérer dans le fichier de texture(textureList.txt)
        static std::map<std::string , std::string> plateList;



        virtual ~generalTexture();
    protected:
    private:
};

#endif // GENERALTEXTURE_H
