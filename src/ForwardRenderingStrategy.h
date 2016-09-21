//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_FORWARDRENDERINGSTRATEGY_H
#define PROJECT_FORWARDRENDERINGSTRATEGY_H


#include "IRenderingStrategy.h"

namespace Render{
	class ForwardRenderingStrategy : public IRenderingStrategy{
	public:
		ForwardRenderingStrategy();
		virtual ~ForwardRenderingStrategy();

		void Init() override;

		virtual void Render(const Camera& camera, const std::vector<GameObject::PTR>& vecLights, std::function<void()> fRenderModels) override;

	private:

	};
}

#endif //PROJECT_FORWARDRENDERINGSTRATEGY_H
