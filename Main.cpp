// **********************************************************************
// PUCRS/Escola Polit�cnica
// COMPUTA��O GR�FICA
//
// Programa basico para criar aplicacoes 2D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************

// Para uso do Windows, sugere-se a versao 17 do Code::Blocks

// Para uso no Xcode:
// Abra o menu Product -> Scheme -> Edit Scheme -> Use custom working directory
// Selecione a pasta onde voce descompactou o ZIP que continha este arquivo.

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include <GL/glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

#include "Ponto.h"
#include "Poligono.h"
#include "Temporizador.h"
#include "Bezier.h"
#include "InstanciaBz.h"
#include <vector>

Temporizador T;
double AccumDeltaT=0;

// Limites logicos da area de desenho
Ponto Min, Max, Tamanho, Meio;

InstanciaBz Player;
vector<InstanciaBz> Mobs;

Ponto smoothPoint = Ponto(0, 0);
stringstream sBuff;

bool openStringBuffer = false;
bool desenhaEixos = true;
bool FoiClicado = false;
bool gogo = false;
bool hidePoints = false;
bool pause = false;

void reshape( int w, int h );
void print();
void keyboard ( unsigned char key, int x, int y );

double t = 0;
int pointBufferIndex = 0;
int bezierBufferIndex = 0;
int pointBuffer[3];
int bezierBuffer[2];
int currentBZ = 0;
int selectedPoint = -1;
int selectedBezier = -1;
int enemyNumber = 10;
int drawSelect = 0;
float tamanho = 0;
double deltaT = 0.02;

void addPonto(int ponto)
{
    pointBuffer[pointBufferIndex] = ponto;
    pointBufferIndex++;
    pointBufferIndex = pointBufferIndex%3;
}

void build()
{
    
    Bz b = Bz();
    b.addPoint(0, pointBuffer[0]);
    b.addPoint(1, pointBuffer[1]);
    b.addPoint(2, pointBuffer[2]);
    printf("%d %d %d\n", pointBuffer[0], pointBuffer[1], pointBuffer[2]);
    b.calculaComprimento();
    putBezi(b);
    Ponto p1 = getPonto(pontosSize() - 1);
    Ponto p2 = getPonto(pontosSize() - 2);
    smoothPoint = p1 - p2 + p1;
    pointBuffer[0] = pointBuffer[2];
    pointBufferIndex = 1;
}

// **********************************************************************
// void init()
//  Faz as inicializacoes das variaveis de estado da aplicacao
// **********************************************************************
void init()
{
    // Define a cor do fundo da tela (AZUL)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Gera ou Carrega os pontos do cenario.
    // Note que o "aspect ratio" dos pontos deve ser o mesmo
    // da janela.
    Min.x--;Min.y--;
    Max.x++;Max.y++;
    reshape((int)Max.x - Min.x, (int)Max.y - Min.y);
    Meio = (Max+Min) * 0.5; // Ponto central da janela
    Tamanho = (Max-Min);  // Tamanho da janela em X,Y
    tamanho = Tamanho.x * Tamanho.y/5;
    setTamanho(&tamanho);
    if(LePoligono("Pista.txt"))
    {
        keyboard('g', 0, 0);
    }
}

double nFrames=0;
double TempoTotal=0;

