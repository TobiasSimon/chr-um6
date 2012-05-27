

#include "posix_lock.h"


#include <pthread.h>
#include <malloc.h>



void um6_posix_lock_init(um6_lock_t *lock)
{
   lock->context = malloc(sizeof(pthread_mutex_t));
   pthread_mutex_init((pthread_mutex_t *)lock->context, NULL);
   lock->lock = (int (*)(void *))pthread_mutex_lock;
   lock->unlock = (int (*)(void *))pthread_mutex_unlock;
}

