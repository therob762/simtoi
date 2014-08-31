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
 
#ifndef CMAINGUI_H
#define CMAINGUI_H

#include "ui_guiMain.h"

#include <QtGui/QMainWindow>
#include <QThread>

#include <memory>
using namespace std;
class CGLWidget;
typedef shared_ptr<CGLWidget> CGLWidgetPtr;

class CWorkQueue;
typedef shared_ptr<CWorkQueue> CQueuePtr;

class CModel;
typedef shared_ptr<CModel> CModelPtr;

class CAnimator;

class guiMain : public QMainWindow, private Ui::guiMain
{
    Q_OBJECT

protected:
    vector<CGLWidgetPtr> mGLWidgetList;
    CQueuePtr mQueue;

public:
    guiMain(QWidget *parent = 0);
    virtual ~guiMain();

    void addModel(CModelPtr model);
    void replaceModel(CModelPtr old_model, CModelPtr new_model);

public slots:
	void on_actionNew_triggered(void);
	void on_btnAddModel_clicked(void);
	void on_btnEditModel_clicked(void);
	void on_btnRemoveModel_clicked(void);

signals:
	void startAnimation(double start_time, double time_step);
	void stopAnimation();

};

#endif // CMAINGUI_H
