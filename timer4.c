#include <drv/clk.h>
#include <drv/tim4.h>
#include <drv/uart1.h>

char buf[] =  __FILE__ "\n";
uint8_t cnt = 0;

void timer_cb(uintptr_t user_data)
{
    /* every ~1ms */
    (void)user_data;
    TIM4_INT_CLEAR();
    /* every ~255ms (~4x/s) */
    if(0 == cnt) uart1_async_send(buf, buf + sizeof(buf), NULL, 0);
    ++cnt;
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

    tim4_cb(timer_cb, 0);

    TIM4_AUTO_RELOAD_PRELOAD_ENABLE();
    TIM4_INT_ENABLE();
    TIM4_INT_CLEAR();
    // 8MHz / 128 = 62500 (62,5kHz) === 16us
    TIM4_CLK_DIV_128();
    TIM4_WR_CNTR(0);
    // 62 x 16us = ~1ms period
    TIM4_WR_TOP(62);
    TIM4_ENABLE();

    INTERRUPT_ENABLE();

    for(;;) {}
}
