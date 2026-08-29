MEMORY
{
  page0  (rw) : ORIGIN = 0x0000, LENGTH = 0x0100
  eeprom (rw) : ORIGIN = 0x0800, LENGTH = 0x0800
  /* 0x2000/0x2001 are reserved for the NoICE BDM Virtual UART. */
  data   (rw) : ORIGIN = 0x2002, LENGTH = 0x1FFE
  text   (rx) : ORIGIN = 0x4000, LENGTH = 0x4000
}

PROVIDE (_stack = 0x4000);
