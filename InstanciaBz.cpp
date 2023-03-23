#include "InstanciaBz.h"

float *tamanhoPointer;

InstanciaBz::InstanciaBz(){}
  
InstanciaBz::InstanciaBz(Bz *bezier, float velo)
{
    isPlayer = true;
    time_t tempo;
    srand((unsigned) time(&tempo));
    this->bezier = bezier;
    this->Pos = bezier->calcula(0);
    this->velo = velo;
    Ponto NextPoint = bezier->calcula(t + 0.02);
    this->b = 0.066;
    this->h = 0.2;
    this->t = 0;
    this->deltaT = 0.02;
    this->currentBz = 0;
    this->Vetor = NextPoint - Pos;
    Ponto VetorNormal = Vetor;
    VetorNormal.versor();
    Ponto p = Pos - VetorNormal * h;
    Ponto p2 = p + Ponto(VetorNormal.y, VetorNormal.x * -1) * b * (*tamanhoPointer);
    Ponto p3 = p + Ponto(VetorNormal.y, VetorNormal.x * -1) * (-b) * (*tamanhoPointer);
    Vertices.push_back(Pos);
    Vertices.push_back(p2);
    Vertices.push_back(p3);
}

InstanciaBz::InstanciaBz(Bz *bezier, float velo, float h, float b , unsigned char R, unsigned char G, unsigned char B)
{
    isPlayer = false;
    time_t tempo;
    srand((unsigned) time(&tempo));
    this->bezier = bezier;
    this->Pos = bezier->calcula(0);
    this->velo = velo;
    Ponto NextPoint = bezier->calcula(t + 0.02);
    this->h = h;
    this->b = b;
    this->R = R;
    this->G = G;
    this->B = B;
    this->t = velo > 0? 0.0 + (rand() % 4)/10.0 : 1 - (rand() % 4)/10.0;
    this->deltaT = 0.02;
    this->Vetor = NextPoint - Pos;
    Ponto VetorNormal = Vetor;
    VetorNormal.versor();
    Ponto p = Pos - VetorNormal * h;
    Ponto p2 = p + Ponto(VetorNormal.y, VetorNormal.x * -1) * b * (*tamanhoPointer);
    Ponto p3 = p + Ponto(VetorNormal.y, VetorNormal.x * -1) * (-b) * (*tamanhoPointer);
    Vertices.push_back(Pos);
    Vertices.push_back(p2);
    Vertices.push_back(p3);
}

void InstanciaBz::Posiciona(float tempo)
{
    float deslocamento = tempo * velo;
    deltaT = deslocamento/bezier->comprimento;
    t += deltaT;
    if((t > 0.5 && velo >0 || t < 0.5 && velo < 0) && !halfPoint)
    {
        halfPoint = true;
        nextBz = bezier->getNextBz(velo, rand(), nextBzIndex, isPlayer);
    }
    if(t + deltaT > 1.0 || t + deltaT < 0)
    {
        int aux = t + deltaT;
        t = 1 - aux;
        bezier = nextBz;
        halfPoint = false;
        if(isPlayer)bezier->selected = false;
    }
    Ponto NextPoint = bezier->calcula(t);
    Pos = Pos + Vetor;
    Vetor = NextPoint - Pos;    
    Ponto VetorNormal = Vetor;
    VetorNormal.versor();
    Ponto p = Pos - VetorNormal * h * (*tamanhoPointer);
    Ponto p2 = p + Ponto(VetorNormal.y, VetorNormal.x * -1) * b * (*tamanhoPointer);
    Ponto p3 = p + Ponto(VetorNormal.y, VetorNormal.x * -1) * (-b) * (*tamanhoPointer);
    Vertices[0] = Pos;
    Vertices[1] = p2;
    Vertices[2] = p3;
}

void InstanciaBz::DesenhaPlayer()
{
    glBegin(GL_POLYGON);
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
        glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
    }
    glEnd();
}

void InstanciaBz::DesenhaInimigo()
{
    glBegin(GL_POLYGON);
        glColor3ub(R, G, B);
        for (int i=0; i<Vertices.size(); i++)
        {
            glVertex3f(Vertices[i].x,Vertices[i].y,Vertices[i].z);
        }
    glEnd();
}


void InstanciaBz::selectNext(int n)
{
    if(!halfPoint) return;
    nextBz->selected = false;
    nextBzIndex = nextBzIndex + n;
    nextBz = bezier->getNextBz(velo, nextBzIndex, nextBzIndex);
}

void setTamanho(float *tamanho)
{
    tamanhoPointer = tamanho;
}