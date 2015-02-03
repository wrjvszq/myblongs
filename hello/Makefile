obj-m := hello.o

DIRS := /smbshare/linux-2.6.39/
all:
	make -C $(DIRS) M=$(PWD) modules
clean:
	rm -Rf *.o *.ko *.mod.c *.order *.symvers 
