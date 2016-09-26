//
// Created by inosphe on 2016. 4. 12..
//

#ifndef PROJECT_MATERIALELEMENT_H
#define PROJECT_MATERIALELEMENT_H

#include <vector>
#include <memory>
#include "common_header.h"
#include "Image.h"
#include "ShaderParam.h"

namespace Render{
	class Texture;

	class MaterialElement {
		public:
			MaterialElement();
			virtual ~MaterialElement();

			void AddTexture(Resource::Image::PTR pImage);
			void Bind(Render::ShaderParam& shader) const;
			void Clear();

		public:
			float m_fShininess = 0.0;
			float m_fSpecular = 0.0;
			float m_fReflectionFactor = 0.0;

		protected:
			std::vector<Render::Texture*> m_vecTexture;
	};
}



#endif //PROJECT_MATERIALELEMENT_H
