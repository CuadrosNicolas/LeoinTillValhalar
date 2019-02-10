#include "fonction.h"

fonction::fonction()
{
    //ctor
}
float fonction::convertStrToFlo(std::string text)
{
        float f;
        std::istringstream(text) >> f;
        return f;
}
    std::string fonction::extract(std::string nom)
    {
        std::string ret("");
        for(int e=0;e <nom.size();e++)
        {
            if(nom[e] == '_')
                e = nom.size();
            else
                ret += nom[e];
        }
        return ret;

    }

std::vector<std::string> fonction::loadData(const char* chemin)
{

            //r�cup�ration fichier dans un tableau de caract�re
            std::ifstream fichier(chemin);
            std::string ligne("");
            std::vector<std::string> tab;
            if(fichier)
            {
                while(getline(fichier,ligne)){
                    if (ligne[ligne.size() - 1] == '\r')
                        ligne.erase(ligne.size() - 1);
                    tab.push_back(ligne);
                }
            }
            return tab;//renvoie du tableau

}
         std::map<std::string,std::vector<pixelCoordTab> > fonction::loadAnim(const char* chemin)
       {
    std::map<std::string,std::vector<pixelCoordTab> > m_animMapTab;
    std::vector<int> dataNumber;
    std::ifstream test(chemin);//r�cup�ration du fichier
    std::string ligne("");
    int a(0);
    int av(0);
    int tab_av(0);
    int nbe_Anim(25);
    std::string anim_etape("");
    int number(0);
    if(test)
    {
            while(getline(test,ligne))
        {
            if(ligne[ligne.size()-1]=='\r')
               ligne .erase(ligne.size() - 1);
            if(a >= nbe_Anim*4 + 2)
            {
                for(int e = 0;e <dataNumber.size();e += 4 )
                {
                    //initialisation les tableaux de coordonn�es
                    m_animMapTab[anim_etape].push_back(pixelCoordTab(dataNumber[e],dataNumber[e+1]));
                    m_animMapTab[anim_etape][tab_av].getTab()[2] =  dataNumber[e+2];
                    m_animMapTab[anim_etape][tab_av].getTab()[3] =  dataNumber[e+3];
                    tab_av++;
                }
                    tab_av = 0;
                    dataNumber.clear();
                    a = 0;
            }
            if(a == 0)
            {
                anim_etape = ligne;
            }
            if(a == 1)
            {
                              std::istringstream(ligne ) >> number;
                              nbe_Anim = number;
            }
            if(a > 1 && a <(nbe_Anim*4 + 2))
            {
              std::istringstream(ligne ) >> number;
                dataNumber.push_back(number);



            }
            a++;
        }

    }
     return m_animMapTab;
        }
                 std::map<std::string,std::vector<coordTab> > fonction::loadBoxTab(const char* chemin)
       {
    std::string anim_etape;
    std::map<std::string,std::vector<coordTab> > m_animMapTab;
    std::vector<std::string> tab;
    tab = loadData(chemin);
    int nbeAnim(0);
    int a(0);
    for(int e = 0;e<tab.size();e++)
    {

                if(a == 0)
                    anim_etape = tab[e];
                if(a == 1)
                    nbeAnim = convertStrToFlo(tab[e]);
                if(a > 1)
                {
                    m_animMapTab[anim_etape].push_back(coordTab(convertStrToFlo(tab[e]),convertStrToFlo(tab[e+1])));
                    e++;
                }
                if(a > nbeAnim)
                    a = 0;
                else
                    a++;



    }


     return m_animMapTab;
        }
std::string fonction::textBack(std::string textR)
{


    std::string text;
    for(int e = 0; e < textR.size() - 1 ; e++)
    {
        text += textR[e];
    }
    return text;

}
fonction::~fonction()
{
    //dtor
}
