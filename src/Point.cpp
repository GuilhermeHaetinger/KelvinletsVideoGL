#include "../include/Point.h"

Point::Point(vec3 position, vec3 color){
	this->position = position;
	this->color = color;
}

vec3 Point::getPosition(){return this->position;}
vec3 Point::getColor(){return this->color;}
