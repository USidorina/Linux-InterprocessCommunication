#include "connector.h"

static mqd_t messageQueue;

Connector::Connector() {

	mq_attr attr;

	attr.mq_flags   = 0;
	attr.mq_maxmsg  = 1;
	attr.mq_msgsize = sizeof(int);
	attr.mq_curmsgs = 0;
    
    messageQueue = mq_open("/ipc_mq", O_CREAT | O_RDWR, S_IRWXU, &attr);

    if (messageQueue == -1) {

    	isInitialized = false;
    }
    else {

    	isInitialized = true;
    }
}

bool Connector::Read(void * readBuf, int readBufSize) {

	if (!isInitialized) {

		std::cout << "ERROR: Connector initialization was failed" << std::endl;
		return 0;
	}

	unsigned int prio;

	if (mq_receive(messageQueue, (char *)readBuf, readBufSize, &prio) == -1) {

        std::cout << "ERROR: wq_receive() was failed" << std::endl;
		return 0;
	}

	return 1;
}

bool Connector::Write(void * writeBuf, int writeBufSize) {

	if (!isInitialized) {

		std::cout << "ERROR: Connector initialization was failed" << std::endl;
		return 0;
	}

	if (mq_send(messageQueue, (char *)writeBuf, writeBufSize, 0) == -1) {

        std::cout << "ERROR: wq_send() was failed" << std::endl;
		return 0;
	}

	return 1;
}

Connector::~Connector() {

	mq_close(messageQueue);
}
