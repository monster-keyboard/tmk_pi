KERNEL_DIR:=/usr/src/linux-headers-4.14.62-v7+
FILE=
obj-m:=g_hid.o
default:
	$(MAKE) -C /usr/src/linux-headers-$(shell uname -r) SUBDIRS=$(PWD) modules
nkro:
	OPT_DEFS += -DUSE_NKRO
	$(MAKE) -C /usr/src/linux-headers-$(shell uname -r) SUBDIRS=$(PWD) modules
install:
	cp ./g_hid.ko /lib/modules/$(shell uname -r)/kernel/drivers/usb/gadget/legacy
clean:
	$(RM) .*.cmd *.mod.c *.o *.ko -r .tmp modules.order  Module.symvers
