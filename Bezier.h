#ifndef _B_
#define _B_

#ifdef _WIN32
#include <windows.h>
#include <GL/glut.h>
#endif


#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#include <vector>
#include <list>
#include "Ponto.h"

class Bz
{
    int vertices[3];
    int selectInd = 0;
    public:
        Bz();
        Bz(int p1, int p2, int p3);
        Ponto calcula(double t);
        void calculaComprimento();
        void addPoint(int i, int ponto);
        void drawLine();
        Bz* getNextBz(float dir, int index, int &nextBz, bool isPlayer = true);
        vector<int> inBind;
        vector<int> outBind;
        bool selected = false;
        float comprimento;
};
void bindBz(int bzOut, int bzIn);
void unbind(int bzOut, int bzIn);
void removeBezi();
void removePoint();
void clear();
void putPoint(Ponto p);
void putBezi(Bz b);
void setPoint(int i, Ponto p);
void draw(bool hidePoints, int selectedPoint, int selectedBezier, bool bezierBuffer, int bezierInBuff);
int getBeziSize();
int pontosSize();
Ponto getPonto(int i);
Bz getBezi(int i);
Bz* getBeziAddress(int i);
bool beziFull();

#endif