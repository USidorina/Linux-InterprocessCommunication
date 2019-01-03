# Linux-InterprocessCommunication
## Description
In this program two related processes (parent and child) communicate with each other. Child process has two conditions: alive and dead. Parent process sends to child process current child status (initial status is alive). If current status is alive then child process sends random number from 1 to 100, else - from 1 to 50. Then parent process generates random number from 1 to 100. If current child status is alive and difference between child number and parent number > 70 then new child status is dead, else if current child status is dead and difference between child number and parent number <= 20 then new child status is alive.
End of game comes if child status is dead twice in a row.

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
## Test program
Now parent process always sends 100 and child process always sends 25, so game ends after three moves.
