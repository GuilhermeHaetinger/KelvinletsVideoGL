#ifndef VIDEO_DEFORMER_HEADER
#define VIDEO_DEFORMER_HEADER

#include "opencv2/opencv.hpp"

#include "KelvinletsTransformer.h"
#include "InterpolationFrame.h"
#include "RenderableFrame.h"
#include "Deformation.h"
#include "Logger/Logger.h"

class VideoDeformer{
	private:
		KelvinletsTransformer kelvinletsTransformer;
		InterpolationFrame * interpolationFrames;
	public:
		VideoDeformer(float elasticShearModulus, float poissonRatio, float radius, cv::VideoCapture video);
		RenderableFrame * deform(Deformation deformation);
};

#endif
