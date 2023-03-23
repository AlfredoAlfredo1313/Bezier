# Makefile para Linux e macOS

PROG = bezier
FONTES = Main.cpp Bz.cpp ListaDeCoresRGB.cpp Poligono.cpp Ponto.cpp Temporizador.cpp
OBJETOS = $(FONTES:.cpp=.o)
CPPFLAGS = -g -O3 -DGL_SILENCE_DEPRECATION -Wno-deprecated # -Wall -g  # Todas as warnings, infos de debug
CC = g++

UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
	LDFLAGS = -framework OpenGL -framework Cocoa -framework GLUT -lm
else
	LDFLAGS = -lGL -lGLU -lglut -lm
endif

$(PROG): $(OBJETOS)
	$(CC) $(CPPFLAGS) $(OBJETOS) $(LDFLAGS) -o $(PROG)

clean:
	-@ rm -f $(OBJETOS) $(PROG)
