/*
 * wMinimizer.h
 *
 *  Created on: Aug 26, 2014
 *      Author: bkloppenborg
 */

#ifndef WMINIMIZER_H_
#define WMINIMIZER_H_

#include <QWidget>
#include <QThread>
#include <memory>

#include "ui_wMinimizer.h"

using namespace std;

class CWorkQueue;
typedef shared_ptr<CWorkQueue> CQueuePtr;

class wMinimizer : public QWidget, public Ui::wMinimizer {
	Q_OBJECT

protected:
	CQueuePtr mQueue;
	void changeEvent ( QEvent * event );

public:
    wMinimizer(CQueuePtr queue, QWidget * parent = 0);
	virtual ~wMinimizer();
};

#endif /* WMINIMIZER_H_ */
