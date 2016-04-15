//
// Created by inosphe on 2016. 4. 3..
//

#ifndef PROJECT_TESTSCENE_H
#define PROJECT_TESTSCENE_H

#include "DummyModel.h"
#include "IScene.h"

class TestScene : public IScene{
public:
	TestScene(Core::Application& app);
	void Init() override;
	void Update(int ms) override;
	void Render(Render::RenderingParameters& rp) override;

private:
	DummyModel model;
};


#endif //PROJECT_TESTSCENE_H
