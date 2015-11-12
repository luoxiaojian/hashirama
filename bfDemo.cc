#include "bfAllocator.h"
#include "allocation.h"
#include "taskset.h"
#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

int main()
{
	ifstream ifs("bf01.cfg");
	taskset ts(ifs);
	bfAllocator ba;
	allocation al(ts);
	bool res=ba.allocate(ts, al);


	assert(res);

	al.output();
	return 0;
}
