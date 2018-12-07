#ifndef CHILD_PROCESS_H
#define CHILD_PROCESS_H

#include "process.h"

class ChildProcess : public Process {

public:

	ChildProcess() {};     

	void        run(Connector & connector, sem_t * sem_parent, sem_t * sem_child);
	int         generateNumber();

	~ChildProcess() {};

private:

	ChildStatus status;
};

#endif