//
// Created by inosphe on 2016. 4. 8..
//

#ifndef PROJECT_IMESH_H
#define PROJECT_IMESH_H

#include <GLFW/glfw3.h>
#include "IRenderable.h"
#include <glm/mat4x4.hpp>

namespace Render{
	class Material;

	class IMesh : public IRenderable {
	public:
		IMesh();
		IMesh(Material* pMaterial);
		virtual ~IMesh();
		virtual void Init(){}
		virtual void Clear() override;
		virtual void Render(Render::ShaderParam& shader) override;

		void GenerateVAO();
		GLuint GetVAO();
		void BindVAO();

		void GenerateVertexBuffer();
		void GenerateIndexBuffer();
		inline GLuint GetVertexBuffer(){return m_iVextexBuffer;}
		inline GLuint GetIndexBuffer(){return m_iIndexBuffer;}
		void BindVertex();
		void BindIndex();

		void SetDrawCount(int nSize);

	protected:
		virtual void Bind(Render::ShaderParam& shader);
		virtual void Draw(Render::ShaderParam& shader);

		glm::mat4x4 m_matWorldTransform;
		Material* m_pMaterial = nullptr;

	private:
		void _Clear();

	private:
		GLuint m_iVAO = 0;
		GLuint m_iVextexBuffer = 0;
		GLuint m_iIndexBuffer = 0;
		int m_nDrawCount = 0;
	};
}



#endif //PROJECT_IMESH_H
