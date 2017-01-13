#include<cstdlib>
#include<ctime>
#include<sstream>
#include<string>
#include"miniwin.h"
using namespace std;
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
    dreptunghi_l(20+1+x*t, 20+1+y*t, 20+x*t+t, 20+y*t+t);
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
    p.orig.x=13;
    p.orig.y=2;
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

string afisare_string(int puncte)
{
    stringstream sout;
    sout<<puncte;
    return sout.str();
}

void reaparitie(const tabel&tab, const piesa&p, const piesa&sig, int puncte, int nivel)
{
    const int latime=t*coloane;
    const int inaltime=t*linii;
    elimina();
    tabel_1(tab);
    culoare(alb);
    linie(20,20,20,20+inaltime);
    linie(20,20+inaltime,20+latime,20+inaltime);
    linie(20+latime,20+inaltime,20+latime,20);
    text(40+latime, 20, "Piesa urmatoare:");
    text(40+latime, 150, "Nivel");
    text(40+latime, 250, "Puncte");
    culoare(alb);
    text(40+latime, 270, afisare_string(puncte));
    text(40+latime, 170, afisare_string(nivel+1));
    piesa_colturi(p);
    piesa_colturi(sig);
    refresh();
}

const int puncte_limite[10]={50,100,130,150,170,200,240,260,400};

const int tics_nivel[10]={33,25,20,18,16,14,12,10,8,2};

void game_over()
{
    culoare(alb);
    text(140,240,"GAME OVER!");
    refresh();
    asteptare(4500);
    inchide();
}

int main()
{
    redimensionare(t*coloane+220,t*linii+100);
    srand(time(0));
    int tic=0, puncte=0, nivel=0;
    tabel tab;
    tabel_gol(tab);

    piesa c, sig;
    piesa_noua(c);
    piesa_noua(sig);
    c.orig.x=5;


    reaparitie(tab,c,sig, puncte, nivel);

    int k=cheie();
    while(k!=ESCAPE)
    {
        piesa copie=c;
        if(k==nimic && tic>tics_nivel[nivel])
        {
            tic=0;
            k=jos;
        }
        if(k==int('N'))
            nivel++;
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
                    int puncte=puncte+cont*cont;
                    if(puncte>puncte_limite[nivel])
                        nivel++;
                    c=sig;
                    piesa_noua(sig);
                    c.orig.x=5;
                    if(coliziune_tabel(tab,c))
                        game_over();

                }
            }

        if(k!=nimic)
        {
            reaparitie(tab,c,sig, puncte, nivel);
        }
        asteptare(30);
        tic++;
        k=cheie();
    }
    inchide();
    return 0;
}
