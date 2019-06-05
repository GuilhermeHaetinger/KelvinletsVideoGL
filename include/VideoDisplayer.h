#ifndef VIDEO_DISPLAYER_HEADER
#define VIDEO_DISPLAYER_HEADER

#include "RenderableFrame.h"
#include "Logger/Logger.h"

class VideoDisplayer{
	private:
		RenderableFrame * renderableFrames; 
	public:
		VideoDisplayer(RenderableFrame * renderableFrames);
		void show();
};

#endif
