#include "UtilityMutex.h"

/* Linux mutex implementation */
static bool attr_initalized = false;
static pthread_mutexattr_t attr;

UtilityMutex::UtilityMutex()
{
	if(!attr_initalized)
	{
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
		attr_initalized = true;
	}

	pthread_mutex_init(&mutex_, &attr);
}

UtilityMutex::~UtilityMutex()
{
	pthread_mutex_destroy(&mutex_);
}
