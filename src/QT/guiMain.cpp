/* 
 * Copyright (c) 2014 Brian Kloppenborg
 *
 * If you use this software as part of a scientific publication, please cite as:
 *
 * Kloppenborg, B.; Baron, F. (2012), "SIMTOI: The SImulation and Modeling 
 * Tool for Optical Interferometry" (Version X). 
 * Available from  <https://github.com/bkloppenborg/simtoi>.
 *
 * This file is part of the SImulation and Modeling Tool for Optical 
 * Interferometry (SIMTOI).
 * 
 * SIMTOI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License 
 * as published by the Free Software Foundation version 3.
 * 
 * SIMTOI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with SIMTOI.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "guiMain.h"

#include "guiRegion.h"
#include "guiModel.h"

#include "CGLWidget.h"
#include "CWorkQueue.h"
#include "wAnimation.h"
#include "wMinimizer.h"

#include <iostream>
using namespace std;

guiMain::guiMain(QWidget *parent_widget)
    : QMainWindow(parent_widget)
{
	// Init the UI
	this->setupUi(this);

	this->tabBottom->clear();

	// setup the queue
	mQueue.reset(new CWorkQueue());

	// Add custom widgets to the bottom tab widget
	wAnimation * widgetAnimation = new wAnimation(mQueue);
	this->tabBottom->addTab(widgetAnimation, QString("Animation"));
	wMinimizer * widgetMinimizer = new wMinimizer(mQueue);
	this->tabBottom->addTab(widgetMinimizer, QString("Minimizers"));

	// Create one CGLWidget for rendering
	CGLWidgetPtr temp(new CGLWidget(mQueue));
	temp->setID(0);
	mGLWidgetList.push_back(temp);

	// Replace the model widget with the CGLWidget we just created
	// Notice that we do NOT re-parent the widget as it is owned by mGLWidgetList!
	this->topRightLayout->addWidget(temp.get());

	// Add another thread
	temp.reset(new CGLWidget(mQueue));
	temp->setID(mGLWidgetList.size());
	mGLWidgetList.push_back(temp);

	// Add another thread
	temp.reset(new CGLWidget(mQueue));
	temp->setID(mGLWidgetList.size());
	mGLWidgetList.push_back(temp);
}

guiMain::~guiMain()
{
	close();
}

/// Opens up a dialog for creating a new model region
void guiMain::addModel(CModelPtr model)
{
	for(auto widget: mGLWidgetList)
	{
		widget->addModel(model);
	}
}

/// Opens up a dialog for creating a new model region
void guiMain::on_actionNew_triggered(void)
{
	guiRegion dialog;
	if(dialog.exec())
	{
		unsigned int width = dialog.spinWidth->value();
		unsigned int height = dialog.spinHeight->value();
		double scale = dialog.spinScale->value();

		for(auto widget: mGLWidgetList)
		{
			widget->initRegion(width, height, scale);
			widget->startWorking();
		}

		// enable buttons
		btnAddData->setEnabled(true);
		btnAddModel->setEnabled(true);
		btnEditData->setEnabled(true);
		btnEditModel->setEnabled(true);
		btnRemoveData->setEnabled(true);
		btnRemoveModel->setEnabled(true);
		// enable tabs
		for(unsigned int i = 0; i < tabBottom->count(); i++)
			tabBottom->setTabEnabled(i, true);
	}
}

/// Opens up a dialog for creating a new model
void guiMain::on_btnAddModel_clicked(void)
{
	guiModel dialog;
	if(dialog.exec())
	{
		CModelPtr model = dialog.getModel();
		addModel(model);
	}
}

/// Opens up a dialog for creating a new model
void guiMain::on_btnEditModel_clicked(void)
{
	unsigned int old_model_index = 0;
	CModelPtr old_model = mGLWidgetList[0]->getModel(old_model_index);

	guiModel dialog(old_model);
	if(dialog.exec())
	{
		CModelPtr new_model = dialog.getModel();

		for(auto widget: mGLWidgetList)
		{
			widget->replaceModel(old_model_index, new_model);
		}
	}
}
