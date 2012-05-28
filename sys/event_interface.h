

#ifndef __EVENT_INTERFACE_H__
#define __EVENT_INTERFACE_H__


typedef struct
{
   void *(*create)(void);
   int (*timed_wait)(void *data, unsigned int timeout);
   void (*wait)(void *data);
   void (*signal)(void *data);
}
event_interface_t;


#endif /* __EVENT_INTERFACE_H__ */

