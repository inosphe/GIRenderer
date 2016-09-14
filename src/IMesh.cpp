//
// Created by inosphe on 2016. 4. 8..
//

#include <GL/glew.h>
#include "IMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <util/GLUtil.h>
#include "Material.h"

namespace Render{
	IMesh::IMesh()
	:m_matWorldTransform(1.0f)
	{
	}

	IMesh::IMesh(Material *pMaterial)
			:m_pMaterial(pMaterial)
	{

	}

	IMesh::~IMesh() {
		_Clear();
	}

	void IMesh::Render(Render::ShaderParam& shader){
		Bind(shader);
		Draw(shader);
	}

	void IMesh::Bind(Render::ShaderParam& shader) {
		shader.BindMat4x4const(SHADER_UNIFORM_ENUM::TRANSFORM, m_matWorldTransform);
		if(m_pMaterial)
			m_pMaterial->Bind(shader);

		BindVAO();
	//	BindVertex();
	//	BindIndex();

		GLUtil::CheckError();

	}

	void IMesh::Draw(Render::ShaderParam& shader) {
		if(GetIndexBuffer() == 0){
			glDrawArrays(GL_TRIANGLES, 0, m_nDrawCount);
		}
		else{
			glDrawElements(GL_TRIANGLES, m_nDrawCount, GL_UNSIGNED_INT, 0);
		}
	}

	void IMesh::GenerateVAO() {
		glGenVertexArrays(1, &m_iVAO);
	}

	GLuint IMesh::GetVAO() {
		return m_iVAO;
	}

	void IMesh::BindVAO() {
		glBindVertexArray(m_iVAO);
	}

	void IMesh::GenerateVertexBuffer() {
		glGenBuffers(1, &m_iVextexBuffer);
	}

	void IMesh::GenerateIndexBuffer() {
		glGenBuffers(1, &m_iIndexBuffer);
	}

	void IMesh::BindVertex() {
		if(m_iVextexBuffer)
			glBindBuffer(GL_ARRAY_BUFFER, m_iVextexBuffer);
	}

	void IMesh::BindIndex() {
		if(m_iIndexBuffer)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iIndexBuffer);
	}

	void IMesh::Clear() {
		_Clear();

		IRenderable::Clear();
	}

	void IMesh::_Clear() {
		if(m_iVAO)
			glDeleteVertexArrays(1, &m_iVAO);

		if(m_iVextexBuffer)
			glDeleteVertexArrays(1, &m_iVextexBuffer);

		if(m_iIndexBuffer)
			glDeleteVertexArrays(1, &m_iIndexBuffer);

		SAFE_DELETE(m_pMaterial);
	}

	void IMesh::SetDrawCount(int nSize) {
		m_nDrawCount = nSize;
	}
}
