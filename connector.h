#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <mqueue.h>
#include <cstring>
#include <iostream>
#include <time.h>
#include <syslog.h>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string>
#include <cstdio>
#include <sys/socket.h>


class Connector {

public:

  Connector();

  bool Read(void * readBuf, int readBufSize);
  bool Write(void * writeBuf, int writeBufSize);
  
  ~Connector();

private:

	bool isInitialized; // true - connector was initialized successfully, false - initialization was failed
};

#endif 