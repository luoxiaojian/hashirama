
#ifndef _BFALLOCATOR_H_
#define _BFALLOCATOR_H_

#include "allocator.h"

class bfAllocator : public allocator {
	public:
		bfAllocator() { }
		virtual ~bfAllocator() { }

		bool allocate(const taskset& ts, allocation& al);
};

#endif
