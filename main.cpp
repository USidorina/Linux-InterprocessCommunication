#include "parent_process.h"
#include "child_process.h"

static ParentProcess parent;
static ChildProcess  child;
static Connector     connector;

static sem_t * sem_parent = NULL;
static sem_t * sem_child  = NULL;


int main(void) {

    int pid;

    sem_parent = sem_open("/sem_parent", O_CREAT | O_EXCL, S_IRWXU, 0);
    sem_child  = sem_open("/sem_child", O_CREAT | O_EXCL, S_IRWXU, 0);

    if (sem_parent == SEM_FAILED || sem_child == SEM_FAILED) {

    	sem_unlink("/sem_parent");
    	sem_unlink("/sem_child");

    	std::cout << "ERROR: Semaphore failed" << std::endl;

    	exit(1);
    }

    pid = fork();

    if (pid) {

    	parent.run(connector, sem_parent, sem_child);
    } 
    else if (!pid) {

    	child.run(connector, sem_parent, sem_child);
        exit(0);
    } 
    else {

    	std::cout << "ERROR: Fork was failed" << std::endl;

        sem_close(sem_parent);
        sem_close(sem_child);

        sem_unlink("/sem_parent");
        sem_unlink("/sem_child");

    	exit(1);
    }

    sem_close(sem_parent);
    sem_close(sem_child);

    sem_unlink("/sem_parent");
    sem_unlink("/sem_child");

	exit(0);
}