#ifndef DG128_REGISTERS_H
#define DG128_REGISTERS_H

/* Minimal MC9S12DG128 register definitions used by the bring-up image. */
#define REG8(address) (*(volatile unsigned char *)(address))
#define REG16(address) (*(volatile unsigned short *)(address))

#define INITRM  REG8(0x0010)
#define PORTA   REG8(0x0000)
#define DDRA    REG8(0x0002)
#define PPAGE   REG8(0x0030)
#define SYNR    REG8(0x0034)
#define REFDV   REG8(0x0035)
#define CRGFLG  REG8(0x0037)
#define CLKSEL  REG8(0x0039)

#define TIOS    REG8(0x0040)
#define TCNT    REG16(0x0044)
#define TSCR1   REG8(0x0046)
#define TIE     REG8(0x004C)
#define TSCR2   REG8(0x004D)
#define TFLG1   REG8(0x004E)
#define TC7     REG16(0x005E)

#define PWME      REG8(0x00A0)
#define PWMPOL    REG8(0x00A1)
#define PWMCLK    REG8(0x00A2)
#define PWMPRCLK  REG8(0x00A3)
#define PWMCAE    REG8(0x00A4)
#define PWMCTL    REG8(0x00A5)
#define PWMSCLA   REG8(0x00A8)
#define PWMSCLB   REG8(0x00A9)
#define PWMCNT0   REG8(0x00AC)
#define PWMCNT1   REG8(0x00AD)
#define PWMPER0   REG8(0x00B4)
#define PWMPER1   REG8(0x00B5)
#define PWMDTY0   REG8(0x00BC)
#define PWMDTY1   REG8(0x00BD)

#define PTP     REG8(0x0258)
#define DDRP    REG8(0x025A)
#define PERP    REG8(0x025C)

#define TIMER_ENABLE       0x80u
#define TIMER_FAST_FLAG    0x10u
#define TIMER_PRESCALE_32  0x05u
#define PLL_LOCKED          0x08u
#define PLL_SELECT          0x80u

#define TC7_MASK 0x80u

#define PWM0_MASK 0x01u
#define PWM1_MASK 0x02u

#endif
