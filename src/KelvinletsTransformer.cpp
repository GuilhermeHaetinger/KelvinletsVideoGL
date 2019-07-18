#include "../include/KelvinletsTransformer.h"

mat3 productWithTranspost(vec3 x);

///
KelvinletsTransformer::KelvinletsTransformer(Deformation deformation, GLfloat poissonRatio, GLfloat elasticShearModulus) :
	deformation(deformation)
{
	  this->a = 1 / (4 * glm::pi<float>() * poissonRatio);
    this->b = this->a / (4 - 4 * elasticShearModulus);
    this->c = 2 / (3 * this->a - 2 * this->b);
}

vec3 KelvinletsTransformer::grab(vec3 position){

	vec3 r = position - this->deformation.getInitialPosition();
	float rLength =  length(r);
	float rEpslon = sqrt(pow(deformation.getRadius(), 2) + pow(rLength, 2));
	mat3 I  = mat3(1.0f);
	mat3 first = (float) ((this->a - this->b)/rEpslon) * I;
	mat3 second = (float) (this->b/pow(rEpslon, 2)/pow(rEpslon, 3)) * productWithTranspost(r);
	mat3 third = (float) ((a/2) * ((pow(this->deformation.getRadius(), 2)/pow(rEpslon, 3)))) * I;
	mat3 kelvinState = first + second + third;
	vec3 delta = this->c * this->deformation.getRadius() * kelvinState * this->deformation.getForce();
  return position + delta;
	///TODO RETARDATION!!!
}

///
mat3 productWithTranspost(vec3 x){
	return mat3(x[0] * x[0], x[1] * x[0], x[2] * x[0],
							x[0] * x[1], x[1] * x[1], x[2] * x[1],
							x[0] * x[2], x[1] * x[2], x[2] * x[2]);
}
