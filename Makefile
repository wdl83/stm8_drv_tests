MKFS = \
	   uart_tx.Makefile \
	   uart_rx.Makefile \
	   uart_irq.Makefile

all: $(MKFS)
	make -f uart_tx.Makefile
	make -f uart_rx.Makefile
	make -f uart_irq.Makefile

clean: $(MKFS) 
	make -f uart_tx.Makefile clean
	make -f uart_rx.Makefile clean
	make -f uart_irq.Makefile clean
