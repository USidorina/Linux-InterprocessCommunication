#include "connector.h"

static int fifoFileDesc = 0;

Connector::Connector() {

	if (mkfifo("ipc_fifo", S_IRWXU) == -1) {

		isInitialized = false;
	}
	else {

		isInitialized = true;
	}
	
	fifoFileDesc = open("ipc_fifo", O_RDWR | O_NONBLOCK);

	if (fifoFileDesc == -1 ) {

		isInitialized = false;
	}
}

bool Connector::Read(void * readBuf, int readBufSize) {

	if (!isInitialized) {

		std::cout << "ERROR: Connector initialization was failed" << std::endl;
		return 0;
	}

	if (read(fifoFileDesc,readBuf, readBufSize) == -1) {

		return 0;
	}

	return 1;
}

bool Connector::Write(void * writeBuf, int writeBufSize) {

	if (!isInitialized) {

		std::cout << "ERROR: Connector initialization was failed" << std::endl;
		return 0;
	}

	if (write(fifoFileDesc, writeBuf, writeBufSize) == -1) {

		return 0;
	}

	return 1;

}

Connector::~Connector() {

	close(fifoFileDesc);
	unlink("ipc_fifo");
 }