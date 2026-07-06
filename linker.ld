MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 16M
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 16M
}

_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    .text :
    {
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data :
    {
        *(.data*)
    } > RAM

    .bss :
    {
        *(.bss*)
        *(COMMON)
    } > RAM
}
