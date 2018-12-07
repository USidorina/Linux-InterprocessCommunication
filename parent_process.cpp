#include "parent_process.h"


void ParentProcess::run(Connector & connector, sem_t * sem_parent, sem_t * sem_child) {
	
	ChildStatus childStatus = ALIVE;

	while (true) {

		//write child status;
		connector.Write(&childStatus, sizeof(childStatus));
		std::cout << "Parent set Child status = " << childStatus << std::endl;

		sem_post(sem_child);

		//check Child status
		if (childStatus == END_OF_GAME) {

			break;
		}

		sem_wait(sem_parent);

		//read child number
		int childNumber;
		connector.Read(&childNumber, sizeof(childNumber));
        std::cout << "Parent gets Child number = " << childNumber << std::endl;
 
		//generate parent number
		int parentNumber = generateNumber();
		std::cout << "Parent number is " << parentNumber << std::endl; 	

        
        //check Child and Parent numbers and update child status
        switch (childStatus) {  

        	case ALIVE:

        		if (abs(parentNumber - childNumber) > 70) {
        			childStatus = DEAD;
        		}
        		break;

        	case DEAD:

        		if (abs(parentNumber - childNumber) <= 20) {
        			childStatus = ALIVE;
        		}
        		else {
        			childStatus = END_OF_GAME; // set dead status second time 
        		}
        		break;

        	case END_OF_GAME:;

        		//do nothing
        		break;
        }
	}

	sem_wait(sem_parent);
	exit(0);
}

int ParentProcess::generateNumber() {
	
	srand((time(0)));

	//return rand() % 100 + 1;
	return 100;
}
