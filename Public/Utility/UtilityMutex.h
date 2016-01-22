#ifndef _UtilityMutex_H_
#define _UtilityMutex_H_

#include <UtilityDefine.h>

class UtilityMutex
{
	friend class UtilityCond;

public:
	UtilityMutex();
	~UtilityMutex();

	inline void Lock()
	{
		pthread_mutex_lock(&mutex_);
	}

	inline void Unlock()
	{
		pthread_mutex_unlock(&mutex_);
	}

	inline bool TryLock()
	{
		return (pthread_mutex_trylock(&mutex_) == 0);
	}

protected:
	pthread_mutex_t mutex_;
};

class UtilityCond
{
public:
	inline UtilityCond()
	{
		pthread_cond_init(&cond_,NULL);
	}
	inline ~UtilityCond()
	{
		pthread_cond_destroy(&cond_);
	}

	inline void Signal()
	{
		pthread_cond_signal(&cond_);
	}
	inline void Broadcast()
	{
		pthread_cond_broadcast(&cond_);
	}
	inline void Wait(UtilityMutex * lock)
	{
		pthread_cond_wait(&cond_, &lock->mutex_);
	}
	inline bool Wait(UtilityMutex * lock,int seconds)
	{
		timespec tv;
		tv.tv_nsec = 0;
		tv.tv_sec  = seconds;
		if ( pthread_cond_timedwait(&cond_, &lock->mutex_, &tv) == 0)
			return true;
		else
			return false;
	}

private:
	pthread_cond_t cond_;
};

class UtilityGuard
{
private :
	UtilityMutex & mtx_;

public:
	UtilityGuard(UtilityMutex & mtx)
		: mtx_(mtx)
	{
		mtx_.Lock();
	}
	~UtilityGuard() {
		mtx_.Unlock();
	}
};

#endif
