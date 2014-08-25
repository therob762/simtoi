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
#include "guiNew.h"

#include "CGLWidget.h"

guiMain::guiMain(QWidget *parent_widget)
    : QMainWindow(parent_widget)
{
	// Init the UI
	this->setupUi(this);

	// Create one CGLWidget for rendering
	CGLWidgetPtr temp(new CGLWidget());
	temp->setID(0);
	mGLWidgetList.push_back(temp);

	// Replace the model widget with the CGLWidget we just created
	// Notice that we do NOT re-parent the widget as it is owned by mGLWidgetList!
	this->topRightLayout->addWidget(temp.get());

	temp.reset(new CGLWidget());
	temp->setID(mGLWidgetList.size());
	mGLWidgetList.push_back(temp);
}

guiMain::~guiMain()
{
	close();
}

void guiMain::on_actionNew_triggered(void)
{
	guiNew dialog;
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

	}

}
