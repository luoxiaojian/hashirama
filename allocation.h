
#ifndef _ALLOCATION_H_
#define _ALLOCATION_H_

#include <stdlib.h>
#include <iostream>
#include "taskset.h"

class allocation {
	public:
		allocation(const taskset& ts) : tnum_(ts.tnum), rnum_(ts.rnum), pnum_(ts.pnum) {
			alloc=(int **)malloc(sizeof(int*)*tnum_);
			for(int i=0; i<tnum_; i++)
				alloc[i]=(int *)malloc(sizeof(int)*rnum_);
		}

		~allocation() {
			for(int i=0; i<tnum_; i++)
				free(alloc[i]);
			free(alloc);
		}

		void output();

	private:
		int tnum_;
		int rnum_;
		int pnum_;

	public:
		int **alloc;
};

#endif
