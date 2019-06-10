KERNEL_DIR:=/usr/src/linux-headers-4.14.62-v7+
obj-m:=g_hid.o
default:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
clean:
	$(RM) .*.cmd *.mod.c *.o *.ko -r .tmp
