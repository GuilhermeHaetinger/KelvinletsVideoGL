#ifndef FRAME_HEADER
#define FRAME

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


class Frame{
	private:
		int frameDeformed;
	public:
		Frame();
		glm::vec2 getPosition(int x, int y, int width);
		glm::vec3 getColor(int x, int y, int width);
		int isFrameDeformed();
		GLfloat z;
		GLfloat * vertexArray;
		GLfloat * colorArray;	
};

#endif
