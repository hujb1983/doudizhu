#ifndef __UtilitySingleton_H__
#define __UtilitySingleton_H__
#include <UtilityDefine.h>

template <typename T>
class UtilitySingleton
{
public:
	~UtilitySingleton() {
	}
	static T * Instance() {
		if (0 == ms_pInstance)	{
			ms_pInstance = new T;
		}
		return ms_pInstance;
	}
	static void DestroyInstance() {
		if (ms_pInstance) {		
			delete ms_pInstance;
			ms_pInstance = NULL;
		}
	}
private:
	static T *		ms_pInstance;
};
template< class T > T * UtilitySingleton<T>::ms_pInstance = 0;
#endif // __UtilitySingleton_H__
