/*
 * guiNew.h
 *
 *  Created on: Aug 21, 2014
 *      Author: bkloppenborg
 */

#ifndef GUIREGION_H_
#define GUIREGION_H_

#include "ui_guiNew.h"

class guiRegion : public QDialog, public Ui::guiNew {
public:
	guiRegion();
	virtual ~guiRegion();
};

#endif /* GUIREGION_H_ */
