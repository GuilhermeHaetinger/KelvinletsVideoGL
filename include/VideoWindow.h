#ifndef VIDEO_WINDOW_HEADER
#define VIDEO_WINDOW_HEADER

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Proportions.h"
#include "Logger/Logger.h"

class VideoWindow{
	private:
		GLuint vertexBuffer;
		GLuint colorBuffer;
		GLuint indexBuffer;
		GLFWwindow * glWindow;
		Proportions proportions;
		void initializeBuffers();
		void initializeGLFW();
		void initializeGLEW();
		void initializeGLFWWindow();
	public:
		VideoWindow(Proportions proportions);
		GLuint * getVertexBuffer();
		GLuint * getColorBuffer();
		GLuint * getIndexBuffer();
		Proportions getProportions();
};

#endif
