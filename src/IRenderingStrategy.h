//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_IRENDERINGSTRATEGY_H
#define PROJECT_IRENDERINGSTRATEGY_H

#include <GLFW/glfw3.h>

class IRenderingStrategy {
public:
	IRenderingStrategy(GLuint uProgram);
	virtual ~IRenderingStrategy();

	virtual void Init(){}
	virtual void Clear(){}

	virtual void RenderBegin() = 0;
	virtual void RenderEnd() = 0;

protected:
	const GLuint m_uProgram;
};


#endif //PROJECT_IRENDERINGSTRATEGY_H
