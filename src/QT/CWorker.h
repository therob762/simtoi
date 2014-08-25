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
#include <QThread>
#include <QGLFramebufferObject>
#include <memory>

using namespace std;


class CGLWidget;

class CWorker : public QThread
{
     Q_OBJECT

protected:
     CGLWidget * mGLWidget;
     bool mDoWork;
     int mID;

     unique_ptr<QGLFramebufferObject> mFBO_render;

protected:
     void run();

public:
	CWorker(CGLWidget * glWidget);
	virtual ~CWorker();

public:

	void setID(int id) { mID = id; };

    void stop();
	void resizeGL (int width, int height);

	void initializeGL();
};

#endif /* CWORKER_H_ */
