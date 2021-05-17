/////////////////////////////////////////////////////////////////
//
// CCISEL 
// 2007-2021
//
// UThread library:
//   User threads supporting cooperative multithreading.
//
// Authors:
//   Carlos Martins, João Trindade, Duarte Nunes, Jorge Martins
// 

#ifndef _UTHREADINTERNAL_H
#define _UTHREADINTERNAL_H

#include <assert.h>
#include "uthread.h"
#include "list.h"

//
// The data structure representing the layout of a thread's execution
// context when saved in the stack.
//
typedef struct uthread_context {
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t rbx;
	uint64_t rbp;
	void (*ret_addr)();
} uthread_context_t;

//
// The descriptor of a user thread, containing an intrusive link
// (through which the thread is linked in the ready queue), the
// thread's starting function and argument, the memory block used as
// the thread's stack and a pointer to the saved execution context.
//
typedef struct uthread {
	uthread_context_t * context;
	list_entry_t        entry;
	void             (* function)(void *);   
	void *              argument; 
	void *              stack;
} uthread_t;

//
// The fixed stack size of a user thread.
//
#define STACK_SIZE (8 * 4096)

#endif
