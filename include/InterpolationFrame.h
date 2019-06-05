#ifndef INTERPOLATION_FRAME_HEADER
#define INTERPOLATION_FRAME_HEADER

#include <GLFW/glfw3.h>

#include "Line.h"
#include "Logger/Logger.h"

class InterpolationFrame{
	private:
		enum TypeOfArray{
			POSITION,
			COLOR
		};
		glm::vec3 getInterpolation(TypeOfArray type, int line);
		GLfloat * getInterpolatedArray(TypeOfArray type);
		int frameIndex;
		int numberOfLines;
		Line * lines;
	public:
		InterpolationFrame(int width, int height, int frameIndex);
		void addLine(Line line, int index);
		GLfloat * getInterpolatedVertexArray();
		GLfloat * getInterpolatedColorArray();
};
#endif
