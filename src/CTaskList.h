/*
 * CTaskList.h
 *
 *  Created on: Feb 14, 2013
 *      Author: bkloppenborg
 */

#ifndef CTASKLIST_H_
#define CTASKLIST_H_

#include <vector>
#include <memory>
#include <valarray>
#include <map>

using namespace std;

class CTask;
typedef shared_ptr<CTask> CTaskPtr;

class CWorkerThread;
typedef shared_ptr<CWorkerThread> CWorkerPtr;

class CTaskList
{
protected:
	vector<CTaskPtr> mTasks;

public:
	CTaskList(CWorkerThread * WorkerThread);
	virtual ~CTaskList();

	void Export(string export_folder);

	unsigned int GetDataSize();
	vector<string> GetFileFilters();
	void GetResiduals(double * residuals, unsigned int size);
	void GetUncertainties(double * uncertainties, unsigned int size);

	void OpenData(string filename);

	void InitCL();
	void InitGL();
};

#endif /* CTASKLIST_H_ */