void animate()
{
    double dt;
    dt = T.getDeltaT();
    AccumDeltaT += dt;
    TempoTotal += dt;
    nFrames++;

    if (AccumDeltaT > 1.0/30) // fixa a atualiza��o da tela em 30
    {
        AccumDeltaT = 0;
        glutPostRedisplay();
    }
    if (TempoTotal > 5.0)
    {
        //cout << "Tempo Acumulado: "  << TempoTotal << " segundos. " ;
        //cout << "Nros de Frames sem desenho: " << nFrames << endl;
        //cout << "FPS(sem desenho): " << nFrames/TempoTotal << endl;
        TempoTotal = 0;
        nFrames = 0;
    }
}
// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
// **********************************************************************
void reshape( int w, int h )
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela area OpenGL dentro da Janela
    glViewport(0, 0, w, h);
    // Define os limites logicos da area OpenGL dentro da Janela
    glOrtho(Min.x,Max.x,
            Min.y,Max.y,
            0,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void DesenhaEixos()
{

    glBegin(GL_LINES);
    //  eixo horizontal
        glVertex2f(Min.x,Meio.y);
        glVertex2f(Max.x,Meio.y);
    //  eixo vertical
        glVertex2f(Meio.x,Min.y);
        glVertex2f(Meio.x,Max.y);
    glEnd();
}

void DesenhaLinha(Ponto P1, Ponto P2)
{
    glBegin(GL_LINES);
        glVertex3f(P1.x,P1.y,P1.z);
        glVertex3f(P2.x,P2.y,P2.z);
    glEnd();
}

void display( void )
{
	// Limpa a tela coma cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

    // Define os limites l�gicos da �rea OpenGL dentro da Janela
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// Coloque aqui as chamadas das rotinas que desenham os objetos
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    if (desenhaEixos)
    {
        glLineWidth(1);
        glColor3f(1,1,1);
    }
    
    tamanho = Tamanho.x * Tamanho.y/10;
    draw(hidePoints, selectedPoint, selectedBezier, bezierBufferIndex == 1, bezierBuffer[0]);
    if(gogo)
    {
        if(!pause)Player.Posiciona(1.0/30);
        Player.DesenhaPlayer();
        for (int i = 0; i < enemyNumber; i++)
        {
            if(!pause)Mobs[i].Posiciona(1.0/30);
            Mobs[i].DesenhaInimigo();
        } 
    }
    jump:
	glutSwapBuffers();
}
// **********************************************************************
// ContaTempo(double tempo)
//      conta um certo n�mero de segundos e informa quanto frames
// se passaram neste per�odo.
// **********************************************************************
void ContaTempo(double tempo)
{
    Temporizador T;
    unsigned long cont = 0;
    //cout << "Inicio contagem de " << tempo << "segundos ..." << flush;
    while(true)
    {
        tempo -= T.getDeltaT();
        cont++;
        if (tempo <= 0.0)
        {
            //cout << "fim! - Passaram-se " << cont << " frames." << endl;
            break;
        }
    }

}
// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
// **********************************************************************

void keyboard ( unsigned char key, int x, int y )
{
    if(!gogo) goto jump;
    if(key == 'r') {
        Player.velo *= -1.0;
        Player.selectNext(0);
    }
    else if(key == 'h') hidePoints = !hidePoints;
    else if(key == 'g') {
        gogo = false;
        Player.nextBz->selected = false;
    }
    else if(key == ' ') pause = !pause;
    return;
    jump: 
	switch ( key )
	{
		case 27:        // Termina o programa qdo
			exit ( 0 );   // a tecla ESC for pressionada
			break;
        case 't':
            ContaTempo(3);
            break;
        case 'b':
            if(beziFull()) 
            {
                cout << "Bezi limit reached" << getBeziSize() << "\n";
                break;
            }
            build();
            cout << "Building Bz n" << getBeziSize() << "\n";
            break;
        case 'c':
            pointBufferIndex = 0;   
            break;
        case 'd':
            clear();
            bezierBufferIndex = 0;
            pointBufferIndex = 0;
            selectedBezier = -2;
            selectedPoint = -2;
            break;
        case 's':
            if(pointBufferIndex != 1) return;
            printf("%.2f %.2f\n", smoothPoint.x, smoothPoint.y);
            putPoint(smoothPoint);
            pointBuffer[1] = pontosSize() - 1;
            pointBufferIndex = 2;
            break;
        case 'r':
            if(pontosSize() > 0){
                removePoint();
                pointBufferIndex = pointBufferIndex == 0? 0 : pointBufferIndex - 1;
            }
            break;
        case 'z':
            if(getBeziSize() > 0) removeBezi();
            break;
        case 'g':
            if(getBeziSize() <= 0) break;
            Mobs.clear();
            time_t t;
            gogo = true;
            Player = InstanciaBz(getBeziAddress(0), 1);
            for (int i = 0; i < enemyNumber; i++)
            {
                srand((unsigned) i * time(&t));
                int bezi = i % getBeziSize();
                float velo = 1.0/((rand() % 4) + 1);
                velo  = rand() % 2 == 1? velo : velo * -1;
                unsigned r = rand() % 256;
                unsigned g = rand() % 256;
                unsigned b = rand() % 256;
                float base = ((rand() % 2) + 1.0)/((rand() % 2) + 1.0);
                float height = ((rand() % 2) + 1.0)/((rand() % 2) + 1.0);
                Mobs.push_back(InstanciaBz(getBeziAddress(bezi), velo, height * 0.2, base * 0.066, r, g, b));
            }
            selectedBezier = -1;
            selectedPoint = -1;
            bezierBufferIndex = 0;
            break;
        case 'h':
            hidePoints = !hidePoints;
            break;
        case ' ':
            if(selectedPoint >= 0) addPonto(selectedPoint);
            else if(selectedBezier >= 0) { 
                bezierBuffer[bezierBufferIndex] = selectedBezier;
                if(bezierBufferIndex == 1) bindBz(bezierBuffer[0], bezierBuffer[1]);
                bezierBufferIndex = (bezierBufferIndex + 1) % 2;
            }
            break;
        default:
			return;
	}
    glutPostRedisplay();
}
// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
    //system("CLS");
    float distancia = (Max.x - Min.x)/250;
	switch ( a_keys )
	{
        case GLUT_KEY_LEFT:       // Se pressionar LEFT
            if(!gogo) goto jump;
            if(pause) drawSelect = drawSelect < 1? 10 : drawSelect - 1;
            Player.velo /= 1.2;
            break;
jump:
            if(selectedPoint >= 0) selectedPoint = selectedPoint - 1 < 0? pontosSize() - 1 : selectedPoint - 1;
            else if(selectedBezier >= 0) selectedBezier = selectedBezier - 1 < 0? getBeziSize() - 1 : selectedBezier - 1;
            break;
        case GLUT_KEY_RIGHT:       // Se pressionar RIGHT
            if(!gogo) goto jump2;
            if(pause) drawSelect = (drawSelect + 1) % 11;
            Player.velo *= 1.2;
            break;
jump2:
            if(selectedPoint >= 0) selectedPoint = (selectedPoint + 1) % pontosSize();
            else if(selectedBezier >= 0) selectedBezier = (selectedBezier + 1) % getBeziSize();
            break;
		case GLUT_KEY_UP:
            if(gogo) {
                Player.selectNext(1);
                break;
            }
            selectedPoint = selectedPoint >= 0? -1 : 0;
            selectedBezier = -1;
            break;
	    case GLUT_KEY_DOWN:
            if(gogo) {
                Player.selectNext(-1); 
                break;
            }
            selectedPoint = -2;
            selectedBezier = selectedBezier >= 0? -2 : 0;
			break;
		default:
            return;
	}
    glutPostRedisplay();
}
// **********************************************************************
// Esta fun��o captura o clique do botao direito do mouse sobre a �rea de
// desenho e converte a coordenada para o sistema de refer�ncia definido
// na glOrtho (ver fun��o reshape)
// Este c�digo � baseado em http://hamala.se/forums/viewtopic.php?t=20
// **********************************************************************
void Mouse(int button,int state,int x,int y)
{    
    GLint viewport[4];
    GLdouble modelview[16],projection[16];
    GLfloat wx=x,wy,wz;
    GLdouble ox=0.0,oy=0.0,oz=0.0;

    if(gogo) return;
    if(state!=GLUT_DOWN)
      return;
    if(button!=GLUT_LEFT_BUTTON)
     return;
    //cout << "Botao da direita! ";

    glGetIntegerv(GL_VIEWPORT,viewport);
    y=viewport[3]-y;
    wy=y;
    glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
    glGetDoublev(GL_PROJECTION_MATRIX,projection);
    glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wz);
    gluUnProject(wx,wy,wz,modelview,projection,viewport,&ox,&oy,&oz);
    printf("%.2f %.2f\n", ox, oy);
    Ponto p = Ponto(ox, oy);
    putPoint(p);
    addPonto(pontosSize() - 1);
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
// **********************************************************************
int  main ( int argc, char** argv )
{
    //cout << "Programa OpenGL" << endl;

    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition (0,0);

    // Define o tamanho inicial da janela grafica do programa
    glutInitWindowSize  ( 500, 500);

    // Cria a janela na tela, definindo o nome da
    // que aparecera na barra de titulo da janela.
    glutCreateWindow    ( "Poligonos em OpenGL" );

    // executa algumas inicializa��es
    init ();

    // Define que o tratador de evento para
    // o redesenho da tela. A funcao "display"
    // ser� chamada automaticamente quando
    // for necess�rio redesenhar a janela
    glutDisplayFunc ( display );

    // Define que o tratador de evento para
    // o invalida��o da tela. A funcao "display"
    // ser� chamada automaticamente sempre que a
    // m�quina estiver ociosa (idle)
    glutIdleFunc(animate);

    // Define que o tratador de evento para
    // o redimensionamento da janela. A funcao "reshape"
    // ser� chamada automaticamente quando
    // o usu�rio alterar o tamanho da janela
    glutReshapeFunc ( reshape );

    // Define que o tratador de evento para
    // as teclas. A funcao "keyboard"
    // ser� chamada automaticamente sempre
    // o usu�rio pressionar uma tecla comum
    glutKeyboardFunc ( keyboard );

    // Define que o tratador de evento para
    // as teclas especiais(F1, F2,... ALT-A,
    // ALT-B, Teclas de Seta, ...).
    // A funcao "arrow_keys" ser� chamada
    // automaticamente sempre o usu�rio
    // pressionar uma tecla especial
    glutSpecialFunc ( arrow_keys );

    glutMouseFunc(Mouse);
    // inicia o tratamento dos eventos
    glutMainLoop ( );

    return 0;
}

