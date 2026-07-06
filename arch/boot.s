.syntax unified
.cpu cortex-m3
.thumb

.global g_pfnVectors
.global Reset_Handler
.global Default_Handler

.extern main

/* Vector Table ----------------------------------------------------------*/
.section .isr_vector,"a",%progbits

g_pfnVectors:
    .word _estack                /* Initial Stack Pointer */
    .word Reset_Handler          /* Reset Handler */
    .word Default_Handler        /* NMI */
    .word Default_Handler        /* HardFault */
    .word Default_Handler        /* MemManage */
    .word Default_Handler        /* BusFault */
    .word Default_Handler        /* UsageFault */
    .word 0
    .word 0
    .word 0
    .word 0
    .word Default_Handler        /* SVCall */
    .word Default_Handler        /* Debug Monitor */
    .word 0
    .word Default_Handler        /* PendSV */
    .word Default_Handler        /* SysTick */

/* Code ------------------------------------------------------------------*/
.section .text.Reset_Handler
.type Reset_Handler,%function

Reset_Handler:
    bl main

LoopForever:
    b LoopForever

.type Default_Handler,%function
Default_Handler:
    b Default_Handler