/*
 * CAnimator.cpp
 *
 *  Created on: Dec 4, 2013
 *      Author: bkloppenborg
 */

#include <QThread>
#include <iostream>
using namespace std;

#include "CAnimator.h"
#include "CWorkQueue.h"

CAnimator::CAnimator(CQueuePtr queue, QObject * parent)
	: QThread(parent)
{
	mQueue = queue;
	mRun = false;
	mTime = 0;
	mStep = 0;
}

CAnimator::~CAnimator()
{
	stop();
	wait();
}

void CAnimator::run()
{
	mRun = true;

	CWorkItem op(RENDER_TO_SCREEN);

	while(mRun)
	{
		mQueue->push(op);

		this->msleep(50);
		mTime += mStep;

		emit(update_time(mTime));
	}
}

void CAnimator::setTime(double time)
{
	mTime = time;
}

void CAnimator::setStep(double step)
{
	mStep = step;
}

void CAnimator::stop()
{
	mRun = false;
}

