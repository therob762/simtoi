/*
 * CGLWidget.h
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#ifndef CGLWIDGET_H_
#define CGLWIDGET_H_

#include <QGLWidget>

#include "CWorker.h"

class CWorkQueue;
typedef shared_ptr<CWorkQueue> CQueuePtr;

class CGLWidget : public QGLWidget
{
protected:
	CWorker mWorker;
	double mScale;
	CQueuePtr mQueue;

public:
	CGLWidget(CQueuePtr queue, QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);
	~CGLWidget();
	void startWorking();
	void stopWorking();

	void initRegion(unsigned int width, unsigned int height, double scale);

protected:
	void paintGL();
	void resizeGL (int width, int height);
	void initializeGL();

public:
	void setID(int id) { mWorker.setID(id); };

public:
	double scale() { return mScale; };

public:
	void glDraw();	// override the QGLWidget::glDraw function
};

#endif /* CGLWIDGET_H_ */
