/*
 * CCGLWidget.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#include "CGLWidget.h"

#include <QResizeEvent>
#include <cassert>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CWorkQueue.h"

using namespace std;

CGLWidget::CGLWidget(CQueuePtr queue, QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f)
: QGLWidget(parent, shareWidget, f), mWorker(this, queue), mQueue(queue)
{

}

CGLWidget::~CGLWidget()
{
	stopWorking();
}

/// starts the worker thread
void CGLWidget::startWorking()
{
	setAutoBufferSwap(false);
	this->doneCurrent();
	mWorker.start();
}

/// Stops the worker thread
void CGLWidget::stopWorking()
{
	mWorker.stop();
	mWorker.wait();
}

void CGLWidget::addModel(CModelPtr model)
{
	mWorker.addModel(model);
}

CModelPtr CGLWidget::getModel(unsigned int model_index)
{
	return mWorker.getModel(model_index);
}

void CGLWidget::replaceModel(unsigned int model_index, CModelPtr new_model)
{
	mWorker.replaceModel(model_index, new_model);
}

void CGLWidget::removeModel(unsigned int model_index)
{
	mWorker.removeModel(model_index);
}

/// Override the QGLWidget::glDraw function when the worker thread is running.
void CGLWidget::glDraw()
{
	// If the worker is not running, we render using the default glDraw function
	// (which eventually calls paintGL).
	if(!mWorker.isRunning())
	{
		QGLWidget::glDraw();
	}
	else
	{
		if(this->isVisible())
		{
			WorkPtr op = make_shared<WorkItem>(RENDER_TO_SCREEN);
			mQueue->push(op);
		}

	}
}

/// Initalize the OpenGL context.
void CGLWidget::initializeGL()
{
	// no initialization is required.
}

/// Initalizes the model rendering region and starts the rendering thread.
void CGLWidget::initRegion(unsigned int width, unsigned int height, double scale)
{
	assert(width > 0);
	assert(height > 0);
	assert(scale > 0);

	mScale = scale;

	// Change the widget's size, notify the parent, resize the default framebuffer
	setFixedSize(QSize(width, height));
	updateGeometry();
	glViewport(0, 0, (GLint)width, (GLint)height);

	// Setup the view:
	double half_width = width * mScale / 2;
	double half_height = width * mScale / 2;
	double depth = 500; // hard-coded to 500 units (typically mas) in each direction.
	mView = glm::ortho(-half_width, half_width, -half_height, half_height, -depth, depth);

	if(mWorker.isRunning())
		stopWorking();
}

/// Renders to the default OpenGL framebuffer
void CGLWidget::paintGL()
{
	// Until the worker thread is running, we render a blank gray window.
	if(!mWorker.isRunning())
	{
		glClearColor(0.5, 0.5, 0.5, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

/// Resizes the widget.
void CGLWidget::resizeGL(int width, int height)
{
	// we do not permit the widget to be resized.
}
