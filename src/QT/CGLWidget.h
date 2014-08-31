/*
 * CGLWidget.h
 *
 *  Created on: Aug 20, 2014
 *      Author: bkloppenborg
 */

#ifndef CGLWIDGET_H_
#define CGLWIDGET_H_

#include <QGLWidget>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "CWorker.h"

class CWorkQueue;
typedef shared_ptr<CWorkQueue> CQueuePtr;

class CGLWidget : public QGLWidget
{
protected:
	CWorker mWorker;
	double mScale;
	CQueuePtr mQueue;
	glm::mat4 mView;

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
	void addModel(CModelPtr model);
	CModelPtr getModel(unsigned int model_index);
	void replaceModel(unsigned int model_index, CModelPtr new_model);
	void removeModel(unsigned int model_index);

public:
	glm::mat4 getView() { return mView; };
	void glDraw();	// override the QGLWidget::glDraw function


	double scale() { return mScale; };
	void setID(int id) { mWorker.setID(id); };
};

#endif /* CGLWIDGET_H_ */
