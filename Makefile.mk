# Makefile para Windows

PROG = BasicGLProgram.exe
FONTES = Ponto.cpp Temporizador.cpp Main.cpp InstanciaBz.cpp Bezier.cpp Poligono.cpp
OBJETOS = $(FONTES:.cpp=.o)
CPPFLAGS = -O0 -g -Iinclude # -Wall -g  # Todas as warnings, infos de debug
# Se estiver usando mingw64, troque lib por lib\x64 abaixo
LDFLAGS = -Llib -lfreeglut -lopengl32 -lglu32 -lm
CC = g++

$(PROG): $(OBJETOS)
	$(CC) $(CPPFLAGS) $(OBJETOS) -o $@ $(LDFLAGS)

clean:
	-@ del $(OBJETOS) $(PROG)
