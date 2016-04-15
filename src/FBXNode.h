//
// Created by inosphe on 2016. 4. 3..
//

#ifndef PROJECT_FBXNODE_H
#define PROJECT_FBXNODE_H

#include "IModel.h"
#include <fbxsdk.h>
#include "glm/mat4x4.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/quaternion.hpp"
#include <vector>

namespace Resource{
	class ResourceManager;
}

namespace Render {
	class FBXMesh;

	class FBXNode : public IModel{
	public:
		FBXNode(FbxNode* pNode, Resource::ResourceManager& rm);
		virtual ~FBXNode();
		void Clear();
		void UpdateWorldTransform(const glm::mat4x4& matWorldTransform);
		void Render(Render::RenderingParameters& rp) override;

	private:
		void InitFBXNode(FbxNode* pNode, Resource::ResourceManager& rm);
		void InitMesh(FbxNode *pNode, Material* pMaterial);
		void _Clear();

	private:
		FBXMesh* m_pMesh = nullptr;
		std::vector<FBXNode*> m_vecChildren;
	};
}



#endif //PROJECT_FBXNODE_H
