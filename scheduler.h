
#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

class scheduler {
public:
	scheduler() { }
	virtual ~scheduler() { }

	virtual void schedule(const allocation&)=0;

};

#endif
