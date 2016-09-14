//
// Created by inosphe on 2016. 4. 1..
//

#ifndef PROJECT_FBXMODEL_H
#define PROJECT_FBXMODEL_H

#include "IModel.h"
#include "FBXScene.h"
#include <fbxsdk.h>
#include <memory>

namespace Resource {
	namespace FBX{
		class FBXScene;
	};
}

namespace Resource{
	class IResource;
	class ResourceManager;
}

namespace Render {
	class FBXNode;

	class FBXModel : public IModel{
	public:
		FBXModel();
		FBXModel(std::shared_ptr<Resource::IResource> pScene, Resource::ResourceManager& rm);
		virtual ~FBXModel();

		void UpdateForRender() override;
		void Render(Render::ShaderParam& shader) override;
		void Clear() override;

		void InitFBX(std::shared_ptr<Resource::FBX::FBXScene> pScene, Resource::ResourceManager& rm);

	protected:
		FBXNode* m_pRootNode = nullptr;
	};
}



#endif //PROJECT_FBXMODEL_H
