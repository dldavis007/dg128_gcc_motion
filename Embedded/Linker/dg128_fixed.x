OUTPUT_FORMAT("elf32-m68hc12")
OUTPUT_ARCH(m68hc12)
ENTRY(_start)

MEMORY
{
  page0  (rw) : ORIGIN = 0x0000, LENGTH = 0x0100
  eeprom (rw) : ORIGIN = 0x0800, LENGTH = 0x0800
  /* 0x2000/0x2001 are reserved for the NoICE BDM Virtual UART. */
  data   (rw) : ORIGIN = 0x2002, LENGTH = 0x1FFE
  text   (rx) : ORIGIN = 0x4000, LENGTH = 0x4000
}

PROVIDE (_stack = 0x4000);
PROVIDE (vectors_addr = 0xff80);

SECTIONS
{
  .page0 :
  {
    *(.page0)
  } > page0

  .text :
  {
    KEEP (*(.install0))
    KEEP (*(.install1))
    KEEP (*(.install2))
    KEEP (*(.install3))
    KEEP (*(.install4))
    *(.init)
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    *(.tramp)
    *(.tramp.*)
    KEEP (*(.fini0))
    KEEP (*(.fini1))
    KEEP (*(.fini2))
    KEEP (*(.fini3))
    KEEP (*(.fini4))
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    *(.eh_frame)
    *(.gcc_except_table)
    KEEP (*(.ctors))
    KEEP (*(.dtors))
    . = ALIGN(2);
    _etext = .;
    PROVIDE (etext = .);
  } > text

  __data_image = .;
  PROVIDE (__data_image = .);

  .data : AT (__data_image)
  {
    __data_section_start = .;
    PROVIDE (__data_section_start = .);
    *(.sdata)
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
    . = ALIGN(2);
    _edata = .;
    PROVIDE (edata = .);
  } > data

  __data_section_size = SIZEOF(.data);
  PROVIDE (__data_section_size = SIZEOF(.data));
  __data_image_end = __data_image + __data_section_size;

  .bss :
  {
    __bss_start = .;
    *(.softregs)
    *(.sbss)
    *(.scommon)
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(2);
    _end = .;
    PROVIDE (end = .);
  } > data

  __bss_size = SIZEOF(.bss);
  PROVIDE (__bss_size = SIZEOF(.bss));

  .eeprom :
  {
    *(.eeprom)
    *(.eeprom.*)
  } > eeprom

  .vectors 0xff80 :
  {
    KEEP (*(.vectors))
  }

  .debug          0 : { *(.debug) }
  .debug_info     0 : { *(.debug_info) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_ranges   0 : { *(.debug_ranges) }
  .stab           0 : { *(.stab) }
  .stabstr        0 : { *(.stabstr) }
  .comment        0 : { *(.comment) }
}
