/*
 * CTaskList.cpp
 *
 *  Created on: Feb 14, 2013
 *      Author: bkloppenborg
 */

#include "CTaskList.h"

#include <stdexcept>
#include <sstream>

#include "CTask.h"
#include "CTaskFactory.h"
#include "CWorkerThread.h"

using namespace std;

CTaskList::CTaskList(CWorkerThread * WorkerThread)
{
	CTaskFactory factory = CTaskFactory::Instance();

	mTasks.push_back(factory.CreateWorker("oi", WorkerThread));
}

CTaskList::~CTaskList()
{

}

void CTaskList::Export(string export_folder)
{
	for(auto task: mTasks)
		task->Export(export_folder);
}

/// \brief Builds a list of file filters for use in open file dialogs.
///
/// Builds a vector of strings containing the valid file description and
/// data types. Each entry in the returned vector will appear as
///		"description (*.extension ... *.extension)"
vector<string> CTaskList::GetFileFilters()
{
	vector<string> output;
	stringstream temp;

	string filetype = "";
	vector<string> extensions;
	for(auto task: mTasks)
	{
		// Clear out the stringstream.
		temp.str("");
		temp.clear();

		// Get the filetype and extensions:
		temp << task->GetDataDescription() << " (";
		extensions = task->GetExtensions();
		for(string extension: extensions)
		{
			temp << "*." << extension << " ";
		}

		temp << ")";

		output.push_back(temp.str());
	}

	return output;
}

void CTaskList::GetResiduals(double * residuals, unsigned int size)
{
	unsigned int n_data;
	unsigned int offset = 0;
	for(auto task: mTasks)
	{
		n_data = task->GetNData();

		// Get the residuals. Don't forget to re-calculate the size of the array:
		task->GetResiduals(residuals + offset, size - offset);

		offset += n_data;
	}
}

void CTaskList::GetUncertainties(double * uncertainties, unsigned int size)
{
	unsigned int n_data;
	unsigned int offset = 0;
	for(auto task: mTasks)
	{
		n_data = task->GetNData();

		// Get the residuals. Don't forget to re-calculate the size of the array:
		task->GetResiduals(uncertainties + offset, size - offset);

		offset += n_data;
	}
}

void CTaskList::OpenData(string filename)
{
	// TODO: Right now we identify the task object from the file extension.
	// There is probably a better way of doing this.

	// First get the extension in lower case:
	string extension = filename.substr(filename.find_last_of(".") + 1);
	std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

	// Now find which task handles the data type.
	for(auto task: mTasks)
	{
		for(auto datatype: task->GetExtensions())
		{
			if(extension == datatype)
			{
				task->OpenData(filename);
				return;
			}
		}
	}

	throw runtime_error("The data type " + extension + " is not supported.");
}

void CTaskList::InitCL()
{
	for(auto task: mTasks)
		task->InitCL();
}

void CTaskList::InitGL()
{
	for(auto task: mTasks)
		task->InitGL();
}
