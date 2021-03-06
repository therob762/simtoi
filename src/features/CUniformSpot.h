/*
 * CUniformSpot.h
 *
 *  Created on: Apr 23, 2014
 *      Author: bkloppenborg
 */

#ifndef CUNIFORMSPOT_H_
#define CUNIFORMSPOT_H_

#include "CFeature.h"

class CUniformSpot: public CFeature
{

public:
	CUniformSpot();
	virtual ~CUniformSpot();

	static shared_ptr<CFeature> Create()
	{
		return shared_ptr<CFeature>(new CUniformSpot());
	}

	void apply(CModel * model);
};

#endif /* CUNIFORMSPOT_H_ */
