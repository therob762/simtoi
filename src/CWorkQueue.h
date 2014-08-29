/*
 * CWorkQueue.h
 *
 *  Created on: Aug 25, 2014
 *      Author: bkloppenborg
 */

#ifndef CWORKQUEUE_H_
#define CWORKQUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

#include "WorkTypes.h"

using namespace std;

class CWorkQueue
{
private:
    queue<WorkPtr> mQueue;
    std::mutex mMutex;
    std::condition_variable mConditionVar;

public:

    void clear()
    {
    	std::unique_lock<std::mutex> lock(mMutex);
    	for(unsigned int i = 0; i < mQueue.size(); i++)
    		mQueue.pop();
    }

    void push(WorkPtr & item)
    {
    	std::unique_lock<std::mutex> lock(mMutex);
		mQueue.push(item);
		mConditionVar.notify_one();
    }

    bool empty()
    {
    	std::unique_lock<std::mutex> lock(mMutex);
    	return mQueue.empty();
    }

    bool try_pop(WorkPtr & popped_item)
	{
    	std::unique_lock<std::mutex> lock(mMutex);
		if(mQueue.empty())
		{
			return false;
		}

		popped_item = mQueue.front();
		mQueue.pop();
		return true;
	}

	void wait_and_pop(WorkPtr& popped_item)
	{
    	std::unique_lock<std::mutex> lock(mMutex);
		while(mQueue.empty())
		{
			mConditionVar.wait(lock);
		}

		popped_item = mQueue.front();
		mQueue.pop();
	}

};

#endif /* CWORKQUEUE_H_ */
