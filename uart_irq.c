#include <stddef.h>
#include <string.h>

#include <drv/clk.h>
#include <drv/uart1_async_rx.h>
#include <drv/uart1_async_tx.h>
#include <drv/uart1_dbg.h>
#include <drv/uart1_tx.h>

bool rx_pred(const uint8_t *, uintptr_t);
void tx_cb(uintptr_t);
void rx_cb(uint8_t *, const uint8_t *, uart_rxflags_t *, uintptr_t);

char buf[] = __FILE__ "\n";

bool rx_pred(const uint8_t *curr, uintptr_t user_data)
{
    (void)user_data;
    return curr && ('\r' == *curr || '\n' == *curr);
}

void tx_cb(uintptr_t user_data)
{
    memset(buf, 0, sizeof(buf));
    uart1_async_recv(buf, buf + sizeof(buf), rx_pred, rx_cb, user_data);
}

void rx_cb(
    uint8_t *begin, const uint8_t *end,
    uart_rxflags_t *flags,
    uintptr_t user_data)
{
    if(!flags) return;

    if(flags->errors.fopn)
    {
        uart_rxflags_str_t str;
        uart_rxflags_str(str, flags);
        uart1_send_str(str);
    }
    else
    {
        flags->value = 0;
        uart1_async_send(begin, end, tx_cb, user_data);
    }
}

void main(void)
{
    /* at startup master clock source is HSI / 8 (16MHz / 8 = 2MHz) */
    CLK_SWCR |= M1(SWEN);
    CLK_SWR = HSE_SRC;

    /* wait for clock source to switch */
    while((CLK_SWCR & M1(SWBSY)) || HSE_SRC != CLK_CMSR) {}

    UART1_BR(CALC_BR(CPU_CLK, 19200));
    UART1_PARITY_EVEN();

    INTERRUPT_ENABLE();
    uart1_async_send(buf, buf + sizeof(buf), tx_cb, 0);

    for(;;) {}
}
