/*
 * CGLWidget.h
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#ifndef CGLWIDGET_H_
#define CGLWIDGET_H_

#include <QThread>
#include <QGLWidget>

#include "CWorker.h"

class CGLWidget : public QGLWidget
{
private:
	CWorker mWorker;
	QThread mThread;

public:
	CGLWidget(QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);
	~CGLWidget();
	void startRendering();
	void stopRendering();

protected:
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);
	QSize sizeHint() const { return QSize(200, 200); }

};

#endif /* CGLWIDGET_H_ */
