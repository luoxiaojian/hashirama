
#ifndef _BFALLOCATOR_H_
#define _BFALLOCATOR_H_

#include "allocator.h"

class bfAllocator : public allocator {
	public:
		bfAllocator() { }
		~bfAllocator() { }

		bool allocate(const taskset& ts, allocation& al);
};

#endif
