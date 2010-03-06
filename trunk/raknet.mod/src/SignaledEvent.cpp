#include "SignaledEvent.h"
#include "RakAssert.h"
#include "RakSleep.h"

#if defined(__GNUC__) 
#include <sys/time.h>
#include <unistd.h>
#endif

SignaledEvent::SignaledEvent()
{
#ifdef _WIN32
	eventList=INVALID_HANDLE_VALUE;
#else
	isSignaled=false;
#endif
}
SignaledEvent::~SignaledEvent()
{
	// Intentionally do not close event, so it doesn't close twice on linux
}

void SignaledEvent::InitEvent(void)
{
#ifdef _WIN32
		eventList=CreateEvent(0, false, false, 0);
#else
		pthread_condattr_init( &condAttr );
		pthread_cond_init(&eventList, &condAttr);
		pthread_mutexattr_init( &mutexAttr	);
		pthread_mutex_init(&hMutex, &mutexAttr);
#endif
}

void SignaledEvent::CloseEvent(void)
{
#ifdef _WIN32
	if (eventList!=INVALID_HANDLE_VALUE)
	{
		CloseHandle(eventList);
		eventList=INVALID_HANDLE_VALUE;
	}
#else
	pthread_cond_destroy(&eventList);
	pthread_mutex_destroy(&hMutex);
	pthread_condattr_destroy( &condAttr );
	pthread_mutexattr_destroy( &mutexAttr );
#endif
}

void SignaledEvent::SetEvent(void)
{
#ifdef _WIN32
	::SetEvent(eventList);
#else
	// Different from SetEvent which stays signaled.
	// We have to record manually that the event was signaled
	isSignaledMutex.Lock();
	isSignaled=true;
	isSignaledMutex.Unlock();

	// Unblock waiting threads
	pthread_cond_broadcast(&eventList);
#endif
}

void SignaledEvent::WaitOnEvent(int timeoutMs)
{
#ifdef _WIN32
//	WaitForMultipleObjects(
//		2,
//		eventList,
//		false,
//		timeoutMs);
	WaitForSingleObject(eventList,timeoutMs);
#else

	// If was previously set signaled, just unset and return
	isSignaledMutex.Lock();
	if (isSignaled==true)
	{
		isSignaled=false;
		isSignaledMutex.Unlock();
		return;
	}
	isSignaledMutex.Unlock();

	
	struct timespec   ts;

	// Else wait for SetEvent to be called
#if defined(_PS3) || defined(__PS3__) || defined(SN_TARGET_PS3)
                                                                                                                                                                                                                                                                                                                                      
	#else
		int rc;
		struct timeval    tp;
		rc =  gettimeofday(&tp, NULL);
		ts.tv_sec  = tp.tv_sec;
		ts.tv_nsec = tp.tv_usec * 1000;
	#endif

		while (timeoutMs > 30)
		{
			// Wait 30 milliseconds for the signal, then check again.
			// This is in case we  missed the signal between the top of this function and pthread_cond_timedwait, or after the end of the loop and pthread_cond_timedwait
			ts.tv_nsec += 30*1000000;
			if (ts.tv_nsec >= 1000000000)
			{
			        ts.tv_nsec -= 1000000000;
			        ts.tv_sec++;
			}
			pthread_cond_timedwait(&eventList, &hMutex, &ts);
			timeoutMs-=30;

			isSignaledMutex.Lock();
			if (isSignaled==true)
			{
				isSignaled=false;
				isSignaledMutex.Unlock();
				return;
			}
			isSignaledMutex.Unlock();
		}

		// Wait the remaining time, and turn off the signal in case it was set
		ts.tv_nsec += timeoutMs*1000000;
		if (ts.tv_nsec >= 1000000000)
		{
		        ts.tv_nsec -= 1000000000;
		        ts.tv_sec++;
		}
		pthread_cond_timedwait(&eventList, &hMutex, &ts);

		isSignaledMutex.Lock();
		isSignaled=false;
		isSignaledMutex.Unlock();
#endif
}
