#include "connector.h"

static int sockets[2];

Connector::Connector() {

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == -1) {

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

	if (read(sockets[0], readBuf, readBufSize) == -1) {

		std::cout << "ERROR: read() was failed" << std::endl;
		return 0;
	}

	return 1;
}

bool Connector::Write(void * writeBuf, int writeBufSize) {

	if (!isInitialized) {

		std::cout << "ERROR: Connector initialization was failed" << std::endl;
		return 0;
	}

	if (write(sockets[1], writeBuf, writeBufSize) == -1) {

		std::cout << "ERROR: write() was failed" << std::endl;
		return 0;
	}

	return 1;
}

Connector::~Connector() {

	close(sockets[0]);
	close(sockets[1]);
}
