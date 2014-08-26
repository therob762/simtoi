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

using namespace std;

enum WorkCommand
{
	RENDER_TO_SCREEN
};

class CWorkItem
{
	WorkCommand command;
};

class CWorkQueue
{
private:
    queue<CWorkItem> mQueue;
    std::mutex mMutex;
    std::condition_variable mConditionVar;

public:

    void push(CWorkItem & item)
    {
    	std::unique_lock<std::mutex> lock(mMutex);
		mQueue.push(item);
		lock.unlock();
		mConditionVar.notify_one();
    }

    bool empty()
    {
    	std::unique_lock<std::mutex> lock(mMutex);
    	return mQueue.empty();
    }

    bool try_pop(CWorkItem & popped_item)
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

	void wait_and_pop(CWorkItem& popped_item)
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
