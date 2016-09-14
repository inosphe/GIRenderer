//
// Created by inosphe on 2016. 4. 12..
//

#ifndef PROJECT_TEXTURE_H
#define PROJECT_TEXTURE_H

#include "Image.h"
#include <glfw/GLFW3.h>
#include "ShaderParam.h"

namespace Render{
	class RenderingParameters;

	class Texture {
	public:
		Texture(Resource::Image::PTR pImage);
		Texture();
		virtual ~Texture();
		void Bind(Render::ShaderParam& shader, int i) const;
		inline GLuint GetID() const {return m_uTexture;}
		void Clear();

	protected:
		void InitTexture(Resource::Image::PTR pImage);

	protected:
		GLuint m_uTexture = 0;
	};
}

#endif //PROJECT_TEXTURE_H
