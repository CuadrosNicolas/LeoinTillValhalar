#include "pixelCoordTab.h"

pixelCoordTab::pixelCoordTab(int firstPx,int firstPy)
{
//oentre les valeurs dans le tableau
m_tab.push_back(firstPx);
m_tab.push_back(firstPy);
m_tab.push_back(0);
m_tab.push_back(0);
}
        std::vector<int>& pixelCoordTab::getTab()//permet de récupérer le tableau
        {
            return this->m_tab;
        }
pixelCoordTab::~pixelCoordTab()
{
    //dtor
}
