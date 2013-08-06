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
#include <sys/atomics.h>


#include "gtthread.h"


#define DEFAULT_STACKSIZE (1024 * 1024)

static gtthread_attr_t gDefaultGTthreadAttr = {
    .flags = 0,
    .stack_base = NULL,
    .stack_size = DEFAULT_STACKSIZE,
};

int gtthread_attr_init(gtthread_attr_t * attr){
	*attr = gDefaultGTthreadAttr;
	//printf("\nAttribute Initialized ");
    return 0;
	
}
int gtthread_create(gtthread_t *thread, gtthread_attr_t const * attr,
                   void *(*start_routine)(void *), void * arg){

	char* stack = malloc(attr->stack_size);
	//attr->stack_base = stack;
	void* tls = stack + attr->stack_size;     //move pointer higher in memory to top of stack

	int flags = CLONE_FILES | CLONE_FS | CLONE_VM | CLONE_SIGHAND |
                CLONE_THREAD | CLONE_SYSVSEM | CLONE_DETACHED;
    *thread = clone((int(*)(void*))start_routine, tls, flags, arg);

    //printf("\nThread Created ");
    usleep(2000);

    return 0;
}

int gtthread_join(gtthread_t thid, void ** ret_val){
	//printf("\nAbout to wait");
	waitpid(thid, NULL, 0);
	//printf("\nThread joined ");
	return 0;
}

int gtthread_mutex_init(gtthread_mutex_t *mutex){
	mutex->value = 0;
	//printf("\nMutex Initialized ");
	return 0;
}
int gtthread_mutex_lock(gtthread_mutex_t *mutex){
	const int unlocked = 0;
	const int locked_uncontended = 1;

	if(__atomic_cmpxchg(unlocked, locked_uncontended, &mutex->value) != 0)	
	{
		const int locked_contended = 2;
		while(__atomic_swap(locked_contended, &mutex->value) != unlocked)
		//{}
			__futex_wait_ex(&mutex->value, 0, locked_contended, 0);
	}
	//printf("\nMutex Locked ");
	return 0;
}

int gtthread_mutex_unlock(gtthread_mutex_t *mutex){
	if( __atomic_dec(&mutex->value) != 0)
	{
		mutex->value = 0;
		//printf("\nMutex Unlocked ");
		//usleep(30000);
		__futex_wake_ex(&mutex->value, 0, 1);
		//usleep(1);
	}
	//sleep(1);

	
	
	return 0;
}

int gtthread_exit(void * retval){
	exit(0);
}