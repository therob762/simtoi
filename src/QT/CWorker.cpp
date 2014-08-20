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


}

CWorker::~CWorker() {
	// TODO Auto-generated destructor stub
}

void CWorker::start()
{
	mGLWidget->makeCurrent();
}

void CWorker::stop()
{
//    QMutexLocker locker(&mutex);
//    doRendering = false;
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
