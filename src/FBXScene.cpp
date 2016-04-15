//
// Created by inosphe on 2016. 4. 1..
//

#include <fbxsdk.h>
#include "FBXLoader.h"
#include "FBXScene.h"


namespace Resource {
	namespace FBX{

		FBXScene::FBXScene(FBXLoader* pLoader, const string& strSceneName)
				:IResource(RESOURCE_TYPE::FBX), m_pLoader(pLoader)
		{
			m_pFbxScene = FbxScene::Create(pLoader->GetManager(), strSceneName.c_str());
		}

		FBXScene::~FBXScene(){
			_Clear();
		}

		bool FBXScene::LoadScene(const string& strFilepath){
			FbxManager* pManager = m_pLoader->GetManager();
			const char* pFilename = strFilepath.c_str();

#undef IOS_REF
#define IOS_REF (*pManager->GetIOSettings())


			int lFileMajor, lFileMinor, lFileRevision;
			int lSDKMajor,  lSDKMinor,  lSDKRevision;
			//int lFileFormat = -1;
			int i, lAnimStackCount;
			bool lStatus;
			char lPassword[1024];

			// Get the file version number generate by the FBX SDK.
			FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

			// Create an importer.
			FbxImporter* lImporter = FbxImporter::Create(pManager,"");

			// Initialize the importer by providing a filename.
			const bool lImportStatus = lImporter->Initialize(strFilepath.c_str(), -1, pManager->GetIOSettings());
			lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

			if( !lImportStatus )
			{
				FbxString error = lImporter->GetStatus().GetErrorString();
				FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
				FBXSDK_printf("Error returned: %s\n\n", error.Buffer());

				if (lImporter->GetStatus().GetCode() == FbxStatus::eInvalidFileVersion)
				{
					FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
					FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
				}

				return false;
			}

			FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

			if (lImporter->IsFBX())
			{
				FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

				// From this point, it is possible to access animation stack information without
				// the expense of loading the entire file.

				FBXSDK_printf("Animation Stack Information\n");

				lAnimStackCount = lImporter->GetAnimStackCount();

				FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
				FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
				FBXSDK_printf("\n");

				for(i = 0; i < lAnimStackCount; i++)
				{
					FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

					FBXSDK_printf("    Animation Stack %d\n", i);
					FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
					FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

					// Change the value of the import name if the animation stack should be imported
					// under a different name.
					FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

					// Set the value of the import state to false if the animation stack should be not
					// be imported.
					FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
					FBXSDK_printf("\n");
				}


			}

			// Import the scene.
			lStatus = lImporter->Import(m_pFbxScene);

			if(lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
			{
				FBXSDK_printf("Please enter password: ");

				lPassword[0] = '\0';

				FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
				scanf("%s", lPassword);
				FBXSDK_CRT_SECURE_NO_WARNING_END

				FbxString lString(lPassword);

				IOS_REF.SetStringProp(IMP_FBX_PASSWORD,      lString);
				IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

				lStatus = lImporter->Import(m_pFbxScene);

				if(lStatus == false && lImporter->GetStatus().GetCode() == FbxStatus::ePasswordError)
				{
					FBXSDK_printf("\nPassword is wrong, import aborted.\n");
				}
			}

			// Destroy the importer.
			lImporter->Destroy();

#undef IOS_REF

			return lStatus;
		}

		FbxNode *FBXScene::GetRootNode() {
			return m_pFbxScene->GetRootNode();
		}

		void FBXScene::Clear() {
			_Clear();
		}

		void FBXScene::_Clear() {
			m_pFbxScene->Destroy(true);
		}
	}
}