//
// Created by inosphe on 2016. 4. 3..
//

#include "common_header.h"
#include "FBXNode.h"
#include <fbxsdk.h>
#include <cassert>
#include "FBXMesh.h"
#include "util/FBXUtil.h"
#include "FBXMesh.h"
#include "FBXMaterial.h"

Render::FBXNode::FBXNode(FbxNode *pNode, Resource::ResourceManager& rm)
:IModel()
{
	InitFBXNode(pNode, rm);
}


void Render::FBXNode::InitFBXNode(FbxNode *pNode, Resource::ResourceManager& rm) {

//  For now grab the global transform of the node from its time at 0
//	FbxAMatrix lGlobalPosition = pNode->EvaluateGlobalTransform(0);
//	m_vWorldTransform = FBXUtil::ToGLU(lGlobalPosition);

	FbxVector4 lLocalPosition = pNode->EvaluateLocalTranslation(0);
	FbxVector4 lLocalScale = pNode->EvaluateLocalScaling(0);
	FbxVector4 lLocalRotation = pNode->EvaluateLocalRotation(0);
	m_vPosition = FBXUtil::ToGLU(lLocalPosition);
	m_vScale = FBXUtil::ToGLU(lLocalScale);
	m_qRotation = glm::quat(glm::vec3(lLocalRotation[0], lLocalRotation[1], lLocalRotation[2]));

	// Find out what type of node this is
	FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();

	if(lNodeAttribute)
	{
		int lMaterialCount = pNode->GetMaterialCount();
		Material* pMaterial = nullptr;
		if(lMaterialCount){
			pMaterial = new Resource::FBX::FBXMaterial(pNode, rm);
		}

		// Draw the actual node mesh data if it is a mesh this time
		// (You could use this like the sample where they draw other nodes like cameras)
		if(lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			InitMesh(pNode, pMaterial);
		}
	}

	// Now check if this node has any children attached
	const int lChildCount = pNode->GetChildCount();
	for(int lChildIndex=0; lChildIndex < lChildCount; ++lChildIndex)
	{
		m_vecChildren.push_back(new FBXNode(pNode->GetChild(lChildIndex), rm));
	}
}

void Render::FBXNode::InitMesh(FbxNode *pNode, Material* pMaterial) {
	assert(!m_pMesh);


	// Get the translation
	const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	// Get the rotation
	const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
	// Get the scale
	const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);

	m_pMesh = new FBXMesh(pNode->GetMesh(), pMaterial, FBXUtil::ToGLU(FbxAMatrix(lT, lR, lS)));
}

Render::FBXNode::~FBXNode() {
	_Clear();
}

void Render::FBXNode::Clear() {
	_Clear();
	IModel::Clear();
}

void Render::FBXNode::UpdateWorldTransform(const glm::mat4x4 &matWorldTransform) {
	glm::mat4x4 matTransform = GetTransform();
	m_matWorldTransform = matTransform*matWorldTransform;

	for(auto node : m_vecChildren){
		node->UpdateWorldTransform(m_matWorldTransform);
	}

	if(m_pMesh){
		m_pMesh->UpdateWorldTransform(m_matWorldTransform);
	}
}

void Render::FBXNode::Render(Render::ShaderParam& shader) {
	if(m_pMesh){
		m_pMesh->Render(shader);
	}

	for(auto node : m_vecChildren){
		node->Render(shader);
	}
}

void Render::FBXNode::_Clear() {
	SAFE_DELETE(m_pMesh);

	for(auto& child : m_vecChildren){
		SAFE_DELETE(child);
	}
}
