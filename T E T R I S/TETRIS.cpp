#include"miniwin.h"
using namespace miniwin;
const int t=25;
void patrat(int x, int y)
{

    dreptunghi_l(1+x*t, 1+y*t, x*t+t, y*t+t);
}
void piesa_1(int x, int y)
{
    culoare(verde);
    patrat(x,y);
    patrat(x+1,y+0);
    patrat(x+1,y+1);
    patrat(x+2,y+1);
}

int main()
{
    redimensionare(t*10,t*20);
    int x=0,y=0;
    int k=cheie();
    piesa_1(x,y);
    refresh();
    while(k!=int('Q'))
    {
        if(k==jos)
           y++;
        else if(k==sus)
                y--;
        else if(k==dreapta)
                x++;
        else if(k==stanga)
                x--;
        if(t!=nimic)
        {
          elimina();
          piesa_1(x,y);
          refresh();
        }
        k=cheie();
    }
    inchide();
}
