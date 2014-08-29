/*
 * guiModel.cpp
 *
 *  Created on: Aug 21, 2014
 *      Author: bkloppenborg
 */

#include "guiModel.h"
#include "guiCommon.h"

#include "CModel.h"
#include "CModelFactory.h"
#include "CPositionFactory.h"
#include "CShaderFactory.h"
#include "CFeatureFactory.h"

guiModel::guiModel() {
	this->setupUi(this);

	auto models = CModelFactory::Instance();
	auto positions = CPositionFactory::Instance();
	auto shaders = CShaderFactory::Instance();
	auto features = CFeatureFactory::Instance();

	guiCommon::setOptions(cboModels, models.GetModelList());
	guiCommon::setOptions(cboPositions, positions.GetPositionList());
	guiCommon::setOptions(cboShaders, shaders.GetShaderList());
	guiCommon::setOptions(cboFeatures, features.GetFeatureList());
}

guiModel::guiModel(CModelPtr model)
{

}

guiModel::~guiModel() {
	// TODO Auto-generated destructor stub
}


void guiModel::on_btnFeatureAdd_clicked()
{
	QString feature_id = cboFeatures->currentText();
	listFeatures->addItem(feature_id);
}

void guiModel::on_btnFeatureRemove_clicked()
{
	qDeleteAll(listFeatures->selectedItems());
}
