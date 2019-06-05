#include "../include/KelvinletsTransformer.h"

KelvinletsTransformer::KelvinletsTransformer(GLfloat poissonRatio, GLfloat elasticShearModulus){
	  this->a = 1 / (4 * glm::pi<float>() * poissonRatio);
    this->b = this->a / (4 - 4 * elasticShearModulus);
    this->c = 2 / (3 * this->a - 2 * this->b);
}

GLfloat ** KelvinletsTransformer::grab(GLfloat ** videoVertices){
	return NULL;
}
