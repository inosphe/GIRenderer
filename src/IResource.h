//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_IRESOURCE_H
#define PROJECT_IRESOURCE_H

#include "ResourceType.h"

namespace Resource{
	class IResource {
	public:
		IResource(RESOURCE_TYPE type);
		virtual ~IResource(){}
		virtual void Clear(){}

		const RESOURCE_TYPE m_type;
	};
}


#endif //PROJECT_IRESOURCE_H
