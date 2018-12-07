#ifndef PARENT_PROCESS_H
#define PARENT_PROCESS_H

#include "process.h"

class ParentProcess : public Process {

public:

	ParentProcess() {};     

	void run(Connector & connector, sem_t * sem_parent, sem_t * sem_child);
	int  generateNumber();

	~ParentProcess() {};
};

#endif