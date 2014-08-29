/*
 * CWorkItems.h
 *
 *  Created on: Aug 26, 2014
 *      Author: bkloppenborg
 *
 *  Header file containing all (?) possible work items for SIMTOI.
 */

#ifndef CWORKITEMS_H_
#define CWORKITEMS_H_

class WorkItem;
typedef shared_ptr<WorkItem> WorkPtr;

enum WorkType
{
	RENDER_TO_SCREEN,	/// No payload
	RENDER_AT_TIME,		/// Payload = 1 double
	TEST_RENDERING,		/// No payload
	EXIT,
	NONE
};

class WorkItem
{
private:
	WorkType mWorkType;

public:

	WorkItem()
	{
		mWorkType = NONE;
	}

	WorkItem(WorkType command)
	{
		mWorkType = command;
	}

	virtual ~WorkItem()
	{

	}

	WorkType getType() { return mWorkType; };
};

class RenderAtTime : public WorkItem
{
public:
	double time;

	RenderAtTime(double time)
		: WorkItem(RENDER_AT_TIME)
	{
		this-> time = time;
	}

	virtual ~RenderAtTime()
	{

	}
};

#endif /* CWORKITEMS_H_ */
