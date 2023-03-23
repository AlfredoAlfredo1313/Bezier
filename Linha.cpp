

#include <cstdlib>

#include "Linha.h"
Linha::Linha()
{
    
}
Linha::Linha(float x1,float y1,float x2,float y2)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;

    GeraEnvelope();
}

void Linha::GeraEnvelope()
{
    Ponto P;
    P = ObtemMinimo(Ponto(x1,y1), Ponto(x2,y2));
    minx = P.x;
    miny = P.y;
   // P.imprime("Minimo: ", "\n");
    
    P = ObtemMaximo(Ponto(x1,y1), Ponto(x2,y2));
    maxx = P.x;
    maxy = P.y;
   // P.imprime("Maximo: ", "\n");

    Meio = Ponto((maxx+minx)/2,(maxy+miny)/2);
    MeiaLargura = Ponto((maxx-minx)/2,(maxy-miny)/2);
   // Meio.imprime("Meio: ", "\n");
   // MeiaLargura.imprime("Meia Largura: ", "\n");
}
void Linha::geraLinha(int limite, int TamMax)
{
    float deltaX,deltaY;
        
    do{
        x1 = (rand() % limite*10)/10.0;
    } while (x1<0 || x1>=limite);
    do{
        y1 = (rand() % limite*10)/10.0;
    } while (y1<0 || y1>=limite);
    
    deltaX = (rand() % limite)/(float)limite;
    deltaY = (rand() % limite)/(float)limite;
    
    do{
        if(rand()%2)
            x2 = x1 + deltaX * TamMax;
        else x2 = x1 - deltaX * TamMax;
    } while (x2<0 || x2>=limite);
    
    do{
        if(rand()%2)
            y2 = y1 + deltaY * TamMax;
        else y2 = y1 - deltaY * TamMax;
    } while (y2<0 || y2>=limite);
    GeraEnvelope();
    
}


void Linha::desenhaLinha()
{
	glBegin(GL_LINES);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();
}

bool Linha::EnvelopesColidem(Linha L)
{
    float distancia;
    //Meio
    distancia = fabs(Meio.x - L.Meio.x);
   //Meia Largura = (max.x - min.x)/2
    if (distancia > (MeiaLargura.x + L.MeiaLargura.x))
        return false;
    distancia = fabs(Meio.y - L.Meio.y);
    //cout << "distancia Y: " << distancia << endl;
    if (distancia > (MeiaLargura.y + L.MeiaLargura.y))
        return false;
    return true;
}

