#include "connector.h"

#define BUFFER_SIZE 100

static void * buffer = NULL;

static int curBufferSize = 0;

Connector::Connector() {
    
	buffer = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

	isInitialized = true;
}

bool Connector::Read(void * readBuf, int readBufSize) {

	if (!isInitialized) {

		std::cout << "ERROR: Connector initialization was failed" << std::endl;
		return 0;
	}

	if (readBufSize < curBufferSize) {

		std::cout << "ERROR: Read buffer size is less than communication buffer size" << std::endl;
		return 0;
	}	

    readBuf = std::memcpy(readBuf, buffer, BUFFER_SIZE);

    if (readBuf == NULL) {

    	std::cout << "ERROR: Memcpy returns null pointer" << std::endl;
		return 0;	
    }

    return 1;
}

bool Connector::Write(void * writeBuf, int writeBufSize) {

	if (!isInitialized) {

		std::cout << "ERROR: Connector initialization was failed" << std::endl;
		return 0;
	}
	
	if (writeBufSize > BUFFER_SIZE) {

        std::cout << "ERROR: Write buffer size is bigger than communication buffer size" << std::endl;
		return 0;
	}

    
    buffer = std::memcpy(buffer, writeBuf, writeBufSize);

    
    if (buffer == NULL) {

        std::cout << "ERROR: Memcpy returns null pointer" << std::endl;
		return 0;	
    }

    curBufferSize = writeBufSize;

    return 1;

}

Connector::~Connector() {

	munmap(buffer, BUFFER_SIZE);
}