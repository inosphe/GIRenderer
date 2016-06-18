//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_MODEL_H
#define PROJECT_MODEL_H

#include "IMovableObject.h"
#include "IMesh.h"

namespace Render{
	class IModel : public IMesh, public IMovableObject{
	public:
		IModel();
		virtual ~IModel();

		virtual void UpdateForRender() override;

		virtual void Clear() override;

	protected:

	private:
		void _Clear();
	};
}


#endif //PROJECT_MODEL_H
