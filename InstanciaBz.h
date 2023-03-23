#ifndef InstanciaBZ
#define InstanciaBZ

#ifdef WIN32
#include <windows.h>
#include <GL/glut.h>
#endif


#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#include <ctime>
#include <fstream>
#include <sstream>
#include "Ponto.h"
#include "Temporizador.h"
#include "Bezier.h"
#include <vector>

using namespace std;

class InstanciaBz
{
    Temporizador temp;
    public:
        vector<Ponto> Vertices;
        Ponto Pos, Vetor;
        Bz *bezier, *nextBz;
        double deltaT, t;
        int currentBz, dir, nextBzIndex;
        float velo, h, b;
        bool halfPoint = false;
        bool isPlayer;
        unsigned char R, G, B;

        InstanciaBz();
        InstanciaBz(Bz *bezier, float velo = 4);
        InstanciaBz(Bz *bezier, float velo, float h, float b , unsigned char R, unsigned char G, unsigned char B);
        void Posiciona(float temp = 0);
        void DesenhaPlayer();
        void DesenhaInimigo();
        void selectNext(int n);
}; 
void setTamanho(float *tamanho);
#endif