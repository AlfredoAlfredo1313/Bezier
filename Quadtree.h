#ifndef Quadtree_hpp
#define Quadtree_hpp

#include <iostream>
#include "Ponto.h"
#include "Linha.h"
#include "Poligono.h"
#include <vector>
#include <stack>
#include "stdlib.h"


class Quadtree
{
    public:
    int *points;
    int pointsSize;
    int cumulativePoints;
    int childrenSize;
    Quadtree* children;
    Quadtree* address;
    Quadtree* Parent;
    float maxX, maxY, minX, minY, meioX, meioY, meiaLarguraX, meiaLarguraY;
    Quadtree();
    Quadtree(float xX, float xY, float nX, float nY, vector<Ponto> &p, int n, Quadtree* address);
    Quadtree(float xX, float xY, float nX, float nY, int *ps, int pointsSize, Quadtree* address, Quadtree* Parent);
    void countPoints();
    void countPoints(int *ps, int pSize);
    void genChildren();
    void draw();
    void print();
    void resetPoints(int n);
    int* treeDFS(Quadtree* node = NULL, int* ptr = NULL);
};
vector<Ponto> pontosCenario;
vector<Quadtree*> nodeList;
vector<Quadtree*> leafNodes;
int nPoints;



#endif
