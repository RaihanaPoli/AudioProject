/*
* Simple app to read/write into custom IP in PL via /dev/uoi0 interface
* To compile for arm: make ARCH=arm CROSS_COMPILE=arm-xilinx-linux-gnueabi-
* Author: Tsotnep, Kjans
*/
  
//C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdint.h>
  
#define SLV_REG_0   *((unsigned *)(ptr + 0))
#define SLV_REG_1   *((unsigned *)(ptr + 4))
#define SLV_REG_2   *((unsigned *)(ptr + 8))
#define SLV_REG_3   *((unsigned *)(ptr + 12))
#define SLV_REG_4   *((unsigned *)(ptr + 16))
  
#define SLV_REG_5   *((unsigned *)(ptr + 20))
#define SLV_REG_6   *((unsigned *)(ptr + 24))
#define SLV_REG_7   *((unsigned *)(ptr + 28))
#define SLV_REG_8   *((unsigned *)(ptr + 32))
#define SLV_REG_9   *((unsigned *)(ptr + 36))
  
#define SLV_REG_10   *((unsigned *)(ptr + 40))
#define SLV_REG_11   *((unsigned *)(ptr + 44))
#define SLV_REG_12   *((unsigned *)(ptr + 48))
#define SLV_REG_13   *((unsigned *)(ptr + 52))
#define SLV_REG_14   *((unsigned *)(ptr + 56))

#define SLV_REG_15   *((unsigned *)(ptr + 60))
#define SLV_REG_16   *((unsigned *)(ptr + 64))

#define SLV_REG_17   *((unsigned *)(ptr + 68))
#define SLV_REG_18   *((unsigned *)(ptr + 72))
#define SLV_REG_19   *((unsigned *)(ptr + 76))


#define LOW 1
#define MID 2
#define HIGH 3

int main(int argc, char *argv[])
{
    if (*argv[1] == 'p') {
        printf("::::START_USAGE::::\n");
        printf("EXAMPLE : %s 0 1 \n", argv[0]);
        printf("::::END_USAGE::::\n");
    }
    else {
  
        //take inputs from user
        unsigned filter = atoi(argv[2]);
  

        // Addresses
        unsigned address0 = 0x43C10000;
        unsigned address1 = 0x43C30000;

        unsigned channel = atoi(argv[1]);// 0 - line_in, 1 - udp
        unsigned address = channel == 0 ? address0 : address1;

        printf("Opening /dev/mem");
        int fd = open("/dev/mem", O_RDWR);
        if (fd < 1) { perror("mem"); return -1; }

        printf("/dev/mem opened");


 
        //Redirect stdout/printf into /dev/kmsg file (so it will be printed using printk)
        //freopen ("/dev/kmsg","w",stdout);
  

        //get architecture specific page size
        unsigned pageSize = sysconf(_SC_PAGESIZE);

        unsigned offset = (address & (~(pageSize - 1)));


        printf("Mapping address\n");
        void *ptr = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
  
        SLV_REG_0 = 0x00002cb6;
	SLV_REG_1 = 0x0000596c;
	SLV_REG_2 = 0x00002cb6;
	SLV_REG_3 = 0x8097a63a;
	SLV_REG_4 = 0x3f690c9d;

	SLV_REG_5 = 0x074d9236;
	SLV_REG_6 = 0x00000000;
	SLV_REG_7 = 0xf8b26dca;
	SLV_REG_8 = 0x9464b81b;
	SLV_REG_9 = 0x3164db93;

	SLV_REG_10 = 0x12bec333;
	SLV_REG_11 = 0xda82799a;
	SLV_REG_12 = 0x12bec333;
	SLV_REG_13 = 0x00000000;
	SLV_REG_14 = 0x0afb0ccc;

        SLV_REG_16 = 1;

        if (filter == LOW) {
                SLV_REG_19 = 0;
                SLV_REG_18 = 1;
                SLV_REG_17 = 1;
        } else if (filter == MID) {
                SLV_REG_19 = 1;
                SLV_REG_18 = 0;
                SLV_REG_17 = 1;
        } else if (filter == HIGH) {
                SLV_REG_19 = 1;
                SLV_REG_18 = 1;
                SLV_REG_17 = 0;
        } else {
                SLV_REG_19 = 0;
                SLV_REG_18 = 0;
                SLV_REG_17 = 0;
        }

        
  
        //unmap
        munmap(ptr, pageSize);
  
        //close
        fclose(stdout);
    }
    return 0;
}
