DRV = stm8_drv
BUILD_DIR = build

CPPFLAGS += -I.
CPPFLAGS += -I$(DRV)

include $(DRV)/Makefile.defs

CFLAGS += \
	-DSTM8S003F3 \
	-DUART_DBG_CNTRS

TARGET = uart_irq

CSRCS = uart_irq.c

LIBS_CSRCS = \
	$(DRV)/drv/uart1_async_rx.c \
	$(DRV)/drv/uart1_async_tx.c \
	$(DRV)/drv/uart1_dbg.c \
	$(DRV)/drv/uart1_tx.c \
	$(DRV)/drv/util.c

include $(DRV)/Makefile.rules

clean:
	rm $(BUILD_DIR) -rf
