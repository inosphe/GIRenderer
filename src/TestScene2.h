//
// Created by inosphe on 2016. 4. 6..
//

#ifndef PROJECT_TESTSCENE2_H
#define PROJECT_TESTSCENE2_H

#include "IScene.h"
#include "DummyModel2.h"

class TestScene2 : public IScene{
public:
	TestScene2(Core::Application& app);
	void Init() override;
	void Update(int ms) override;
	void Render(Render::ShaderParam& shader) override;

private:
	DummyModel2 model;
};


#endif //PROJECT_TESTSCENE2_H
