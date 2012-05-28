

#include "posix_event.h"


#include <pthread.h>
#include <time.h>
#include <malloc.h>


typedef struct
{
   pthread_mutex_t mutex;
   pthread_cond_t cv;
}
posix_event_t;


static void *posix_event_create(void)
{
   posix_event_t *pev = malloc(sizeof(posix_event_t));
   pthread_mutex_init(&pev->mutex, NULL);
   pthread_cond_init(&pev->cv, NULL);
   return pev;
}


static int posix_event_timed_wait(void *event, unsigned int timeout)
{
   posix_event_t *pev = (posix_event_t *)event;
   pthread_mutex_lock(&pev->mutex);
   struct timespec ts;
   clock_gettime(CLOCK_REALTIME, &ts);
   ts.tv_sec += timeout;
   int ret = pthread_cond_timedwait(&pev->cv, &pev->mutex, &ts);
   pthread_mutex_unlock(&pev->mutex);
   return ret;
}


static void posix_event_wait(void *event)
{
   posix_event_t *pev = (posix_event_t *)event;
   pthread_mutex_lock(&pev->mutex);
   pthread_cond_wait(&pev->cv, &pev->mutex);
   pthread_mutex_unlock(&pev->mutex);
}


static void posix_event_signal(void *event)
{
   posix_event_t *pev = (posix_event_t *)event;
   pthread_mutex_lock(&pev->mutex);
   pthread_cond_broadcast(&pev->cv);
   pthread_mutex_unlock(&pev->mutex);
}


void posix_event_interface_init(event_interface_t *event_interface)
{
   event_interface->create = posix_event_create;
   event_interface->timed_wait = posix_event_timed_wait;
   event_interface->wait = posix_event_wait;
   event_interface->signal = posix_event_signal;
}

