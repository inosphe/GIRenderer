//
// Created by inosphe on 2016. 3. 28..
//

#include "ResourceManager.h"
#include <fstream>
#include <ios>
#include "Logger.h"
#include <fbxsdk.h>
#include <fbxsdk/fileio/fbxiosettings.h>
#include "FBXLoader.h"
#include "FBXModel.h"
#include "Image.h"

#include "RESOURCE_PATH.h"
#include "stb_image.h"

namespace Resource{
	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager() {
		Clear();
	}

	bool ResourceManager::Init() {
		m_pFBXLoader = new FBX::FBXLoader();
		m_pFBXLoader->Init();

		return true;
	}

	void ResourceManager::Clear() {
		m_mapResourceCached.clear();
		SAFE_DELETE(m_pFBXLoader);
	}

	std::vector<std::shared_ptr<IResource>> ResourceManager::LoadFBXFromConfig(const string& strConfig) {
		std::ifstream fileStream(RESOURCE_PATH(strConfig));
		fileStream.open(strConfig);
		if(!fileStream.is_open()){
			throw "file not opened.";
		}
		string strResourceName;

		std::vector<std::shared_ptr<IResource>> ret;

		while(std::getline(fileStream, strResourceName)){
			ret.push_back(Load<RESOURCE_TYPE::FBX>(strResourceName, true));
		}
		return ret;
	}

	std::shared_ptr<Resource::Image> ResourceManager::LoadImageFromFile(string strFilepath) {
		int w;
		int h;
		int comp;

//		size_t pos = 0;
//		while((pos = strFilepath.find('\\', pos))!=string::npos){
//			strFilepath.replace(pos, 1, "/");
//		}
		std::replace(strFilepath.begin(), strFilepath.end(), '\\', '/');

		BYTE* image = stbi_load(strFilepath.c_str(), &w, &h, &comp, STBI_rgb_alpha);
		if(image)
			return std::shared_ptr<Resource::Image>(new Resource::Image(image, w, h, comp));
		else
			return nullptr;
	}

	std::shared_ptr<IResource> ResourceManager::GetResource(const string &strFilepath) {
		auto itr = m_mapResourceCached.find(strFilepath);
		if(itr != m_mapResourceCached.end()){
			return itr->second;
		}
		return std::shared_ptr<IResource>(nullptr);
	}


	template <>
	std::shared_ptr<Resource::IResource> ResourceManager::Load<RESOURCE_TYPE::FBX>(const string& strFilepath, bool bStoreCache){
		auto itr = m_mapResourceCached.find(strFilepath);
		if(itr != m_mapResourceCached.end()){
			return itr->second;
		}

		auto pResource = m_pFBXLoader->Load(strFilepath);

		if(bStoreCache){
			auto ret = m_mapResourceCached.insert(std::make_pair(strFilepath, pResource));
			if(!ret.second){
//					throw std::runtime_error("inserting cache failed.");
			}
		}

		return pResource;
	}
}
