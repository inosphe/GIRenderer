//
// Created by inosphe on 2016. 4. 3..
//

#include <util/FBXUtil.h>
#include "FBXMesh.h"
#include <iostream>

namespace Render {

	FBXMesh::FBXMesh(const FbxMesh *pMesh, Material* pMaterial, const glm::mat4 &matOffset)
	:IMesh(pMaterial), m_matOffset(matOffset)
	{
		InitMesh(pMesh);
		InitBuffer();
		ClearTemporal();
	}

	FBXMesh::~FBXMesh() {
		_Clear();
	}

	void FBXMesh::InitMesh(const FbxMesh *pMesh) {
		const int lVertexCount = pMesh->GetControlPointsCount();

		// May not have any vertex data
		if(lVertexCount==0) return;

		auto vertices = pMesh->GetControlPoints();

		const int lPolygonCount = pMesh->GetPolygonCount();
		for(int lPolygonIndex =0; lPolygonIndex<lPolygonCount; lPolygonIndex++)
		{
			int lVerticesCount = pMesh->GetPolygonSize(lPolygonIndex);
//			if(lVerticesCount>3)
//				lVerticesCount = 3;
//			std::cout << lVerticesCount << std::endl;
			for(int lVerticeIndex =0; lVerticeIndex<lVerticesCount; lVerticeIndex++)
			{
				auto iVertexId = m_vecVertex.size();
				Vertex vert;
				vert.pos = FBXUtil::ToGLU(vertices[pMesh->GetPolygonVertex(lPolygonIndex, lVerticeIndex)]);
				FbxVector4 norm;
				pMesh->GetPolygonVertexNormal(lPolygonIndex, lVerticeIndex, norm);


				FbxStringList UVSetNameList;
				// Get the name of each set of UV coords
				pMesh->GetUVSetNames( UVSetNameList );
				if(UVSetNameList.GetCount()){
					FbxVector2 uv;
					bool unmapped = true;
					pMesh->GetPolygonVertexUV(lPolygonIndex, lVerticeIndex, UVSetNameList.GetItemAt(0)->mString.Buffer(), uv, unmapped);
					if(!unmapped)
						vert.uv = FBXUtil::ToGLU(uv);
				}

				auto _norm = FBXUtil::ToGLU(norm);
				vert.norm = glm::vec3(_norm.x, _norm.y, _norm.z);
				m_vecVertex.push_back(vert);

				if(lVerticeIndex==3){
					m_vecIndex.push_back(iVertexId-3);
					m_vecIndex.push_back(iVertexId-1);
				}
				m_vecIndex.push_back(iVertexId);
			}
		}

	}

	void FBXMesh::InitBuffer() {
		if(m_vecVertex.size()<=0)
			return;

		GenerateVAO();
		BindVAO();

		GenerateVertexBuffer();
		BindVertex();

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_vecVertex.size(), &m_vecVertex[0], GL_STATIC_DRAW);
		int sizeofVertex = sizeof(Vertex);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, norm));

		GenerateIndexBuffer();
		BindIndex();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_vecIndex.size(), &m_vecIndex[0], GL_STATIC_DRAW);
		SetDrawCount(m_vecIndex.size());
	}

	void FBXMesh::UpdateWorldTransform(const glm::mat4x4 &matWorldTransform) {
		m_matWorldTransform = m_matOffset*matWorldTransform;
	}

	void FBXMesh::ClearTemporal() {
		m_vecIndex.clear();
		m_vecVertex.clear();
	}

	void FBXMesh::Clear() {
		_Clear();
		IMesh::Clear();
	}

	void FBXMesh::_Clear() {

	}
}