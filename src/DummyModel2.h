//
// Created by inosphe on 2016. 4. 6..
//

#ifndef PROJECT_DUMMYMODEL2_H
#define PROJECT_DUMMYMODEL2_H

#include "IModel.h"

class DummyModel2 : public Render::IModel{
public:
	void Init() override;
	void Update(int ms) override;
};


#endif //PROJECT_DUMMYMODEL2_H
