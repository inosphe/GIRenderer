//
// Created by inosphe on 2016. 4. 1..
//

#ifndef PROJECT_IRESOUrCELOADER_H
#define PROJECT_IRESOUrCELOADER_H

#include "common_header.h"
#include <memory>

namespace Resource{
	class IResource;

	class IResourceLoader {
	public:
		virtual std::shared_ptr<IResource> Load(const string& strFilepath) = 0;
	};
}



#endif //PROJECT_IRESOUrCELOADER_H
