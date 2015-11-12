
#ifndef _MSALGO_H_
#define _MSALGO_H_

#include "scheduler.h"

class msAlgo : scheduler{
public:
	msAlgo() { }
	virtual ~msAlgo() { }

	void schedule(const allocation&);
};

#endif
