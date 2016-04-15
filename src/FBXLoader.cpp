//
// Created by inosphe on 2016. 4. 1..
//

#include "FBXLoader.h"
#include "FBXScene.h"

namespace Resource {
	namespace FBX{

		FBXLoader::FBXLoader(){

		}

		FBXLoader::~FBXLoader() {
			Clear();
		}

		bool FBXLoader::Init() {
			m_pManager = FbxManager::Create();

			// Create an IOSettings object. IOSROOT is defined in Fbxiosettingspath.h.
			m_pSetting = FbxIOSettings::Create(m_pManager, IOSROOT );
			m_pManager->SetIOSettings(m_pSetting);

			return true;
		}

		void FBXLoader::Clear() {
			m_pManager->Destroy();
			m_pManager = nullptr;

			m_pSetting->Destroy();
			m_pSetting = nullptr;
		}

		void FBXLoader::InitSettings(){
#undef IOS_REF
#define IOS_REF (*m_pManager->GetIOSettings())
			// Set the import states. By default, the import states are always set to
			// true. The code below shows how to change these states.
			IOS_REF.SetBoolProp(IMP_FBX_MATERIAL,        true);
			IOS_REF.SetBoolProp(IMP_FBX_TEXTURE,         true);
			IOS_REF.SetBoolProp(IMP_FBX_LINK,            true);
			IOS_REF.SetBoolProp(IMP_FBX_SHAPE,           true);
			IOS_REF.SetBoolProp(IMP_FBX_GOBO,            true);
			IOS_REF.SetBoolProp(IMP_FBX_ANIMATION,       true);
			IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
#undef IOS_REF
		}

		std::shared_ptr<FBXScene> FBXLoader::CreateScene(const string& strSceneName){
			auto pScene = std::shared_ptr<IResource>(new FBXScene(this, strSceneName.c_str()));
			return std::static_pointer_cast<FBXScene>(pScene);
		}

		std::shared_ptr<IResource> FBXLoader::Load(const string &strFilepath) {
			int pos = strFilepath.find_last_of('/');
			if(pos == string::npos){
				pos = -1;
			}

			auto pScene = CreateScene(strFilepath.substr(pos+1));
			if(pScene->LoadScene(strFilepath)){
				return pScene;
			}
			else{
				throw std::runtime_error("invalid dir(" + strFilepath + ")");
			}
		}
	}
}