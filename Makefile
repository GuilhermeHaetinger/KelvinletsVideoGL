CC=g++
SRC=./src/
BIN=./bin/
KELVIN=./kelvin

MAIN=$(SRC)main.cpp
MAIN_OBJECT=$(BIN)main.o
LOGGER=$(SRC)Logger/Logger.cpp
LOGGER_OBJECT=$(BIN)Logger.o

LINE=$(SRC)Line.cpp
LINE_OBJECT=$(BIN)Line.o
POINT=$(SRC)Point.cpp
POINT_OBJECT=$(BIN)Point.o


OPENGL_FLAGS=-lpthread -lX11 -std=c++11 -lglfw -lGLEW -lglut -lGL
OPENCV_FLAGS=`pkg-config opencv --cflags --libs`
FLAGS = $(OPENGL_FLAGS) $(OPENCV_FLAGS)

$(KELVIN): $(MAIN_OBJECT) $(LOGGER_OBJECT) $(LINE_OBJECT) $(POINT_OBJECT) 
	$(CC) -o $(KELVIN) $(MAIN_OBJECT) $(LOGGER_OBJECT) $(LINE_OBJECT) $(POINT_OBJECT) $(FLAGS)

$(MAIN_OBJECT): $(MAIN)
	$(CC) -o $(MAIN_OBJECT) -c $(MAIN) $(FLAGS)

$(LOGGER_OBJECT): $(LOGGER)
	$(CC) -o $(LOGGER_OBJECT) -c $(LOGGER) $(FLAGS)

$(LINE_OBJECT): $(LINE)
	$(CC) -o $(LINE_OBJECT) -c $(LINE) $(FLAGS)

$(POINT_OBJECT): $(POINT)
	$(CC) -o $(POINT_OBJECT) -c $(POINT) $(FLAGS)

clean:
	rm ./bin/*
