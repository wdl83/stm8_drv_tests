DRV = stm8_drv
BUILD_DIR = build

CPPFLAGS += -I.
CPPFLAGS += -I$(DRV)

include $(DRV)/Makefile.defs

CFLAGS += -DSTM8S003F3

TARGET = timer4

CSRCS = timer4.c

LIBS_CSRCS = \
		$(DRV)/drv/tim4.c \
		$(DRV)/drv/uart1_async_tx.c

include $(DRV)/Makefile.rules

clean:
	rm $(BUILD_DIR) -rf
