#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <pthread.h>
#include "udpclient.h"

#define AUDIO_OUT_REG *((unsigned *)(audioOutPtr + 0))



char * myfifo = "/tmp/myfifo";
 void *audioOutPtr;

void *line_out(){
	int fifo;
	fifo = open(myfifo, O_RDONLY);
	int buffer;
	while (1) {
		read(fifo, &buffer, sizeof(buffer));
		AUDIO_OUT_REG = buffer;
	}
	return 0;
}


int main(int argc, char *argv[])
{
     
    

        // Audio out address
        unsigned address = 0x43c00000;

        printf("Opening /dev/mem");
        int audioOutFd = open("/dev/mem", O_RDWR);
        if (audioOutFd < 1) { perror("mem"); return -1; }

        printf("/dev/mem opened");
    	/* create the FIFO (named pipe) */
    	mkfifo(myfifo, 0666);


  
        //get architecture specific page size
        unsigned pageSize = sysconf(_SC_PAGESIZE);

        unsigned offset = (address & (~(pageSize - 1)));

        printf("Mapping address\n");
        audioOutPtr = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, audioOutFd, offset);

	pthread_t line_out_thread;
	
 	if(pthread_create(&line_out_thread, NULL, line_out, NULL)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	int fifo;
	fifo = open(myfifo, O_WRONLY);
	udp_client_setup("10.255.255.255", 7891);

	unsigned buffer[64];
        printf("Waiting for new sample interrupt\n");
        while (1) {
		udp_client_recv(buffer, sizeof(buffer));
		write(fifo, &buffer, sizeof(buffer));
        }

    return 0;
}
