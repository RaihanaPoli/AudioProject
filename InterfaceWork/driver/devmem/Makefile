
# CC is a variable to specify the compiler to be used. By default it would be cc, but as we are cross-compiling
# we should specify another compiler for that. Therefore we can redefine it to take $CROSS_COMPILE variable into account which
# we will be specifying when running make. Example: make CROSS_COMPILE=arm-xilinx-linux-gnueabi-
# At this point it is only necessary for compiling the userspace program
CC=$(CROSS_COMPILE)gcc
 
all:
	make -C ../../../linux-digilent/ M=$(PWD) modules
# let's compile the userspace program
	$(CC) devmem.c udpclient.c -o devmem -pthread
	$(CC) AudioFilter.c  ZedboardOLED.c  -o AudioFilter
	
 
clean:
	make -C ../../../linux-digilent/ M=$(PWD) clean
