MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
  ER_IROM1 : {
    *(RESET)
    *(.text*)
    *(.rodata*)
    . = ALIGN(4);
  } > FLASH

  RW_IRAM1 : {
    *(.data*)
    . = ALIGN(4);
  } > RAM AT > FLASH

  RW_IRAM1 : {
    *(STACK)
    *(HEAP)
    *(.bss*)
    . = ALIGN(4);
  } > RAM
}

ENTRY(Reset_Handler)