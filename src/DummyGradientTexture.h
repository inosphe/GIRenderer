//
// Created by inosphe on 2016. 9. 14..
//

#ifndef PROJECT_DUMMYGRADIENTTEXTURE_H
#define PROJECT_DUMMYGRADIENTTEXTURE_H

#include "Texture.h"

namespace Render{
	class DummyGradientTexture : public Texture{
		DummyGradientTexture(int type);
		virtual ~DummyGradientTexture(){}
	};
}



#endif //PROJECT_DUMMYGRADIENTTEXTURE_H
