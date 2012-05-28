
#ifndef __POSIX_EVENT_H__
#define __POSIX_EVENT_H__


void *posix_event_create(void);

int posix_event_timed_wait(void *event, unsigned int timeout);

void posix_event_wait(void *event);

void posix_event_signal(void *event);


#endif /* __POSIX_EVENT_H__ */

