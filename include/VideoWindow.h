#ifndef VIDEO_WINDOW_HEADER
#define VIDEO_WINDOW_HEADER

#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Proportions.h"
#include "ShaderCompiler.h"
#include "Logger/Logger.h"

class VideoWindow{
	private:
		GLuint vertexBuffer;
		GLuint colorBuffer;
		GLuint indexBuffer;
		GLFWwindow * glWindow;
		Proportions proportions;
		void initializeBuffers();
		void initializeBufferData();
		void initializeVertexData();
		void initializeColorData();
		void initializeIndexData();
		GLuint * initializeIndexArray();
		void initializeGLFW();
		void initializeGLEW();
		void initializeGLFWWindow();
		void initializeShaderProgram();
	public:
		VideoWindow(Proportions proportions);
		GLuint getVertexBuffer();
		GLuint getColorBuffer();
		GLuint getIndexBuffer();
		int getNumberOfVertices();
		int getNumberOfIndices();
		Proportions getProportions();
		GLFWwindow * getGLFWWindow();
};

#endif
