obj-m += upas.o
CFLAGS_upas.o := -DDEBUG
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
ins:
	sudo insmod upas.ko
	sudo mknod /dev/unkill c 113 0
	sudo chmod 666 /dev/unkill

rem:
	sudo rmmod upas
	sudo rm /dev/unkill

