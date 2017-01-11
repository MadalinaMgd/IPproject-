#include"miniwin.h"
using namespace miniwin;
const int t=25;
const int linii=20;
const int coloane=10;

struct coordonate{int x,y;};

struct piesa{coordonate orig;
             coordonate perif[3];
             int culoare;
             coordonate pozitie(int n)const;};

coordonate piesa::pozitie(int n)const
{
    coordonate ret;
    if(n==0)
    {
        ret.x=orig.x;
        ret.y=orig.y;
    }
    else
    {
        ret.x=orig.x+perif[n-1].x;
        ret.y=orig.y+perif[n-1].y;
    }
    return ret;
}

typedef int tabel[coloane][linii];

void patrat(int x, int y)
{
    dreptunghi_l(1+x*t, 1+y*t, x*t+t, y*t+t);
}

void piesa_colturi(const piesa&p)
{
    culoare(p.culoare);
    for(int i=0;i<4;i++)
        {
            coordonate c=p.pozitie(i);
            patrat(c.x, c.y);
        }

}

coordonate rotatie_dreapta(const coordonate&c)
{
    coordonate ret={-c.y,c.x};
    return ret;
}

void rotire_dreapta(piesa&p)
{
    for(int i=0;i<3;i++)
        p.perif[i]=rotatie_dreapta(p.perif[i]);
}

coordonate rotatie_stanga(const coordonate&c)
{
    coordonate ret={c.y, -c.x};
    return ret;
}

void rotire_stanga(piesa&p)
{
    for(int i=0;i<3;i++)
        p.perif[i]=rotatie_stanga(p.perif[i]);
}

void tabel_gol(tabel&tab)
{
    int i,j;
    for(i=0;i<coloane;i++)
    {
        for(j=0;j<linii;j++)
        tab[i][j]=negru;
    }
}

void tabel_1(const tabel&tab)
{
    int i,j;
    for(i=0;i<coloane;i++)
    {
        for(j=0;j<linii;j++)
        {
            culoare(tab[i][j]);
            patrat(i,j);
        }
    }
}

void tabel_incrustare_piesa(tabel&tab, const piesa&p)
{
    int i;
    int ox=p.orig.x;
    int oy=p.orig.y;
    tab[ox][oy]=p.culoare;
    for(i=0;i<3;i++)
        tab[ox+p.perif[i].x][oy+p.perif[i].y]=p.culoare;

}

bool coliziune_tabel(tabel&tab, const piesa&p)
{
    bool coliziune=false;
    int i;
    for(i=0;i<4;i++)
    {
        coordonate c=p.pozitie(i);
        //verifica limite
        if(c.x<0 || c.x>coloane)
            coliziune=true;
        if(c.y<0 || c.y<linii)
            coliziune=true;
        if(tab[c.x][c.y]!=negru)
            coliziune=true;

    }
    return coliziune;
}

int main()
{
    redimensionare(t*coloane,t*linii);
    piesa c={{5,10},{{1,0},{1,1},{0,1}},purpuriu};
    tabel tab;
    tabel_gol(tab);
    elimina();
    tabel_1(tab);
    refresh();
    return 0;
}

