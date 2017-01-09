



#ifndef _MINIWIN_H_
#define _MINIWIN_H_

#include <iostream>

#ifndef MINIWIN_SOURCE
#define main _main_
#endif

int _main_();

std::ostream& log();



namespace miniwin {

void elimina();
void refresh();
void mensaj(std::string msj);
bool intrebare(std::string msj);
void asteptare(int miliseg);

int  latine();
int  dimensiune();
void redimensionare(int ample, int alt);
void inchide();

void culoare(int c);
void culoare_rgb(int r, int g, int b);

void punct(float x, float y);
void linie(float x_ini, float y_ini, float x_fin, float y_fin);
void dreptunghi(float izq, float arr, float der, float aba);
void dreptunghi_l(float izq, float arr, float der, float aba);
void cerc(float x_cen, float y_cen, float radio);
void cerc_l(float x_cen, float y_cen, float radio);
void text(float x, float y, const std::string& texto);

int cheie();

bool  raton(float& x, float& y);
bool  raton_in();
float raton_x();
float raton_y();
void  raton_butoane(bool& izq, bool& der);
bool  raton_buton_izq();
bool  raton_buton_der();

enum {
  ESCAPE,
  stanga, dreapta, jos, sus,
  F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
  spatiu,
  inapoi,
  nimic
};

enum {
  negru, rosu,verde , albastru,
  galben, purpuriu, cyan, alb
};

} // namespace miniwin

#endif

