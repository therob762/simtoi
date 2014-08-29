/*
 * wAnimation.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: bkloppenborg
 */

#include "wMinimizer.h"
#include "CMinimizerFactory.h"

class CWorkQueue;
typedef shared_ptr<CWorkQueue> CQueuePtr;

wMinimizer::wMinimizer(CQueuePtr queue, QWidget * parent)
	: QWidget(parent), mQueue(queue)
{
	this->setupUi(this);

	setEnabled(false);

}

wMinimizer::~wMinimizer()
{
//	mAnimator.stop();
//	mAnimator.wait();
}

void wMinimizer::changeEvent ( QEvent * event )
{
	if(event->type() == QEvent::EnabledChange)
	{
		bool is_enabled = isEnabled();
		btnMinimizerStartStop->setEnabled(is_enabled);
		cboMinimizers->setEnabled(is_enabled);
		textSaveFolder->setEnabled(is_enabled);

	}
}

