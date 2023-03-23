#include "Bezier.h"

int bzMax = 25;
Bz *bezi = (Bz*)calloc(bzMax, sizeof(Bz));
int beziSize = 0;
vector<Ponto> pontosDoCenario;

Bz::Bz()
{
    
}

Bz::Bz(int p1, int p2, int p3)
{
    vertices[0] = p1;
    vertices[1] = p2;
    vertices[2] = p3;
    calculaComprimento();
}

void Bz::addPoint(int i, int ponto)
{
    vertices[i] = ponto;
}

Ponto Bz::calcula(double t)
{
    Ponto P = pontosDoCenario[vertices[0]];
    double UmMenosT = 1-t;
    P =  pontosDoCenario[vertices[0]] * (UmMenosT * UmMenosT) + pontosDoCenario[vertices[1]] * 2 * (UmMenosT * t) + pontosDoCenario[vertices[2]] * (t*t);
    return P;
}

void Bz::drawLine()
{
    double deltaT = 0.02;
    double tt = 0;
    if(selected) {
        glColor3f(1, 0, 1);
        glLineWidth(3);
    }
    Ponto P = pontosDoCenario[vertices[0]];
    glBegin(GL_LINE_STRIP);
    while (tt < 1.0)
    {
        P = calcula(tt);
        glVertex2f(P.x, P.y);
        tt = tt + deltaT;
    }
    P = calcula(1.0); // faz o fechamento da curva
    glVertex2f(P.x, P.y);
    glEnd();
}

Bz* Bz::getNextBz(float dir, int index, int &nextBz, bool isPlayer)
{
    int bzIndex;
    if(dir > 0)
    {
        if(outBind.size() == 0) return bezi;
        index = index % outBind.size();
        bzIndex = outBind[index];
    }
    else
    {
        if(inBind.size() == 0) return bezi;
        index = index % inBind.size();
        bzIndex = inBind[index];
    }
    nextBz = index;
    if(isPlayer) (bezi + bzIndex)->selected = true;
    return (bezi + bzIndex);
}

void Bz::calculaComprimento()
{
    double DeltaT = 1.0/50;
    double t=DeltaT;
    Ponto P1, P2;
    comprimento = 0;
    P1 = calcula(0.0);
    while(t<1.0)
    {
        P2 = calcula(t);
        comprimento += calculaDistancia(P1,P2);
        P1 = P2;
        t += DeltaT;
    }
    P2 = calcula(1.0); // faz o fechamento da curva
    this->comprimento += calculaDistancia(P1,P2);
    //cout << "comprimento: " << comprimento << endl;
}


void bindBz(int bzOut, int bzIn)
{
    (bezi + bzOut)->outBind.push_back(bzIn);
    (bezi + bzIn)->inBind.push_back(bzOut);
    printf("bind %d %d\n", bzOut, bzIn);
}

void unbind(int bzOut, int bzIn)
{
    (bezi + bzOut)->outBind.pop_back();
    (bezi + bzIn)->outBind.pop_back();
}

void putPoint(Ponto p)
{
    pontosDoCenario.push_back(p);
}

void putBezi(Bz b)
{
    *(bezi + beziSize) = b;
    beziSize++;
}

void setPoint(int i, Ponto p)
{
    pontosDoCenario[i] = p;
}

void draw(bool hidePoints, int selectedPoint, int selectedBezier, bool bezierBuffer, int bezierInBuff)
{
    for (int i = 0; i < beziSize; i++)
    {
        glLineWidth(1);
        if(i == selectedBezier) glColor3f(1, 0, 1);
        else if(bezierBuffer && bezierInBuff == i) glColor3f(1, 1, 0);
        else glColor3f(0, 1, 1);
        getBeziAddress(i)->drawLine();
    }
    for (int i = 0; i < pontosDoCenario.size(); i++)
    {
        if(hidePoints) break;
        if(i == selectedPoint) glColor3f(1, 0, 1);
        else glColor3f(0, 1, 1);
        glPointSize(5);
        glBegin(GL_POINTS);
        glVertex3f(pontosDoCenario[i].x, pontosDoCenario[i].y, pontosDoCenario[i].z);
        glEnd();
    }
}

void removeBezi()
{
    beziSize--;
}

void removePoint()
{
    pontosDoCenario.pop_back();
}

void clear()
{
    beziSize = 0;
    pontosDoCenario.clear();
}

int getBeziSize()
{
    return beziSize;
}

int pontosSize()
{
    return pontosDoCenario.size();
}

Ponto getPonto(int i)
{
    return pontosDoCenario[i];
}

Bz getBezi(int i)
{
    return bezi[i];
}

Bz* getBeziAddress(int i)
{
    return &bezi[i];
}

bool beziFull()
{
    return beziSize == bzMax;
}