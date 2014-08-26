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

}

wMinimizer::~wMinimizer()
{
//	mAnimator.stop();
//	mAnimator.wait();
}


