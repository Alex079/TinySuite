#ifndef TinyBufferConst_h
#define TinyBufferConst_h

#define TINY_UART_BUFFER_SIZE 16
#define TINY_UART_BUFFER_MASK 15
#define next_buffer_index(p) ((p+1) & TINY_UART_BUFFER_MASK)

#endif