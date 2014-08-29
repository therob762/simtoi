/*
 * CWorker.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#include "CWorker.h"
#include "CGLWidget.h"

#include <QGLFramebufferObjectFormat>

#include "OpenGL.h" // OpenGL includes, plus several workarounds for various OSes

#include "CWorkQueue.h"

#include <sys/timeb.h>
int GetMilliCount()
{
	// Something like GetTickCount but portable
	// It rolls over every ~ 12.1 days (0x100000/24/60/60)
	// Use GetMilliSpan to correct for rollover
	timeb tb;
	ftime( &tb );
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int GetMilliSpan( int nTimeStart )
{
	int nSpan = GetMilliCount() - nTimeStart;
	if ( nSpan < 0 )
		nSpan += 0x100000 * 1000;
	return nSpan;
}

CWorker::	CWorker(CGLWidget * glWidget, CQueuePtr queue)
{
	mGLWidget = glWidget;
	mQueue = queue;
	mDoWork = true;
	mStopInstructed = false;
}

CWorker::~CWorker()
{
	// TODO Auto-generated destructor stub
}

void CWorker::stop()
{
	mStopInstructed = true;

	WorkPtr op = make_shared<WorkItem>(EXIT);
	mQueue->push(op);
}

void CWorker::resizeGL (int width, int height)
{
	// do nothing (for now)
}

void CWorker::initializeGL()
{
	// Set the clear color to black with no transparency
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Dithering is a fractional pixel filling technique that allows you to
	// combine some colors to create the effect of other colors. The non-full
	// fill fraction of pixels could negatively impact the interferometric
	// quantities we wish to simulate. So, disable dithering.
	glDisable(GL_DITHER);

	// Enable multi-sample anti-aliasing to improve the effective resolution
	// of the model area.
	// This should be enabled by default due to QGLFormat in src/main.cpp
	//glEnable(GL_MULTISAMPLE);

	// Enable depth testing to permit vertex culling
	glEnable(GL_DEPTH_TEST);

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create an RGBA32F MAA buffer
    QGLFramebufferObjectFormat fbo_format = QGLFramebufferObjectFormat();
    fbo_format.setInternalTextureFormat(GL_RGBA32F);
    fbo_format.setTextureTarget(GL_TEXTURE_2D);

    mFBO_render.reset(new QGLFramebufferObject(mGLWidget->size(), fbo_format));

	CHECK_OPENGL_STATUS_ERROR(glGetError(), "Could not create mFBO_render");
}

void CWorker::run()
{
	// take control of the OpenGL context
	mGLWidget->makeCurrent();
	mDoWork = true;

	float color = 0;

	initializeGL();

	int start = GetMilliCount();
	double time = 0;
	unsigned int frames = 0;

	WorkPtr op;

	while(mDoWork)
	{
		// Get the next operation
		mQueue->wait_and_pop(op);

		if(op->getType() == RENDER_TO_SCREEN && !mGLWidget->isVisible())
		{
			mQueue->push(op);
			continue;
		}


		switch(op->getType())
		{

		case EXIT:
			// Only process the exit event if we have been instructed to exit.
			if(mStopInstructed)
				mDoWork = false;
			else
				mQueue->push(op);

			break;

		case TEST_RENDERING:
			// Renders to the off-screen buffer as quickly as possible. Blits
			// to the screen if necessary.

			mFBO_render->bind();
			CHECK_OPENGL_STATUS_ERROR(glGetError(), "Could not bind to mFBO_render");
			glClearColor(color, 0.0, 0.0, 0.0);
			CHECK_OPENGL_STATUS_ERROR(glGetError(), "glClearColor failed");
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			CHECK_OPENGL_STATUS_ERROR(glGetError(), "glClear failed");
			mFBO_render->release();
			CHECK_OPENGL_STATUS_ERROR(glGetError(), "Could not bind release mFBO_render");

			if(mGLWidget->isVisible())
			{
				// blit the off-screen buffer to the default buffer
				QRect region(0, 0, mGLWidget->size().width(), mGLWidget->size().height());
				QGLFramebufferObject::blitFramebuffer (0, region, mFBO_render.get(), region);
				CHECK_OPENGL_STATUS_ERROR(glGetError(), "blitFramebuffer failed");
				mGLWidget->swapBuffers();
			}

			mQueue->push(op);
			break;

		case RENDER_TO_SCREEN:
			// Renders directly to GL_BACK and swaps buffers

			glClearColor(color, 0.0, 0.0, 0.0);
			CHECK_OPENGL_STATUS_ERROR(glGetError(), "glClearColor failed");
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			CHECK_OPENGL_STATUS_ERROR(glGetError(), "glClear failed");

			mGLWidget->swapBuffers();
			break;

		}

		frames += 1;
		color += 0.10;
		color = fmod(color, 1);

	}

	time = double(GetMilliSpan(start)) / 1000;
	cout << "Thread " << mID << " framerate: " << double(frames) / time << " fps" << endl;

	mGLWidget->doneCurrent();
}
