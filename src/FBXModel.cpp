//
// Created by inosphe on 2016. 4. 1..
//

#include "FBXModel.h"
#include "FBXScene.h"
#include "FBXNode.h"

Render::FBXModel::FBXModel() {

}

Render::FBXModel::FBXModel(std::shared_ptr<Resource::IResource> pScene, Resource::ResourceManager& rm) {
	if(pScene->m_type != RESOURCE_TYPE::FBX)
		throw std::runtime_error("invalid resource type");

	InitFBX(std::static_pointer_cast<Resource::FBX::FBXScene>(pScene), rm);
}


void Render::FBXModel::InitFBX(std::shared_ptr<Resource::FBX::FBXScene> pScene, Resource::ResourceManager &rm) {
	m_pRootNode = new FBXNode(pScene->GetRootNode(), rm);
}


void Render::FBXModel::Render(Render::ShaderParam& shader) {
	if(m_pRootNode)
		m_pRootNode->Render(shader);
}

void Render::FBXModel::UpdateForRender() {
	if(m_pRootNode){
		m_pRootNode->UpdateWorldTransform(GetTransform());
		m_pRootNode->UpdateForRender();
	}
}

Render::FBXModel::~FBXModel() {

}

void Render::FBXModel::Clear() {

}
