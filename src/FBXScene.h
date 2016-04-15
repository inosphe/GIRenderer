//
// Created by inosphe on 2016. 4. 1..
//

#ifndef PROJECT_FBXSCENE_H
#define PROJECT_FBXSCENE_H

#include "common_header.h"
#include <fbxsdk.h>
#include "IResource.h"

namespace Resource {
	namespace FBX{
		class FBXLoader;

		class FBXScene : public IResource{
		public:
			FBXScene(FBXLoader* pLoader, const string& strSceneName);
			virtual ~FBXScene();
			bool LoadScene(const string& strFilepath);
			FbxNode* GetRootNode();

			void Clear();

		private:
			void _Clear();

		private:
			FBXLoader* m_pLoader = nullptr;
			FbxScene* m_pFbxScene = nullptr;
		};		
	}
}


#endif //PROJECT_FBXSCENE_H
