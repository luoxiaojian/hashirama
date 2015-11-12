#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include "taskset.h"
#include "allocation.h"

class allocator {
	public:
		allocator() { }

		virtual ~allocator() { }

		virtual bool allocate(const taskset& ts, allocation& al)=0;
};

#endif
