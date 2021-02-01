obj-m+=DD.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) main.c -o main -lssl -lcrypto
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm DD.ko main DD.mod.o DD.o
