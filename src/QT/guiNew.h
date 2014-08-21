/*
 * guiNew.h
 *
 *  Created on: Aug 21, 2014
 *      Author: bkloppenborg
 */

#ifndef GUINEW_H_
#define GUINEW_H_

#include "ui_guiNew.h"

class guiNew : public QDialog, public Ui::guiNew {
public:
	guiNew();
	virtual ~guiNew();
};

#endif /* GUINEW_H_ */
