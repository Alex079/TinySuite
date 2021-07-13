#ifndef TinyUartConst_h
#define TinyUartConst_h

#define TINY_UART_HALF_BIT_CLK         2
#define TINY_UART_ONE_BIT_CLK          3
#define TINY_UART_ONE_AND_HALF_BIT_CLK 5

#define TINY_UART_STATE_IDLE  0
#define TINY_UART_STATE_START 1
// ... data bit states in between
#define TINY_UART_STATE_STOP 10

#endif