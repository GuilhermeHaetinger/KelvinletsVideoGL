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
PROPORTIONS=$(SRC)Proportions.cpp
PROPORTIONS_OBJECT=$(BIN)Proportions.o
DEFORMATION=$(SRC)Deformation.cpp
DEFORMATION_OBJECT=$(BIN)Deformation.o



INTERPOLATION_FRAME=$(SRC)InterpolationFrame.cpp
INTERPOLATION_FRAME_OBJECT=$(BIN)InterpolationFrame.o

KELVINLETS_TRANSFORMER=$(SRC)KelvinletsTransformer.cpp
KELVINLETS_TRANSFORMER_OBJECT=$(BIN)KelvinletsTransformer.o

VIDEO_DEFORMER=$(SRC)VideoDeformer.cpp
VIDEO_DEFORMER_OBJECT=$(BIN)VideoDeformer.o



RENDERABLE_FRAME=$(SRC)RenderableFrame.cpp
RENDERABLE_FRAME_OBJECT=$(BIN)RenderableFrame.o
FRAME=$(SRC)Frame.cpp
FRAME_OBJECT=$(BIN)Frame.o
VIDEO_GL=$(SRC)VideoGL.cpp
VIDEO_GL_OBJECT=$(BIN)VideoGL.o
VIDEO_WINDOW=$(SRC)VideoWindow.cpp
VIDEO_WINDOW_OBJECT=$(BIN)VideoWindow.o
SHADER_COMPILER=$(SRC)ShaderCompiler.cpp
SHADER_COMPILER_OBJECT=$(BIN)ShaderCompiler.o

OPENGL_FLAGS=-lpthread -lX11 -std=c++11 -lglfw -lGLEW -lglut -lGL -lfreeimage
OPENCV_FLAGS=`pkg-config opencv4 --cflags --libs`
FLAGS=$(OPENGL_FLAGS) $(OPENCV_FLAGS)

DEPENDECIES=$(MAIN_OBJECT) $(LOGGER_OBJECT) $(LINE_OBJECT) $(POINT_OBJECT) $(RENDERABLE_FRAME_OBJECT) $(VIDEO_GL_OBJECT) $(VIDEO_WINDOW_OBJECT) $(SHADER_COMPILER_OBJECT) $(PROPORTIONS_OBJECT) $(FRAME_OBJECT) $(DEFORMATION_OBJECT) $(INTERPOLATION_FRAME_OBJECT) $(KELVINLETS_TRANSFORMER_OBJECT) $(VIDEO_DEFORMER_OBJECT) 

$(KELVIN): $(DEPENDECIES)
	$(CC) -o $(KELVIN) $(MAIN_OBJECT) $(LOGGER_OBJECT) $(LINE_OBJECT) $(POINT_OBJECT) $(RENDERABLE_FRAME_OBJECT) $(VIDEO_GL_OBJECT) $(VIDEO_WINDOW_OBJECT) $(SHADER_COMPILER_OBJECT) $(PROPORTIONS_OBJECT) $(FRAME_OBJECT) $(DEFORMATION_OBJECT) $(INTERPOLATION_FRAME_OBJECT) $(KELVINLETS_TRANSFORMER_OBJECT) $(VIDEO_DEFORMER_OBJECT) $(FLAGS)

$(MAIN_OBJECT): $(MAIN)
	$(CC) -o $(MAIN_OBJECT) -c $(MAIN) $(FLAGS)

$(LOGGER_OBJECT): $(LOGGER)
	$(CC) -o $(LOGGER_OBJECT) -c $(LOGGER) $(FLAGS)

$(POINT_OBJECT): $(POINT)
	$(CC) -o $(POINT_OBJECT) -c $(POINT) $(FLAGS)

$(LINE_OBJECT): $(LINE)
	$(CC) -o $(LINE_OBJECT) -c $(LINE) $(FLAGS)

$(RENDERABLE_FRAME_OBJECT): $(RENDERABLE_FRAME)
	$(CC) -o $(RENDERABLE_FRAME_OBJECT) -c $(RENDERABLE_FRAME) $(FLAGS)

$(VIDEO_GL_OBJECT): $(VIDEO_GL)
	$(CC) -o $(VIDEO_GL_OBJECT) -c $(VIDEO_GL) $(FLAGS)

$(VIDEO_WINDOW_OBJECT): $(VIDEO_WINDOW)
	$(CC) -o $(VIDEO_WINDOW_OBJECT) -c $(VIDEO_WINDOW) $(FLAGS)

$(SHADER_COMPILER_OBJECT): $(SHADER_COMPILER)
	$(CC) -o $(SHADER_COMPILER_OBJECT) -c $(SHADER_COMPILER) $(FLAGS)

$(PROPORTIONS_OBJECT): $(PROPORTIONS)
	$(CC) -o $(PROPORTIONS_OBJECT) -c $(PROPORTIONS) $(FLAGS)

$(FRAME_OBJECT): $(FRAME)
	$(CC) -o $(FRAME_OBJECT) -c $(FRAME) $(FLAGS)

$(DEFORMATION_OBJECT): $(DEFORMATION)
	$(CC) -o $(DEFORMATION_OBJECT) -c $(DEFORMATION) $(FLAGS)

$(INTERPOLATION_FRAME_OBJECT): $(INTERPOLATION_FRAME)
	$(CC) -o $(INTERPOLATION_FRAME_OBJECT) -c $(INTERPOLATION_FRAME) $(FLAGS)

$(KELVINLETS_TRANSFORMER_OBJECT): $(KELVINLETS_TRANSFORMER)
	$(CC) -o $(KELVINLETS_TRANSFORMER_OBJECT) -c $(KELVINLETS_TRANSFORMER) $(FLAGS)

$(VIDEO_DEFORMER_OBJECT): $(VIDEO_DEFORMER)
	$(CC) -o $(VIDEO_DEFORMER_OBJECT) -c $(VIDEO_DEFORMER) $(FLAGS)	

clean:
	rm ./bin/*
