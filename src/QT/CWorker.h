/*
 * CWorker.h
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 *
 *  A worker for SIMTOI which is capable of OpenGL and OpenCL tasks.
 */

#ifndef CWORKER_H_
#define CWORKER_H_

#include <QObject>
#include <QSize>

class CGLWidget;

class CWorker : public QObject
{
     Q_OBJECT

private:
     CGLWidget * mGLWidget;

public:
	CWorker(CGLWidget * glWidget);
	virtual ~CWorker();

public:
    void stop();
    void resizeViewport(const QSize &size);

public slots:
    void start();

};

#endif /* CWORKER_H_ */
