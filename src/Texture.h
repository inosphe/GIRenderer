//
// Created by inosphe on 2016. 4. 12..
//

#ifndef PROJECT_TEXTURE_H
#define PROJECT_TEXTURE_H

#include "Image.h"
#include <glfw/GLFW3.h>

namespace Render{
	class RenderingParameters;

	class Texture {
	public:
		Texture(int iOffset, Resource::Image::PTR pImage);
		virtual ~Texture();
		void Bind(Render::RenderingParameters& rp) const;
		inline int GetTexOffset() const {return m_iTexOffset;}
		inline GLuint GetID() const {return m_uTexture;}
		void Clear();

	protected:
		void InitTexture(Resource::Image::PTR pImage);

	private:
		int m_iTexOffset = 0;
		GLuint m_uTexture = 0;
	};
}

#endif //PROJECT_TEXTURE_H
