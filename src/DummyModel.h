//
// Created by inosphe on 2016. 4. 2..
//

#ifndef PROJECT_DUMMYMODEL_H
#define PROJECT_DUMMYMODEL_H

#include "IModel.h"

class DummyModel : public Render::IModel{
public:
	DummyModel();
	void Init() override;
};


#endif //PROJECT_DUMMYMODEL_H
