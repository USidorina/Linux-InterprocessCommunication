#ifndef PROCESS_H
#define PROCESS_H

#include "connector.h"

class Process {

public:

	virtual void run(Connector & connector, sem_t * sem_parent, sem_t * sem_child) = 0;
	virtual int generateNumber() = 0;
};

enum ChildStatus {

	ALIVE,
	DEAD,
	END_OF_GAME,
};

#endif