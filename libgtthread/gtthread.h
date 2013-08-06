#ifndef _GTTHREAD_H_
#define _GTTHREAD_H_


#include <sys/wait.h>
#include <sched.h>
#include <malloc.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <malloc.h>
#include <memory.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/atomics.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/*
 * Types
 */
typedef struct
{
  // Fill this
	int volatile value;
} gtthread_mutex_t;

typedef struct
{
  // Fill this
	uint32_t flags;
    void * stack_base;
    size_t stack_size;
} gtthread_attr_t;

typedef unsigned int gtthread_t;
/*
 * Prototypes
 */
#ifdef __cplusplus
extern "C" {
#endif

int gtthread_attr_init(gtthread_attr_t * attr);
int gtthread_create(gtthread_t *thread, gtthread_attr_t const * attr,
                   void *(*start_routine)(void *), void * arg);
int gtthread_join(gtthread_t thid, void ** ret_val);

int gtthread_mutex_init(gtthread_mutex_t *mutex);
int gtthread_mutex_lock(gtthread_mutex_t *mutex);
int gtthread_mutex_unlock(gtthread_mutex_t *mutex);
int gtthread_exit(void * retval);


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* _GTTHREAD_H_ */
