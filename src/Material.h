//
// Created by inosphe on 2016. 4. 12..
//

#ifndef PROJECT_MATERIAL_H
#define PROJECT_MATERIAL_H

#include "common_header.h"
#include <fbxsdk.h>
#include "MaterialElement.h"
#include <vector>
#include "ShaderParam.h"

namespace Render{
	class Material {
	public:
		~Material();
		MaterialElement& AddElement();
		void Bind(Render::ShaderParam& shader) const;
		void Clear();

	private:
		std::vector<MaterialElement*> m_vecElements;
	};
}


#endif //PROJECT_MATERIAL_H
