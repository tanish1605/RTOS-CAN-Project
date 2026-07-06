.syntax unified
.cpu cortex-m3
.thumb

.section .isr_vector

.global g_pfnVectors

g_pfnVectors:
    .word _estack
    .word Reset_Handler

.text
.global Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
    bl main

1:
    b 1b