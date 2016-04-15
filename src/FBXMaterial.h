//
// Created by inosphe on 2016. 4. 12..
//

#ifndef PROJECT_FBXMATERIAL_H
#define PROJECT_FBXMATERIAL_H

#include "Material.h"

namespace Resource{
	class ResourceManager;

	namespace FBX{
		class FBXMaterial : public Render::Material{
		public:
			FBXMaterial(FbxNode* pNode, Resource::ResourceManager& rm);
			virtual ~FBXMaterial();
		private:
			bool InitFbx(FbxNode* pNode, Resource::ResourceManager& rm);
			void InitMaterial(const FbxSurfaceMaterial* pFbxMaterial, Resource::ResourceManager& rm);
		};

	}
}


#endif //PROJECT_FBXMATERIAL_H
