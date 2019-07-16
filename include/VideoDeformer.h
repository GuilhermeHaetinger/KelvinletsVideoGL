#ifndef VIDEO_DEFORMER_HEADER
#define VIDEO_DEFORMER_HEADER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "opencv2/opencv.hpp"

#include "KelvinletsTransformer.h"
#include "InterpolationFrame.h"
#include "Proportions.h"
#include "Deformation.h"
#include "Logger/Logger.h"

class VideoDeformer{
	private:
		Proportions proportions;
		Frame * frames;
		GLfloat ** depthValue;
		KelvinletsTransformer kelvinletsTransformer;
		Frame * generateInterpolatedFrames(Frame * frames);
		Frame * interpolateFrames(InterpolationFrame * interpolationFrames);
    void drawPoints();
  public:
    VideoDeformer(Deformation deformation, Frame * frames, Proportions proportions);
    Frame * deform(Deformation deformation);
};

#endif
