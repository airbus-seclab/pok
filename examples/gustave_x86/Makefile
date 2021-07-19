export ARCH=x86
export BSP=x86-qemu
export POK_CONFIG_OPTIMIZE_FOR_GENERATED_CODE=1

export POK_PATH=$(shell realpath $(shell pwd)/../..)

ifeq ($(AFL_POK_COV),src)
export AFLGCC=$(AFL_PATH)/afl-gcc
export AFL_CC=$(shell which x86_64-linux-gnu-gcc)
export AFL_AS=$(shell which x86_64-linux-gnu-as)
endif

include $(POK_PATH)/misc/mk/config.mk
include $(POK_PATH)/misc/mk/common-$(ARCH).mk

TARGET=$(shell pwd)/pok.elf
PARTITIONS= part1/part1.elf part2/part2.elf
KERNEL=kernel/kernel.lo

all: cleanconf firmware

firmware: pok

pok: build-kernel partitions $(TARGET)

build-kernel:
	$(CD) kernel && $(MAKE)

p1:
	$(CD) part1 && $(MAKE)
p2:
	$(CD) part2 && $(MAKE)

partitions: p1 p2

clean: common-clean
	$(CD) kernel && $(MAKE) clean
	$(CD) part1 && $(MAKE) clean
	$(CD) part2 && $(MAKE) clean

cleanconf:
	$(RM) $(POK_PATH)/misc/mk/config.mk

distclean: clean
	$(CD) kernel && $(MAKE) distclean
	$(CD) part1 && $(MAKE) distclean
	$(CD) part2 && $(MAKE) distclean


include $(POK_PATH)/misc/mk/rules-common.mk
include $(POK_PATH)/misc/mk/rules-main.mk
include $(POK_PATH)/misc/mk/install-rules.mk
