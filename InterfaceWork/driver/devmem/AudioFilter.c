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
#include <string.h>
#include "ZedboardOLED.h"

//----------Filter  
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


//-----------For Volume
#define SLV_REG_0V   *((unsigned *)(ptrV + 0))
#define SLV_REG_1V   *((unsigned *)(ptrV + 4))


int main(int argc, char *argv[])
{
    if (*argv[1] == 'p') {
        printf("::::START_USAGE::::\n");
        printf("EXAMPLE : %s 0  500\n", argv[0]);
        printf("::::END_USAGE::::\n");
    }
    else {
		//take input channel from user
  	unsigned channel = atoi(argv[1]);// 0 - network, 1 - linein
        //take  volume inputs from user
        unsigned volume = atoi(argv[2]);
  //-------------------------------------------------------------------------------

        // Addresses for Filter
        unsigned address0 = 0x43C10000; //network filter
        unsigned address1 = 0x43C30000; //linein filter

	// Address for Volume
        unsigned address00 = 0x43C20000; //network vol
        unsigned address11 = 0x43C40000;  //linein vol
//-------------------------------------------------------------------------
        // choose channel for filter
        unsigned address = channel == 0 ? address0 : address1;
	//choose channel For Volume
	unsigned addressV = channel == 0 ? address00 : address11;
       
	//--------------------------------------------------------	
	//mapp channel address for Filter

	printf("Opening /dev/mem");
        int fd = open("/dev/mem", O_RDWR);
        if (fd < 1) { perror("mem"); return -1; }

        printf("/dev/mem opened");

        unsigned pageSize = sysconf(_SC_PAGESIZE);

        unsigned offset = (address & (~(pageSize - 1)));

        printf("Mapping address for Filter\n");
        void *ptr = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);

//-----------------------------------------------------------------------
	//mapp channel address for Volume

	printf("Opening /dev/mem");
        int fdV = open("/dev/mem", O_RDWR);
        if (fdV < 1) { perror("mem"); return -1; }

        printf("/dev/mem opened");

        //unsigned pageSizeV = sysconf(_SC_PAGESIZE);

        unsigned offsetV = (addressV & (~(pageSize - 1)));

        printf("Mapping address for Volume\n");
        void *ptrV = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fdV, offsetV);
//-----------------------------------------------------------------------------
	//Map OLED address
	printf("Opening /dev/mem");
        int fdL = open("/dev/mem", O_RDWR);
        if (fdL < 1) { perror("mem"); return -1; }

        printf("/dev/mem opened");
	unsigned address2 = 0x43C50000;
	unsigned offset1 = (address2 & (~(pageSize - 1)));
	void *ptr1 = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fdL, offset1);
//------------------------------------------------------------------------------------
// Write volume to registers
        SLV_REG_0V = volume;
        SLV_REG_1V = volume;
//------------------------------------------------------------------------------
  
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
//-----------------------------------------------------
	
//-------Reserve (export) the GPIO--------------///////
	int fp;
	char buf[100]; 
	int gpio = 224;
	lseek(fp, 0, SEEK_SET);
	fp = open("/sys/class/gpio/export", O_WRONLY);

	sprintf(buf, "%d", gpio); 

	write(fp, buf, strlen(buf));

	close(fp);
      
//------------------------------------------------------
//--------------Set the direction in the GPIO folder just created
	sprintf(buf, "/sys/class/gpio/gpio%d/direction", gpio);

	fp = open(buf, O_WRONLY);
 
	// Set in direction
	write(fp, "in", 2); 

	close(fp);

//-------------------------------------------------------
//--------In case of in direction get the current value of GPIO
	char value;

	while(1)
	{             
		oled_clear(ptr1);
		sprintf(buf, "/sys/class/gpio/gpio%d/value", gpio);

		fp = open(buf, O_RDONLY);

		read(fp, &value, 1);

 		//oled_print_message("ON", 0, ptr1) ;
		
		       SLV_REG_19 = 0;
		       SLV_REG_18 = value;
		       SLV_REG_17 = value;
			if (value== '1')
			{
				oled_print_message( "LOW", 0, ptr1) ;
			}
			else if (value== '0')
			{
				oled_print_message( "HIGH", 0, ptr1) ;
			}
		
    		
		
		close(fp);
			
	}


//=============================================
   
//==================================

fp = open("/sys/class/gpio/unexport", O_WRONLY);

	sprintf(buf, "%d", gpio);

	write(fp, buf, strlen(buf));

	close(fp); 

//---------------------------------------------
    

       //unmap for Filter
        munmap(ptr, pageSize);

	//unmap for Volume
        munmap(ptrV, pageSize);
	//unmap for OLED

	munmap(ptr1, pageSize);
//-----------------------------------------------
	
//-------------------------------------------------
          
    }
    return 0;
}
