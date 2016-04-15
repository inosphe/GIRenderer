//
// Created by inosphe on 2016. 4. 1..
//

#ifndef PROJECT_FBXLOADER_H
#define PROJECT_FBXLOADER_H

#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h>

#include <map>
#include "common_header.h"
#include "FBXScene.h"
#include "IResourceLoader.h"
#include "IResource.h"

namespace Resource {
	namespace FBX{
		class FBXScene;

		class FBXLoader : public IResourceLoader{
			friend class FBXScene;
		public:
			FBXLoader();
			virtual ~FBXLoader();

			bool Init();
			void Clear();

			std::shared_ptr<IResource> Load(const string& strFilepath) override;


		private:
			inline FbxManager* GetManager(){return m_pManager;}
			std::shared_ptr<FBXScene> CreateScene(const string& strSceneName);
			void InitSettings();

		private:
			FbxManager* m_pManager = nullptr;
			FbxIOSettings* m_pSetting = nullptr;
		};
	}
}
#endif //PROJECT_FBXLOADER_H
