#include <drv/clk.h>
#include <drv/uart1_rx.h>
#include <drv/uart1_tx.h>

void main(void)
{
    /* at startup master clock source is HSI / 8 (16MHz / 8 = 2MHz) */
    CLK_SWCR |= M1(SWEN);
    CLK_SWR = HSE_SRC;

    /* wait for clock source to switch */
    while((CLK_SWCR & M1(SWBSY)) || HSE_SRC != CLK_CMSR) {}

    UART1_BR(CALC_BR(CPU_CLK, 19200));
    UART1_PARITY_EVEN();
    UART1_TX_ENABLE();

    uart1_send_str(__FILE__ "\n");

    for(;;)
    {
        char buf[32];
        char *end = uart1_recv_str(buf, buf + sizeof(buf), '\r');
        uart1_send_str("recv:");
        uart1_send_str_r(buf, end);
        uart1_send_str("\n");
    }
}
