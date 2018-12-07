#include "child_process.h"


void ChildProcess::run(Connector & connector, sem_t * sem_parent, sem_t * sem_child) {

	std::cout << "Game start!" << std::endl;

	while (true) {

		sem_wait(sem_child);

		//read child current status
		ChildStatus newStatus;
		connector.Read(&newStatus, sizeof(newStatus));
		std::cout << "Child status is " << newStatus << std::endl;	
		status = newStatus;

		//check Child status
		if (status == END_OF_GAME) {

			break;
		}

		//generate child number
		int number = generateNumber();

		//write number
		std::cout << "Child number is " << number << std::endl;
		connector.Write(&number, sizeof(number));

		sem_post(sem_parent);
	}

    std::cout << "End of Game!" << std::endl;

	sem_post(sem_parent);
	exit(0);
}

int ChildProcess::generateNumber() {

    srand(unsigned(time(0)) + 7654); //constant for different parent and child numbers 

    int number = 0;

	switch (status) {

		case ALIVE:

			number = rand() % 100 + 1;
		    break;

		case DEAD:

			number = rand() % 50 + 1;
		    break;

		case END_OF_GAME:

		    //do nothing
			break;
	}

	number = 25;

	return number;
}

