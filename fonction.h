#ifndef FONCTION_H
#define FONCTION_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "coordTab.h"
#include "pixelCoordTab.h"
#include <map>

class fonction //classe contenant les diff�rentes fonction r�curante du programme
{
    public:
        fonction();
        virtual ~fonction();
        //permet de convertir une chiffre en chaine de caract�re
        template<typename T>
        static std::string convertToString(T a);
        //permet de convertir une chaine de caract�re
        static float convertStrToFlo(std::string text);

        static std::map<std::string,std::vector<pixelCoordTab> > loadAnim(const char* chemin);//chargment d'animation pour le personnage en fonction du fichier "chemin"
        //chargement de la position de la hitbox de l'arme du joueur
        static std::map<std::string,std::vector<coordTab> > loadBoxTab(const char* chemin);
        //permet de charger un fichier et de le stocker dans une liste de tableau de caract�re
        static std::vector<std::string> loadData(const char* chemin);
        //permet d'extraire le debut d'une chaine de caract�re jusqu'� un '_'
        static std::string extract(std::string);
        static std::string textBack(std::string textR);//permet un retour en arri�re
    protected:
    private:
};
#include "fonction.tpp"
#endif // FONCTION_H
