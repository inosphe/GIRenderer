//
// Created by inosphe on 2016. 4. 3..
//

#ifndef PROJECT_FBXMESH_H
#define PROJECT_FBXMESH_H

#include "IMesh.h"
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <fbxsdk.h>
#include <OpenGL/OpenGL.h>
#include "Vertex.h"

namespace Render {
	class RenderingParameters;

	class FBXMesh : public IMesh{
	public:
		FBXMesh(const FbxMesh* pMesh, Material* pMaterial, const glm::mat4& matOffset);
		virtual ~FBXMesh();
		void UpdateWorldTransform(const glm::mat4x4& matWorldTransform);
		virtual void Clear() override;

	private:
		void InitMesh(const FbxMesh* pMesh);
		void InitBuffer();
		void ClearTemporal();
		void _Clear();

	private:
		glm::mat4 m_matOffset;
		std::vector<Vertex> m_vecVertex;
		std::vector<GLuint> m_vecIndex;
	};
};

#endif //PROJECT_FBXMESH_H
