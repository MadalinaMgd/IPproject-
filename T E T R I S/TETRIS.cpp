#include<cstdlib>
#include<ctime>
#include"miniwin.h"
using namespace miniwin;
const int t=25;
const int linii=20;
const int coloane=10;

typedef int tabel[coloane][linii];
struct coordonate{int x,y;};


struct piesa{coordonate orig;
             coordonate perif[3];
             int culoare;
             coordonate pozitie(int n)const;//n cuprins intre 0 si 3(0=central, 1-3 periferii)
            };

coordonate piesa::pozitie(int n)const
{
    coordonate ret={orig.x, orig.y};
    if(n!=0)
    {
        ret.x+=perif[n-1].x;
        ret.y+=perif[n-1].y;
    }
    return ret;
}

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
    coordonate ret={-c.y, c.x};
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

coordonate perifs[7][3]={{{1,0},{0,1},{1,1}},//patrat
                         {{1,0},{-1,1},{0,1}},//s
                         {{0,1},{1,1},{-1,0}},//2
                         {{0,1},{0,-1},{1,1}},//L
                         {{0,1},{0,-1},{-1,1}},//L invers
                         {{-1,0},{1,0},{0,1}},//T
                         {{0,1},{0,-1},{0,2}},//bara
                        };

void piesa_noua(piesa&p)
{
    p.orig.x=5;
    p.orig.y=3;
    p.culoare=1+rand()%6; //1-RAND_MAX+1
    //culoare piese random
    int r=rand()%7;
    int i;
    for(i=0;i<3;i++)
        p.perif[i]=perifs[r][i];
    //piese random

}

bool tabel_linie_plina(const tabel&tab, int linie)
{
    for(int i=0;i<coloane;i++)
        if(tab[i][linie]==negru)
           return false;
    return true;
}

void tabel_eliminare_linie(tabel&tab, int linie)
{
    for(int j=linie;j>0;j--)
        {
            for(int i=0;i<coloane;i++)
                tab[i][j]=tab[i][j-1];
        }
    for(int i=0;i<coloane;i++)
        tab[i][0]=negru;
}


int tabel_linie(tabel&tab)
{
    int linie=linii-1;
    int contor=0;
    while(linie>=0)
    {
        if(tabel_linie_plina(tab, linie))
            {
                tabel_eliminare_linie(tab, linie);
                contor++;
            }
        else linie--;
    }
    return contor;
}

int main()
{
    redimensionare(t*coloane+220,t*linii+100);
    srand(time(0));
    int tic=0;
    tabel tab;
    tabel_gol(tab);
    tabel_1(tab);
    piesa c;
    piesa_noua(c);
    piesa_colturi(c);
    refresh();
    int k=cheie();
    while(k!=ESCAPE)
    {
        piesa copie=c;
        if(k==nimic && tic>43)
        {
            tic=0;
            k=jos;
        }
        if(k==jos)
            c.orig.y++;
        else
            {if(k==sus)
            rotire_dreapta(c);
             else
                {if(k==dreapta)
                c.orig.x++;
                else
                   {if(k==stanga)
                   c.orig.x--;}}}
        if(coliziune_tabel(tab, c))
            {
                c=copie;
                if(k==jos)
                {
                    tabel_incrustare_piesa(tab,c);
                    int cont=tabel_linie(tab);
                    piesa_noua(c);
                }
            }

        if(k!=nimic)
        {
            elimina();
            tabel_1(tab);
            culoare(alb);
            linie(0,0,0,t*linii);
            linie(0,t*linii,t*coloane,t*linii);
            linie(t*coloane,t*linii,t*coloane,0);
            piesa_colturi(c);
            refresh();
        }
        asteptare(30);
        tic++;
        k=cheie();
    }
    inchide();
    return 0;
}
