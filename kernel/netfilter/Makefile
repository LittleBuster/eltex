CURRENT = $(shell uname -r)
KDIR = /lib/modules/$(CURRENT)/build
PWD = $(shell pwd)
DEST = /lib/modules/$(CURRENT)/misc
EXTRA_CFLAGS += -std=gnu99
	
TARGET1 = my
obj-m := $(TARGET1).o 
	
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm *.o my.ko
