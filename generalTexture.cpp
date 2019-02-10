#include "generalTexture.h"
//d�claration des diff�rents oblets
sf::Texture generalTexture::persoText;
sf::Font generalTexture::TextFont;
sf::Color generalTexture::m_maskColor;
std::map<std::string , std::string> generalTexture::plateList;
std::map<std::string ,sf::Texture> generalTexture::textureList;
generalTexture::generalTexture()
{

}


void generalTexture::initiate()
{

            //initialisation des textures � partir du fichier TextureList.txt
            std::vector<std::string> tab;
            tab = fonction::loadData("./data/textureList/TextureList.txt");//on charge le fichier dans un tableau de chaine de caract�re
            int nbe(0);
            for(int e = 0;e<tab.size();e += 2)
            {
                generalTexture::plateList[tab[e]] = tab[e+1];
                nbe++;

            }
            for(std::map<std::string,std::string>::iterator it = generalTexture::plateList.begin();it!=generalTexture::plateList.end();++it)
                generalTexture::textureList[it->first] = sf::Texture();//on initialise les textures

            for(std::map<std::string,sf::Texture>::iterator it = generalTexture::textureList.begin();it!=generalTexture::textureList.end();++it)
            {
                for(std::map<std::string,std::string>::iterator it_b = generalTexture::plateList.begin();it_b!=generalTexture::plateList.end();++it_b)
                {
                    if(it->first == it_b->first)//si cette texture a le m�me nom que les informations de texture
                    {
                        if(!it->second.loadFromFile(it_b->second));//chargement de la texture qui lui correspond
                    }
                }
            }

    m_maskColor = sf::Color(30,255,0);//d�finition de la couleur d'arri�re plan d'une texture
    persoText = generalTexture::load("data/image/perso.png");//chargement de la texture du joueur
    TextFont.loadFromFile("data/text/BASKVILL.TTF");//chargement de la police de texte
}
sf::Texture generalTexture::load(std::string nom)//permet de charger une texture en cr�ant un masque en fonction de la couleur d'arri�re plan d�finit plus haut
{

    sf::Image image;
    image.loadFromFile(nom);
    image.createMaskFromColor(m_maskColor);
    sf::Texture texture;
    if(!texture.loadFromImage(image));

    return texture;

}




generalTexture::~generalTexture()
{
    //dtor
}
