//
//  Poligono.hpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#ifndef Poligono_hpp
#define Poligono_hpp

#include <iostream>
using namespace std;


#ifdef WIN32
#include <windows.h>
#include <GL/glut.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

#include "Ponto.h"
#include "Bezier.h"
#include <vector>

class Poligono
{
    vector <Ponto> Vertices;
    Ponto Min, Max;
public:
    Poligono();
    Ponto getVertice(int);
    void getVerticeVec(vector<Ponto> &Pontos);
    unsigned long getNVertices();
    void insereVertice(Ponto p);
    void insereVertice(Ponto p, int pos);
    void inserePointer(Ponto &p);
    Ponto* getVerticeAddress(int i);
    Ponto* getLastAddress();
    void desenhaPoligono();
    void desenhaVertices();
    void pintaPoligono();
    void imprime();
    void atualizaLimites();
    void obtemLimites(Ponto &Min, Ponto &Max);
    void desenhaAresta(int n);
    void getAresta(int i, Ponto &P1, Ponto &P2);
    void alteraVertice(int i, Ponto P);
    void imprimeVertices();
    void setPoint(int i, int val);
    int getMeiaLargura();
};
bool LePoligono(const char *nome);
#endif
