//
// Created by inosphe on 2016. 4. 12..
//

#include "FBXMaterial.h"
#include "Logger.h"
#include "ResourceManager.h"

Resource::FBX::FBXMaterial::FBXMaterial(FbxNode *pNode, Resource::ResourceManager& rm) {
	InitFbx(pNode, rm);
}

bool Resource::FBX::FBXMaterial::InitFbx(FbxNode *pNode, Resource::ResourceManager& rm) {
	int lMaterialCount = pNode->GetMaterialCount();
	for (int lCount = 0; lCount < lMaterialCount; lCount++) {
		FbxSurfaceMaterial *lMaterial = pNode->GetMaterial(lCount);
		InitMaterial(lMaterial, rm);
	}

	return true;
}

Resource::FBX::FBXMaterial::~FBXMaterial() {

}

void Resource::FBX::FBXMaterial::InitMaterial(const FbxSurfaceMaterial *pFbxMaterial, Resource::ResourceManager& rm) {
	Logger::Debug(pFbxMaterial->GetName());

	Render::MaterialElement& material = AddElement();

	const FbxImplementation *lImplementation = pFbxMaterial->GetDefaultImplementation();
		FbxPropertyT<FbxDouble3> lKFbxDouble3;
		FbxPropertyT<FbxDouble> lKFbxDouble1;
		FbxColor theColor;

	if(lImplementation){
		const FbxBindingTable *lTable = lImplementation->GetRootTable();
		size_t lEntryNum = lTable->GetEntryCount();

		for (int i = 0; i < (int) lEntryNum; ++i) {
			const FbxBindingTableEntry &lEntry = lTable->GetEntry(i);
			const char *lEntrySrcType = lEntry.GetEntryType(true);
			FbxProperty lFbxProp;


			FbxString lTest = lEntry.GetSource();
			FBXSDK_printf("            Entry: %s\n", lTest.Buffer());


			if (strcmp(FbxPropertyEntryView::sEntryType, lEntrySrcType) == 0) {
				lFbxProp = pFbxMaterial->FindPropertyHierarchical(lEntry.GetSource());
				if (!lFbxProp.IsValid()) {
					lFbxProp = pFbxMaterial->RootProperty.FindHierarchical(lEntry.GetSource());
				}


			}
			else if (strcmp(FbxConstantEntryView::sEntryType, lEntrySrcType) == 0) {
				lFbxProp = lImplementation->GetConstants().FindHierarchical(lEntry.GetSource());
			}
		}
	}
	else if (pFbxMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
	{
		// We found a Phong material.  Display its properties.

		// Display the Ambient Color
		lKFbxDouble3 =((FbxSurfacePhong *) pFbxMaterial)->Ambient;
		theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

		// Display the Diffuse Color
		lKFbxDouble3 =((FbxSurfacePhong *) pFbxMaterial)->Diffuse;
		theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

		// Display the Specular Color (unique to Phong materials)
		lKFbxDouble3 =((FbxSurfacePhong *) pFbxMaterial)->Specular;
		theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

		// Display the Emissive Color
		lKFbxDouble3 =((FbxSurfacePhong *) pFbxMaterial)->Emissive;
		theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

		//Opacity is Transparency factor now
		lKFbxDouble1 =((FbxSurfacePhong *) pFbxMaterial)->TransparencyFactor;

		// Display the Shininess
		lKFbxDouble1 =((FbxSurfacePhong *) pFbxMaterial)->Shininess;

		// Display the Reflectivity
		lKFbxDouble1 =((FbxSurfacePhong *) pFbxMaterial)->ReflectionFactor;
	}
	else if(pFbxMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId) )
	{
		// We found a Lambert material. Display its properties.
		// Display the Ambient Color
		lKFbxDouble3=((FbxSurfaceLambert *)pFbxMaterial)->Ambient;
		theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

		// Display the Diffuse Color
		lKFbxDouble3 =((FbxSurfaceLambert *)pFbxMaterial)->Diffuse;
		theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

		// Display the Emissive
		lKFbxDouble3 =((FbxSurfaceLambert *)pFbxMaterial)->Emissive;
		theColor.Set(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

		// Display the Opacity
		lKFbxDouble1 =((FbxSurfaceLambert *)pFbxMaterial)->TransparencyFactor;
	}
	else
		Logger::Debug("Unknown type of Material");



	FbxProperty prop = pFbxMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
	// Check if it's layeredtextures
	int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();
	for (int j = 0; j < layeredTextureCount; j++)
	{
		FbxLayeredTexture* layered_texture = FbxCast<FbxLayeredTexture>(prop.GetSrcObject<FbxLayeredTexture>(j));
		int lcount = layered_texture->GetSrcObjectCount<FbxFileTexture>();

		for (int k = 0; k < lcount; k++)
		{
			FbxFileTexture* texture = FbxCast<FbxFileTexture>(layered_texture->GetSrcObject<FbxFileTexture>(k));
			// Then, you can get all the properties of the texture, include its name
			const char* textureName = texture->GetFileName();

			material.AddTexture(rm.LoadImageFromFile(textureName));
		}
	}

	int textureCount = prop.GetSrcObjectCount<FbxFileTexture>();
	for(int i=0; i<textureCount; ++i){
		FbxFileTexture* texture = FbxCast<FbxFileTexture>(prop.GetSrcObject<FbxFileTexture>(i));
		const char* textureName = texture->GetFileName();

		material.AddTexture(rm.LoadImageFromFile(textureName));
	}

	FbxPropertyT<FbxString> lString;
	lString = pFbxMaterial->ShadingModel;
}

