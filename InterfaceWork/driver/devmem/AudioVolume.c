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
  
  
int main(int argc, char *argv[])
{
    if (*argv[1] == 'p') {
        printf("::::START_USAGE::::\n");
        printf("EXAMPLE : %s 0 256 \n", argv[0]);
        printf("::::END_USAGE::::\n");
    }
    else {
        printf("Starting audio_copy_driver\n");
  
        //take inputs from user
        unsigned volume = atoi(argv[2]);

        // Addresses
        unsigned address0 = 0x43C20000;
        unsigned address1 = 0x43C40000;

        unsigned channel = atoi(argv[1]);// 0 - line_in, 1 - udp
        unsigned address = (channel == 0) ? address0 : address1;

        printf("Channel %d\n", channel);
        printf("Address %d\n", address);

        printf("Opening /dev/mem\n");
        int fd = open("/dev/mem", O_RDWR);
        if (fd < 1) { perror("mem"); return -1; }

        printf("/dev/mem opened\n");

 
  
        //Redirect stdout/printf into /dev/kmsg file (so it will be printed using printk)
        //freopen ("/dev/kmsg","w",stdout);
  
        //get architecture specific page size
        unsigned pageSize = sysconf(_SC_PAGESIZE);

        unsigned offset = (address & (~(pageSize - 1)));

          
        printf("Mapping address\n");
        void *ptr = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);


        // Write volume to registers
        SLV_REG_0 = volume;
        SLV_REG_1 = volume;
         
  
        //unmap
        munmap(ptr, pageSize);
  
        //close
        fclose(stdout);
    }
    return 0;
}
