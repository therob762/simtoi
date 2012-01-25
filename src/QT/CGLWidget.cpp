#include "CGLWidget.h"

CGLWidget::CGLWidget(QWidget *parent, string shader_source_dir, string cl_kernel_dir)
    : QGLWidget(parent), mGLT(this, shader_source_dir, cl_kernel_dir)
{ 
    setAutoBufferSwap(false);
    this->doneCurrent();
}

CGLWidget::~CGLWidget()
{
	stopRendering();
}

void CGLWidget::AddModel(eModels model)
{
	mGLT.AddModel(model);
}

void CGLWidget::EnqueueOperation(CL_GLT_Operations op)
{
	mGLT.EnqueueOperation(op);
}

void CGLWidget::closeEvent(QCloseEvent *evt)
{
    stopRendering();
    QGLWidget::closeEvent(evt);
}
void CGLWidget::paintEvent(QPaintEvent *)
{
    // Handled by the GLThread.
}
void CGLWidget::resizeEvent(QResizeEvent *evt)
{
    mGLT.resizeViewport(evt->size());
}


void CGLWidget::startRendering()
{
    mGLT.start();
}

void CGLWidget::stopRendering()
{
    mGLT.stop();
    mGLT.wait();
}

void CGLWidget::SetParameters(float * params, int n_params)
{
	mGLT.SetParameters(params, n_params);
}

void CGLWidget::SetScale(double scale)
{
	mGLT.SetScale(scale);
}

void CGLWidget::SetShader(int model_id, eGLShaders shader)
{
	mGLT.SetShader(model_id, shader);
}

void CGLWidget::SetPositionType(int model_id, ePositionTypes pos_type)
{
	mGLT.SetPositionType(model_id, pos_type);
}

