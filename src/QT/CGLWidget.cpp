/*
 * CCGLWidget.cpp
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#include "CGLWidget.h"
#include <QResizeEvent>

CGLWidget::CGLWidget(QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f)
: QGLWidget(parent, shareWidget, f)
	, mWorker(this)
	, mThread(this)
{

}

CGLWidget::~CGLWidget()
{
	stopRendering();
}

void CGLWidget::startRendering()
{
	mWorker.moveToThread(&mThread);
	connect(&mThread, SIGNAL(started()), &mWorker, SLOT(start()));
	mThread.start();
}

void CGLWidget::stopRendering()
{
	mWorker.stop();
	mThread.wait();
}

void CGLWidget::resizeEvent(QResizeEvent *event)
{
	mWorker.resizeViewport(event->size());
}

void CGLWidget::paintEvent(QPaintEvent *)
{
	// Handled by GLPainter.
}
