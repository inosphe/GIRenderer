//
// Created by inosphe on 2016. 9. 14..
//

#ifndef PROJECT_DUMMYGRADIENTTEXTURE_H
#define PROJECT_DUMMYGRADIENTTEXTURE_H

#include "Texture.h"

namespace Render{
	class DummyGradientTexture : public Texture{
	public:
		DummyGradientTexture(int size, int type=0);
		virtual ~DummyGradientTexture();

	private:
		uint8_t* m_pData = nullptr;
	};
}



#endif //PROJECT_DUMMYGRADIENTTEXTURE_H
