//
// Created by inosphe on 2016. 3. 28..
//

#include "IModel.h"

namespace Render{
	IModel::IModel()
	:IMesh(), IMovableObject()
	{

	}

	IModel::~IModel() {
		_Clear();
	}

	void IModel::UpdateForRender() {
		IRenderable::UpdateForRender();

		m_matWorldTransform = GetTransform();
	}

	void IModel::Clear() {
		_Clear();
		IMesh::Clear();
	}

	void IModel::_Clear() {

	}
}

