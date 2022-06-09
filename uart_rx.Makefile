DRV = stm8_drv
BUILD_DIR = build

CPPFLAGS += -I.
CPPFLAGS += -I$(DRV)

include $(DRV)/Makefile.defs

CFLAGS += -DSTM8S003F3

TARGET = uart_rx

CSRCS = uart_rx.c

LIBS_CSRCS = \
	$(DRV)/drv/uart1_rx.c \
	$(DRV)/drv/uart1_tx.c

include $(DRV)/Makefile.rules

clean:
	rm $(BUILD_DIR) -rf
