//
// Created by inosphe on 2016. 4. 12..
//

#ifndef PROJECT_IMAGE_H
#define PROJECT_IMAGE_H

#include "common_header.h"

namespace Resource{
	class Image {
	public:
		DECLARE_RESOURCE(Image)

		Image();
		Image(BYTE* pData, int w, int h, int comp);
		virtual ~Image();

		inline const BYTE* GetData(){return m_pData;}
		inline int GetWidth(){return m_iWidth;}
		inline int GetHeight(){return m_iHeight;}
		inline int GetComponentNum(){return m_iComp;}
		int GetFormat();

	private:
		BYTE* m_pData = nullptr;
		int m_iWidth = 0;
		int m_iHeight = 0;
		int m_iComp = 0;
	};



}


#endif //PROJECT_IMAGE_H
