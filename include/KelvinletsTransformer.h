#ifndef KELVINLETS_TRANSFORMER_HEADER
#define KELVINLETS_TRANSFORMER_HEADER

#include <glm/gtc/constants.hpp>
#include <glm/vec3.hpp>

#include "RenderableFrame.h"
#include "Deformation.h"
#include "Logger/Logger.h"

class KelvinletsTransformer{
	private:
		GLfloat a, b, c;
		Deformation deformation;
	public:
		KelvinletsTransformer( Deformation deformation, GLfloat poissonRatio, GLfloat elasticShearModulus);
		vec3 grab(glm::vec3 position);	
};

#endif
