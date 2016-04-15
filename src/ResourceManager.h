//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_RESOURCEMANAGER_H
#define PROJECT_RESOURCEMANAGER_H

#include "common_header.h"
#include "Singleton.h"
#include "ResourceType.h"
#include <map>
#include <vector>
#include "FBXLoader.h"
#include "IModel.h"

namespace Render{
	class IModel;
}

namespace Resource{
	class Image;
	class IResource;


	class ResourceManager{

	public:
		ResourceManager();
		~ResourceManager();
		bool Init();
		void Clear();

		std::vector<std::shared_ptr<IResource>> LoadFBXFromConfig(const string& strConfig);
		template <int T>
		std::shared_ptr<Resource::IResource> Load(const string& strFilepath, bool bStoreCache){
			throw std::runtime_error("not implemented.");
		}
		std::shared_ptr<Resource::Image> LoadImageFromFile(string strFilepath);
		std::shared_ptr<IResource> GetResource(const string& strFilepath);

	private:
		Render::IModel* LoadFBX(const string& strFilepath);
		Render::IModel* GetModel(const string& strFilepath);

	private:
		FBX::FBXLoader* m_pFBXLoader = nullptr;
		std::map<string, std::shared_ptr<IResource>> m_mapResourceCached;

	};

	template <>
	std::shared_ptr<Resource::IResource> ResourceManager::Load<RESOURCE_TYPE::FBX>(const string& strFilepath, bool bStoreCache);
}


#endif //PROJECT_RESOURCEMANAGER_H
