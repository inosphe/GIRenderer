//
// Created by inosphe on 2016. 3. 28..
//

#ifndef PROJECT_SINGLETON_H
#define PROJECT_SINGLETON_H

#include "common_header.h"

template <class T>
class Singleton {
protected:
	Singleton(){}
	virtual bool Init(){}

public:
	~Singleton(){SAFE_DELETE(m_pInstance);}
	virtual void Clear(){}

	T& GetInstance(){
		if(!m_pInstance)
			m_pInstance = new T();
		return m_pInstance;
	}

private:
	T* m_pInstance;
};


#endif //PROJECT_SINGLETON_H
