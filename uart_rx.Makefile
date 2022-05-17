DRV = stm8_drv
OBJ_DIR = obj

CPPFLAGS += -I.
CPPFLAGS += -I$(DRV)

include $(DRV)/Makefile.defs

CFLAGS += -DSTM8S003F3P6

TARGET = uart_rx
CSRCS = \
		$(DRV)/drv/uart1.c \
		uart_rx.c

include $(DRV)/Makefile.rules

clean:
	rm $(OBJ_DIR) -rf
