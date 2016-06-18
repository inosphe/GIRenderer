//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_DEFERREDRENDERINGSTRATEGY_H
#define PROJECT_DEFERREDRENDERINGSTRATEGY_H

#include "IRenderingStrategy.h"

namespace Render{
	class DeferredRenderingStrategy : public IRenderingStrategy{
	public:
		DeferredRenderingStrategy();
		virtual ~DeferredRenderingStrategy();
	};
}

#endif //PROJECT_DEFERREDRENDERINGSTRATEGY_H
