/*
 * guiCommon.h
 *
 *  Created on: Aug 29, 2014
 *      Author: bkloppenborg
 */

#ifndef GUICOMMON_H_
#define GUICOMMON_H_

#include <QComboBox>
#include <vector>

using namespace std;

namespace guiCommon
{
/// Populates a QComboBox with string stored in options
void setOptions(QComboBox * comboBox, vector<string> options)
{
	QString tmp_str;
	for(auto str : options)
	{
		tmp_str = QString::fromStdString(str);
		comboBox->addItem(tmp_str);
	}
}

}	// namespace guiCommon



#endif /* GUICOMMON_H_ */
