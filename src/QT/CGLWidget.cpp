/*
 * CCGLWidget.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#include "CGLWidget.h"
#include <QResizeEvent>

#include <cassert>
using namespace std;

CGLWidget::CGLWidget(QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f)
: QGLWidget(parent, shareWidget, f), mWorker(this)
{

}

CGLWidget::~CGLWidget()
{
	stopRendering();
}

void CGLWidget::startRendering()
{
	setAutoBufferSwap(false);
	this->doneCurrent();
	mWorker.start();
}

void CGLWidget::stopRendering()
{
	mWorker.stop();
	mWorker.wait();
}

void CGLWidget::paintGL()
{
	// Until the worker thread is running, we render a blank window.
	if(!mWorker.isRunning())
	{
		glClearColor(0.5, 0.5, 0.5, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

/// Override the QGLWidget::glDraw function when the worker thread is running.
void CGLWidget::glDraw()
{
	if(!mWorker.isRunning())
	{
		QGLWidget::glDraw();
	}
}

void CGLWidget::resizeGL(int w, int h)
{
	// we do not permit the widget to be resized.
}

void CGLWidget::initializeGL()
{
	// no intialization is required.
}

void CGLWidget::initRegion(unsigned int width, unsigned int height, double scale)
{
	assert(width > 0);
	assert(height > 0);
	assert(scale > 0);

	mImageWidth = width;
	mImageHeight = height;
	mImageScale = scale;

	if(mWorker.isRunning())
		stopRendering();
}
