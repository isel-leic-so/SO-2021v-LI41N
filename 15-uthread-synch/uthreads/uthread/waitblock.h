#pragma once

#include "uthread.h"
#include "list.h"

typedef struct waitblock {
	list_entry_t entry;
	uthread_t * thread;
} waitblock_t;

INLINE void init_waitblock(waitblock_t * waitblock) {
	waitblock->thread = ut_self();
}
