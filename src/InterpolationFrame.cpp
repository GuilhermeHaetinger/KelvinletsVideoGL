#include "../include/InterpolationFrame.h"

void vec3ToFloatArray(GLfloat * array, int index, vec3 vector);
///

GLfloat * InterpolationFrame::getInterpolatedArray(TypeOfArray type){
	GLfloat * array = new GLfloat[this->numberOfLines * 3];
	for(int line = 0, counter = 0; line < this->numberOfLines; line++, counter+=3){
		vec3 interpolatedPosition = this->getInterpolation(type, line);
		vec3ToFloatArray(array, counter, interpolatedPosition);
	}
	return array;
}

vec3 InterpolationFrame::getInterpolation(TypeOfArray type, int line){
	return type == POSITION ?
		this->lines[line].interpolatePosition(this->frameIndex) :
		this->lines[line].interpolateColor(this->frameIndex);
}

InterpolationFrame::InterpolationFrame(int width, int height, int frameIndex){
	this->frameIndex = frameIndex;
	this->numberOfLines = width * height;
	this->lines = (Line *)malloc(numberOfLines * sizeof(Line)); 
}

void InterpolationFrame::addLine(Line line, int index){lines[index] = line;}


GLfloat * InterpolationFrame::getInterpolatedVertexArray(){
	return this->getInterpolatedArray(this->TypeOfArray::POSITION);
}

GLfloat * InterpolationFrame::getInterpolatedColorArray(){
	return this->getInterpolatedArray(this->TypeOfArray::COLOR);
}

///
void vec3ToFloatArray(GLfloat * array, int index, vec3 vector){
	array[index] = vector[0];
	array[index + 1] = vector[1];
	array[index + 2] = vector[2];
}
