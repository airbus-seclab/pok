
CFLAGS	=	$(CONFIG_CFLAGS) -nostdinc -iwithprefix include -fno-builtin -DPOK_ARCH_PPC $(KIND_CFLAGS) $(GENERIC_FLAGS) -Wall -g -O -Wuninitialized

CFLAGS += -fno-stack-protector

CFLAGS += \
	-mno-mfcrf \
	-mno-fprnd \
	-mno-mfpgpr \
	-mno-hard-dfp \
	-mno-popcntb \
	-mno-popcntd \
	-mno-cmpb \
	-msoft-float

#LDFLAGS	=	-m $(ELF_MODE)
