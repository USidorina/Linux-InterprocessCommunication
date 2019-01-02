# Linux-InterprocessCommunication
## Description
In this program two related processes (parent and child) communicate with each other. Child process has two conditions: alive and dead. Parent process sends to child process current child status (initial status is alive). If current status is alive then child process sends random number from 1 to 100, else - from 1 to 50. Then parent process generates random number from 1 to 100.

Processes can communicate using these types of IPC:
* mmap (anonymous mapping)
* shmopen + mmap
* pipe
* mkfifo (named pipes)
* socket
* mq_open
## Start program
For example using anonymous mapping

    make
    ./conn_mmap
