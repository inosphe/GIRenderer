//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_FORWARDRENDERINGSTRATEGY_H
#define PROJECT_FORWARDRENDERINGSTRATEGY_H


#include "IRenderingStrategy.h"
#include <GLFW/glfw3.h>

class ForwardRenderingStrategy : public IRenderingStrategy{
public:
	ForwardRenderingStrategy(GLuint uProgram);
	virtual ~ForwardRenderingStrategy();

	void Init() override;
	void Clear() override;

	virtual void RenderEnd() override;

	virtual void RenderBegin() override;

private:
};


#endif //PROJECT_FORWARDRENDERINGSTRATEGY_H
