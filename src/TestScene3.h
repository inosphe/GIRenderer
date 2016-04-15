//
// Created by inosphe on 2016. 4. 8..
//

#ifndef PROJECT_TESTSCENE3_H
#define PROJECT_TESTSCENE3_H

#include "IScene.h"
#include <vector>
#include <memory>

namespace Render{
	class IModel;
}


class TestScene3 : public IScene{
public:
	TestScene3(Core::Application& app);
	virtual ~TestScene3();
	void Init() override;
	void Update(int ms) override;
	void Render(Render::RenderingParameters& rp) override;

	std::vector<std::shared_ptr<Render::IModel>> models;
};


#endif //PROJECT_TESTSCENE3_H
