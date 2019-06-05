#ifndef KELVINLETS_TRANSFORMER_HEADER
#define KELVINLETS_TRANSFORMER_HEADER

#include <GLFW/glfw3.h>

#include "Logger/Logger.h"
#include <glm/gtc/constants.hpp>

class KelvinletsTransformer{
	private:
		GLfloat a, b, c;
	public:
		KelvinletsTransformer( GLfloat poissonRatio, GLfloat elasticShearModulus);
		GLfloat ** grab(GLfloat ** videoVertices);	
};

#endif
