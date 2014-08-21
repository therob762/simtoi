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

class CGLWidget : public QGLWidget
{
private:
	CWorker mWorker;

	unsigned int mImageWidth;
	unsigned int mImageHeight;
	double mImageScale;

public:
	CGLWidget(QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);
	~CGLWidget();
	void startRendering();
	void stopRendering();

	void initRegion(unsigned int width, unsigned int height, double scale);

protected:
	void paintGL();
	void resizeGL (int width, int height);
	void initializeGL();

public:
	void glDraw();	// override the QGLWidget::glDraw function
};

#endif /* CGLWIDGET_H_ */
