/*
 * CWorker.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#include "CWorker.h"

#include "CGLWidget.h"

CWorker::	CWorker(CGLWidget * glWidget)
{
	mGLWidget = glWidget;
	mDoWork = true;
}

CWorker::~CWorker() {
	// TODO Auto-generated destructor stub
}

void CWorker::stop()
{
	mDoWork = false;
}

void CWorker::resizeViewport(const QSize &size)
{
//    QMutexLocker locker(&mutex);
//    viewportWidth = size.width();
//    viewportHeight = size.height();
//    initSwirlyItems();
//    textCounter = 0;
//    messageYPos = -1;
}

void CWorker::run()
{
	// take control of the OpenGL context
	mGLWidget->makeCurrent();

	float color = 0;

	while(mDoWork)
	{
		// change the background clear color
//		mFBO_render->bind();
//		CHECK_OPENGL_STATUS_ERROR(glGetError(), "Could not bind to mFBO_render");
		glClearColor(color, 0.0, 0.0, 0.0);
//		CHECK_OPENGL_STATUS_ERROR(glGetError(), "glClearColor failed");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		CHECK_OPENGL_STATUS_ERROR(glGetError(), "glClear failed");
//		mFBO_render->release();

		// blit the off-screen buffer to the default buffer
//		QRect region(0, 0, glw->size().width(), glw->size().height());
//		QGLFramebufferObject::blitFramebuffer (0, region, mFBO_render.get(), region);
//		CHECK_OPENGL_STATUS_ERROR(glGetError(), "blitFramebuffer failed");
		mGLWidget->swapBuffers();

		// update the color
		color += 0.10;
		color = fmod(color, 1);
	}
}
