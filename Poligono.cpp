//
//  Poligono.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//
#include <iostream>
#include <fstream>
using namespace std;

#include "Poligono.h"

Poligono::Poligono()
{
    
}

void Poligono::insereVertice(Ponto p)
{
    this->Vertices.push_back(p);
}

void Poligono::insereVertice(Ponto p, int pos)
{
    if ((pos < 0) || (pos>Vertices.size()))
    {
        cout << "Metodo " << __FUNCTION__ << ". Posicao Invalida. Vertice nao inserido." << endl;
        return;
    }
    Vertices.insert(Vertices.begin()+pos, p);
}

void Poligono::inserePointer(Ponto &p)
{
    this->Vertices.push_back(p);
}

Ponto Poligono::getVertice(int i)
{
    return this->Vertices[i];
}

void Poligono::getVerticeVec(vector<Ponto> &Pontos)
{
    Pontos = Vertices;
}

Ponto* Poligono::getVerticeAddress(int i)
{
    return &Vertices[i];
}
void Poligono::pintaPoligono()
{
    glBegin(GL_POLYGON);
    for (int i=0; i<Vertices.size(); i++)
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
    glEnd();
}

void Poligono::desenhaPoligono()
{
    glBegin(GL_LINE_LOOP);
    for (int i=0; i<Vertices.size(); i++)
    {
        switch (i)
        {
        case 0:
            glColor3f(1.0f, 0.0f, 0.0f);
            break;

        case 1:
            glColor3f(0.0f, 1.0f, 0.0f);
            break;

        case 2:
            glColor3f(0.0f, 0.0f, 1.0f);
            break;

        default:
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        }
        if(Vertices.size() == 4) glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
    }
    glEnd();
}

void Poligono::desenhaVertices()
{
    for (int i=0; i<Vertices.size(); i++)
    {

        if(Vertices[i].brute != 1)
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            //cout << "(" << this -> Vertices[i].brute <<")\n";
            cout << " " << Vertices.size() << "\n";
        }
        else
        {
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        //if(i < 33) glColor3f(1.0f, 0.0f, 0.0f);
        //else if(i < 66) glColor3f(0.0f, 1.0f, 0.0f);
        //else glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_POINTS);
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
        glEnd();
    }
}

void Poligono::imprime()
{
    for (int i=0; i<Vertices.size(); i++)
        Vertices[i].imprime();
}

unsigned long Poligono::getNVertices()
{
    return Vertices.size();
}

void Poligono::obtemLimites(Ponto &Min, Ponto &Max)
{
    Max = Min = Vertices[0];

    for (int i=0; i<Vertices.size(); i++)
    {
        Min = ObtemMinimo (Vertices[i], Min);
        Max = ObtemMaximo (Vertices[i], Max);
    }
}

// **********************************************************************
//
// **********************************************************************
bool LePoligono(const char *nome)
{
    ifstream input;            // ofstream arq;
    input.open(nome, ios::in); //arq.open(nome, ios::out);
    if (!input)
    {
        cout << "Erro ao abrir " << nome << ". " << endl;
        return false;
    }
    cout << "Lendo arquivo " << nome << "...";
    string S;
    //int nLinha = 0;
    unsigned int qtdVertices;

    input >> qtdVertices;  // arq << qtdVertices

    for (int i=0; i< qtdVertices; i++)
    {
        double x,y;
        // Le cada elemento da linha
        input >> x >> y; // arq << x  << " " << y << endl
        if(!input)
            return false;
        //nLinha++;
        putPoint(Ponto(x,y));
    }
    unsigned int qtdCurvas;
    input >> qtdCurvas;
    for(int i = 0; i < qtdCurvas; i++)
    {
        int p1, p2, p3;
        input >> p1 >> p2 >> p3;
        putBezi(Bz(p1, p2, p3));
        if(!input)
            return false;
    }
    unsigned int qtdBinds;
    input >> qtdBinds;
    for(int i = 0; i < qtdBinds; i++)
    {
        int bzOut, bzIn;
        input >> bzOut >> bzIn;
        bindBz(bzOut, bzIn);
        if(!input)
            return false;
    }
    cout << "Pista lido com sucesso!" << endl;
    return true;

}

void Poligono::getAresta(int n, Ponto &P1, Ponto &P2)
{
    P1 = Vertices[n];
    int n1 = (n+1) % Vertices.size();
    P2 = Vertices[n1];
}

void Poligono::desenhaAresta(int n)
{
    glBegin(GL_LINES);
        glVertex3f(Vertices[n].x,Vertices[n].y,Vertices[n].z);
        int n1 = (n+1) % Vertices.size();
        glVertex3f(Vertices[n1].x,Vertices[n1].y,Vertices[n1].z);
    glEnd();
}

void Poligono::alteraVertice(int i, Ponto P)
{
    Vertices[i].x = P.x;
    Vertices[i].y = P.y;
    Vertices[i].z = P.z;
}

void Poligono::setPoint(int i, int val)
{
    Vertices[i].setBrute(val);
}

void Poligono::imprimeVertices()
{
    for (int i=0; i<Vertices.size(); i++)
        Vertices[i].imprime("", "\n");
}

int Poligono::getMeiaLargura()
{
    
}
