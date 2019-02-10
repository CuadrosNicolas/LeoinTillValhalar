#ifndef PIXELCOORDTAB_H
#define PIXELCOORDTAB_H
#include <vector>

class pixelCoordTab //tableau permettant de contenir les coordonées(position du coin supérieur gauche et taille) d'une image(frame) d'une animation
{
    public:
        pixelCoordTab(int firstPx,int firstPy);
        std::vector<int>& getTab();
        virtual ~pixelCoordTab();
    protected:
        std::vector<int> m_tab;
    private:
};

#endif // PIXELCOORDTAB_H
