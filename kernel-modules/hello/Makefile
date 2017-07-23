obj-m += hello-1.o
obj-m += hello-2.o
obj-m += hello-3.o
obj-m += hello-4.o
obj-m += hello-5.o
obj-m += startstop.o
startstop-objs := start.o stop.o
# obj-m += procfs1.o
# obj-m += procfs2.o
# obj-m += procfs3.o

obj-m += lel.o

obj-m += hue.o
hue-objs := chardev.o

# obj-m += print_string.o
# obj-m += kbleds.o
# obj-m += sched.o
# obj-m += intrpt.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc ioctl.c -o ioctl

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -vf ioctl
