// #include "uart.h"

// #define UART0_BASE 0x40004000UL

// #define UART_DR (*(volatile unsigned int *)(UART0_BASE + 0x000))
// #define UART_FR (*(volatile unsigned int *)(UART0_BASE + 0x018))
// #define UART_CR (*(volatile unsigned int *)(UART0_BASE + 0x030))

// void uart_init(void)
// {

// }

// void uart_putchar(char c)
// {
//     while (UART_FR & (1 << 5))
//     {
//     }

//     UART_DR = c;
// }

// void uart_puts(const char *str)
// {
//     while (*str)
//     {
//         uart_putchar(*str++);
//     }
// }

#include <stdio.h>

#include "uart.h"

void uart_init(void)
{
    printf("[UART] Initialized\n");
}

void uart_write_char(char c)
{
    putchar(c);
}

void uart_write_string(const char *str)
{
    while (*str)
    {
        uart_write_char(*str++);
    }
}