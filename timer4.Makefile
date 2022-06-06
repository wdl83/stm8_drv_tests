DRV = stm8_drv
OBJ_DIR = obj

CPPFLAGS += -I.
CPPFLAGS += -I$(DRV)

include $(DRV)/Makefile.defs

CFLAGS += -DSTM8S003F3P6

TARGET = timer4
CSRCS = \
		$(DRV)/drv/tim4.c \
		$(DRV)/drv/uart1.c \
		timer4.c

include $(DRV)/Makefile.rules

clean:
	rm $(OBJ_DIR) -rf
