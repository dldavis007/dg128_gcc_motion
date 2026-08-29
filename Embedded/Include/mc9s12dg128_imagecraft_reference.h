/* mc9s12dg128.h
** Copyright (C) 2005 ImageCraft Creations Inc. 
** V1.0 Created November, 3 2005
*/
 
#ifndef __mc9s12dg128_H
#define __mc9s12dg128_H


/*  bit masks
 */
#define       BIT0	0x1
#define       BIT1	0x2
#define       BIT2	0x4
#define       BIT3	0x8
#define       BIT4	0x10
#define       BIT5	0x20
#define       BIT6	0x40
#define       BIT7	0x80




#define REG_BASE  	0x0000
#define VReserved63	0x0000FF80
#define VReserved62	0x0000FF82
#define VReserved61	0x0000FF84
#define VReserved60	0x0000FF86
#define VReserved59	0x0000FF88
#define VReserved58	0x0000FF8A
#define Vpwmesdn  	0x0000FF8C
#define Vportp    	0x0000FF8E
#define Vcan4tx   	0x0000FF90
#define Vcan4rx   	0x0000FF92
#define Vcan4err  	0x0000FF94
#define Vcan4wkup 	0x0000FF96
#define VReserved51	0x0000FF98
#define VReserved50	0x0000FF9A
#define VReserved49	0x0000FF9C
#define VReserved48	0x0000FF9E
#define VReserved47	0x0000FFA0
#define VReserved46	0x0000FFA2
#define VReserved45	0x0000FFA4
#define VReserved44	0x0000FFA6
#define VReserved43	0x0000FFA8
#define VReserved42	0x0000FFAA
#define VReserved41	0x0000FFAC
#define VReserved40	0x0000FFAE
#define Vcan0tx   	0x0000FFB0
#define Vcan0rx   	0x0000FFB2
#define Vcan0err  	0x0000FFB4
#define Vcan0wkup 	0x0000FFB6
#define Vflash    	0x0000FFB8
#define Veeprom   	0x0000FFBA
#define VReserved33	0x0000FFBC
#define Vspi1     	0x0000FFBE
#define Viic      	0x0000FFC0
#define VReserved30	0x0000FFC2
#define Vcrgscm   	0x0000FFC4
#define Vcrgplllck	0x0000FFC6
#define Vtimpabovf	0x0000FFC8
#define Vtimmdcu  	0x0000FFCA
#define Vporth    	0x0000FFCC
#define Vportj    	0x0000FFCE
#define Vatd1     	0x0000FFD0
#define Vatd0     	0x0000FFD2
#define Vsci1     	0x0000FFD4
#define Vsci0     	0x0000FFD6
#define Vspi0     	0x0000FFD8
#define Vtimpaie  	0x0000FFDA
#define Vtimpaaovf	0x0000FFDC
#define Vtimovf   	0x0000FFDE
#define Vtimch7   	0x0000FFE0
#define Vtimch6   	0x0000FFE2
#define Vtimch5   	0x0000FFE4
#define Vtimch4   	0x0000FFE6
#define Vtimch3   	0x0000FFE8
#define Vtimch2   	0x0000FFEA
#define Vtimch1   	0x0000FFEC
#define Vtimch0   	0x0000FFEE
#define Vrti      	0x0000FFF0
#define Virq      	0x0000FFF2
#define Vxirq     	0x0000FFF4
#define Vswi      	0x0000FFF6
#define Vtrap     	0x0000FFF8
#define Vcop      	0x0000FFFA
#define Vclkmon   	0x0000FFFC
#define Vreset    	0x0000FFFE

#define PORTAB	(*(volatile unsigned *)(REG_BASE + 0x00000000))
#define DDRAB	(*(volatile unsigned *)(REG_BASE + 0x00000002))
#define PORTA	(*(volatile unsigned char *)(REG_BASE + 0x00000000))
#define PORTB	(*(volatile unsigned char *)(REG_BASE + 0x00000001))
#define DDRA	(*(volatile unsigned char *)(REG_BASE + 0x00000002))
#define DDRB	(*(volatile unsigned char *)(REG_BASE + 0x00000003))
#define PORTE	(*(volatile unsigned char *)(REG_BASE + 0x00000008))
#define DDRE	(*(volatile unsigned char *)(REG_BASE + 0x00000009))
#define PEAR	(*(volatile unsigned char *)(REG_BASE + 0x0000000A))

#define RDWE      	0x4
#define LSTRE     	0x8
#define NECLK     	0x10
#define PIPOE     	0x20
#define NOACCE    	0x80

#define MODE	(*(volatile unsigned char *)(REG_BASE + 0x0000000B))

#define EME       	0x1
#define EMK       	0x2
#define IVIS      	0x8
#define MODA      	0x20
#define MODB      	0x40
#define MODC      	0x80
#define MOD       	0xe0

#define PUCR	(*(volatile unsigned char *)(REG_BASE + 0x0000000C))

#define PUPAE     	0x1
#define PUPBE     	0x2
#define PUPEE     	0x10
#define PUPKE     	0x80

#define RDRIV	(*(volatile unsigned char *)(REG_BASE + 0x0000000D))

#define RDPA      	0x1
#define RDPB      	0x2
#define RDPE      	0x10
#define RDPK      	0x80
#define RDPx      	0x3

#define EBICTL	(*(volatile unsigned char *)(REG_BASE + 0x0000000E))

#define ESTR      	0x1

#define INITRM	(*(volatile unsigned char *)(REG_BASE + 0x00000010))

#define RAMHAL    	0x1
#define RAM11     	0x8
#define RAM12     	0x10
#define RAM13     	0x20
#define RAM14     	0x40
#define RAM15     	0x80
#define RAM_11    	0xf8

#define INITRG	(*(volatile unsigned char *)(REG_BASE + 0x00000011))

#define REG11     	0x8
#define REG12     	0x10
#define REG13     	0x20
#define REG14     	0x40
#define REG_11    	0x78

#define INITEE	(*(volatile unsigned char *)(REG_BASE + 0x00000012))

#define EEON      	0x1
#define EE12      	0x10
#define EE13      	0x20
#define EE14      	0x40
#define EE15      	0x80
#define EE_12     	0xf0

#define MISC	(*(volatile unsigned char *)(REG_BASE + 0x00000013))

#define ROMON     	0x1
#define ROMHM     	0x2
#define EXSTR0    	0x4
#define EXSTR1    	0x8
#define EXSTR     	0xc

#define MTST0	(*(volatile unsigned char *)(REG_BASE + 0x00000014))
#define ITCR	(*(volatile unsigned char *)(REG_BASE + 0x00000015))

#define ADR0      	0x1
#define ADR1      	0x2
#define ADR2      	0x4
#define ADR3      	0x8
#define WRTINT    	0x10
#define ADR       	0xf

#define ITEST	(*(volatile unsigned char *)(REG_BASE + 0x00000016))

#define INT0      	0x1
#define INT2      	0x2
#define INT4      	0x4
#define INT6      	0x8
#define INT8      	0x10
#define INTA      	0x20
#define INTC      	0x40
#define INTE      	0x80

#define MTST1	(*(volatile unsigned char *)(REG_BASE + 0x00000017))
#define PARTIDH	(*(volatile unsigned char *)(REG_BASE + 0x0000001A))

#define ID15      	0x1
#define ID14      	0x2
#define ID13      	0x4
#define ID12      	0x8
#define ID11      	0x10
#define ID10      	0x20
#define ID9       	0x40
#define ID8       	0x80

#define PARTIDL	(*(volatile unsigned char *)(REG_BASE + 0x0000001B))

#define ID0       	0x1
#define ID1       	0x2
#define ID2       	0x4
#define ID3       	0x8
#define ID4       	0x10
#define ID5       	0x20
#define ID6       	0x40
#define ID7       	0x80
//#define ID        	0xff

#define MEMSIZ0	(*(volatile unsigned char *)(REG_BASE + 0x0000001C))

#define sw0       	0x1
#define sw1       	0x2
#define sw2       	0x4

/* duplicate resolved by name mangling -- prepend MEMSIZ0_eep */
#define MEMSIZ0_eep_sw0	0x10

/* duplicate resolved by name mangling -- prepend MEMSIZ0_eep */
#define MEMSIZ0_eep_sw1	0x20

/* duplicate resolved by name mangling -- prepend MEMSIZ0_reg */
#define MEMSIZ0_reg_sw0	0x80
#define sw        	0x7

/* duplicate resolved by name mangling -- prepend MEMSIZ0_eep */
#define MEMSIZ0_eep_sw	0x30

#define MEMSIZ1	(*(volatile unsigned char *)(REG_BASE + 0x0000001D))

/* duplicate resolved by name mangling -- prepend MEMSIZ1_pag */

#define MEMSIZ1_pag_sw0	0x1

/* duplicate resolved by name mangling -- prepend MEMSIZ1_pag */
#define MEMSIZ1_pag_sw1	0x2

/* duplicate resolved by name mangling -- prepend MEMSIZ1_rom */
#define MEMSIZ1_rom_sw0	0x40

/* duplicate resolved by name mangling -- prepend MEMSIZ1_rom */
#define MEMSIZ1_rom_sw1	0x80

/* duplicate resolved by name mangling -- prepend MEMSIZ1_pag */
#define MEMSIZ1_pag_sw	0x3

/* duplicate resolved by name mangling -- prepend MEMSIZ1_rom */
#define MEMSIZ1_rom_sw	0xc0

#define INTCR	(*(volatile unsigned char *)(REG_BASE + 0x0000001E))

#define IRQEN     	0x40
#define IRQE      	0x80

#define HPRIO	(*(volatile unsigned char *)(REG_BASE + 0x0000001F))

#define PSEL1     	0x2
#define PSEL2     	0x4
#define PSEL3     	0x8
#define PSEL4     	0x10
#define PSEL5     	0x20
#define PSEL6     	0x40
#define PSEL7     	0x80
#define PSEL_1    	0xfe

#define BKPCT0	(*(volatile unsigned char *)(REG_BASE + 0x00000028))

#define BKTAG     	0x10
#define BKBDM     	0x20
#define BKFULL    	0x40
#define BKEN      	0x80

#define BKPCT1	(*(volatile unsigned char *)(REG_BASE + 0x00000029))

#define BK1RW     	0x1
#define BK1RWE    	0x2
#define BK0RW     	0x4
#define BK0RWE    	0x8
#define BK1MBL    	0x10
#define BK1MBH    	0x20
#define BK0MBL    	0x40
#define BK0MBH    	0x80

#define BKP0X	(*(volatile unsigned char *)(REG_BASE + 0x0000002A))

#define BK0V0     	0x1
#define BK0V1     	0x2
#define BK0V2     	0x4
#define BK0V3     	0x8
#define BK0V4     	0x10
#define BK0V5     	0x20
#define BK0V      	0x3f

#define BKP0H	(*(volatile unsigned char *)(REG_BASE + 0x0000002B))
#define BKP0L	(*(volatile unsigned char *)(REG_BASE + 0x0000002C))
#define BKP1X	(*(volatile unsigned char *)(REG_BASE + 0x0000002D))

#define BK1V0     	0x1
#define BK1V1     	0x2
#define BK1V2     	0x4
#define BK1V3     	0x8
#define BK1V4     	0x10
#define BK1V5     	0x20
#define BK1V      	0x3f

#define BKP1H	(*(volatile unsigned char *)(REG_BASE + 0x0000002E))
#define BKP1L	(*(volatile unsigned char *)(REG_BASE + 0x0000002F))
#define PPAGE	(*(volatile unsigned char *)(REG_BASE + 0x00000030))

#define PIX0      	0x1
#define PIX1      	0x2
#define PIX2      	0x4
#define PIX3      	0x8
#define PIX4      	0x10
#define PIX5      	0x20
#define PIX       	0x3f

#define PORTK	(*(volatile unsigned char *)(REG_BASE + 0x00000032))
#define DDRK	(*(volatile unsigned char *)(REG_BASE + 0x00000033))

#define DDK0      	0x1
#define DDK1      	0x2
#define DDK2      	0x4
#define DDK3      	0x8
#define DDK4      	0x10
#define DDK5      	0x20
#define DDK7      	0x80
#define DDK       	0x3f

#define SYNR	(*(volatile unsigned char *)(REG_BASE + 0x00000034))

#define SYN0      	0x1
#define SYN1      	0x2
#define SYN2      	0x4
#define SYN3      	0x8
#define SYN4      	0x10
#define SYN5      	0x20
#define SYN       	0x3f

#define REFDV	(*(volatile unsigned char *)(REG_BASE + 0x00000035))

#define REFDV0    	0x1
#define REFDV1    	0x2
#define REFDV2    	0x4
#define REFDV3    	0x8

/* duplicate resolved by name mangling -- prepend REFDV */
#define REFDV_REFDV	0xf

#define CRGFLG	(*(volatile unsigned char *)(REG_BASE + 0x00000037))

#define SCM       	0x1
#define SCMIF     	0x2
#define TRACK     	0x4
#define LOCK      	0x8
#define LOCKIF    	0x10
#define PORF      	0x40
#define RTIF      	0x80

#define CRGINT	(*(volatile unsigned char *)(REG_BASE + 0x00000038))

#define SCMIE     	0x2
#define LOCKIE    	0x10
#define RTIE      	0x80

#define CLKSEL	(*(volatile unsigned char *)(REG_BASE + 0x00000039))

#define COPWAI    	0x1
#define RTIWAI    	0x2
#define CWAI      	0x4
#define PLLWAI    	0x8
#define ROAWAI    	0x10
#define SYSWAI    	0x20
#define PSTP      	0x40
#define PLLSEL    	0x80

#define PLLCTL	(*(volatile unsigned char *)(REG_BASE + 0x0000003A))

#define SCME      	0x1
#define ACQ       	0x10
#define AUTO      	0x20
#define PLLON     	0x40
#define CME       	0x80

#define RTICTL	(*(volatile unsigned char *)(REG_BASE + 0x0000003B))

#define RTR0      	0x1
#define RTR1      	0x2
#define RTR2      	0x4
#define RTR3      	0x8
#define RTR4      	0x10
#define RTR5      	0x20
#define RTR6      	0x40
#define RTR       	0x7f

#define COPCTL	(*(volatile unsigned char *)(REG_BASE + 0x0000003C))

#define CR0       	0x1
#define CR1       	0x2
#define CR2       	0x4
#define RSBCK     	0x40
#define WCOP      	0x80
#define CR        	0x7

#define ARMCOP	(*(volatile unsigned char *)(REG_BASE + 0x0000003F))
#define TIOS	(*(volatile unsigned char *)(REG_BASE + 0x00000040))

#define IOS0      	0x1
#define IOS1      	0x2
#define IOS2      	0x4
#define IOS3      	0x8
#define IOS4      	0x10
#define IOS5      	0x20
#define IOS6      	0x40
#define IOS7      	0x80
#define IOS       	0xff

#define CFORC	(*(volatile unsigned char *)(REG_BASE + 0x00000041))

#define FOC0      	0x1
#define FOC1      	0x2
#define FOC2      	0x4
#define FOC3      	0x8
#define FOC4      	0x10
#define FOC5      	0x20
#define FOC6      	0x40
#define FOC7      	0x80
#define FOC       	0xff

#define OC7M	(*(volatile unsigned char *)(REG_BASE + 0x00000042))

#define OC7M0     	0x1
#define OC7M1     	0x2
#define OC7M2     	0x4
#define OC7M3     	0x8
#define OC7M4     	0x10
#define OC7M5     	0x20
#define OC7M6     	0x40
#define OC7M7     	0x80

/* duplicate resolved by name mangling -- prepend OC7M */
#define OC7M_OC7M 	0xff

#define OC7D	(*(volatile unsigned char *)(REG_BASE + 0x00000043))

/* duplicate resolved by name mangling -- prepend OC7D */

#define OC7D_OC7D 	0xff

#define TCNT	(*(volatile unsigned *)(REG_BASE + 0x00000044))
#define TSCR1	(*(volatile unsigned char *)(REG_BASE + 0x00000046))

#define TFFCA     	0x10
#define TSFRZ     	0x20
#define TSWAI     	0x40
#define TEN       	0x80

#define TTOV	(*(volatile unsigned char *)(REG_BASE + 0x00000047))

#define TOV0      	0x1
#define TOV1      	0x2
#define TOV2      	0x4
#define TOV3      	0x8
#define TOV4      	0x10
#define TOV5      	0x20
#define TOV6      	0x40
#define TOV7      	0x80
#define TOV       	0xff

#define TCTL1	(*(volatile unsigned char *)(REG_BASE + 0x00000048))

#define OL4       	0x1
#define OM4       	0x2
#define OL5       	0x4
#define OM5       	0x8
#define OL6       	0x10
#define OM6       	0x20
#define OL7       	0x40
#define OM7       	0x80

#define TCTL2	(*(volatile unsigned char *)(REG_BASE + 0x00000049))

#define OL0       	0x1
#define OM0       	0x2
#define OL1       	0x4
#define OM1       	0x8
#define OL2       	0x10
#define OM2       	0x20
#define OL3       	0x40
#define OM3       	0x80

#define TCTL3	(*(volatile unsigned char *)(REG_BASE + 0x0000004A))

#define EDG4A     	0x1
#define EDG4B     	0x2
#define EDG5A     	0x4
#define EDG5B     	0x8
#define EDG6A     	0x10
#define EDG6B     	0x20
#define EDG7A     	0x40
#define EDG7B     	0x80
#define EDG4x     	0x3
#define EDG6x     	0x30

#define TCTL4	(*(volatile unsigned char *)(REG_BASE + 0x0000004B))

#define EDG0A     	0x1
#define EDG0B     	0x2
#define EDG1A     	0x4
#define EDG1B     	0x8
#define EDG2A     	0x10
#define EDG2B     	0x20
#define EDG3A     	0x40
#define EDG3B     	0x80
#define EDG0x     	0x3
#define EDG2x     	0x30

#define TIE	(*(volatile unsigned char *)(REG_BASE + 0x0000004C))

#define C0I       	0x1
#define C1I       	0x2
#define C2I       	0x4
#define C3I       	0x8
#define C4I       	0x10
#define C5I       	0x20
#define C6I       	0x40
#define C7I       	0x80

#define TSCR2	(*(volatile unsigned char *)(REG_BASE + 0x0000004D))

#define PR0       	0x1
#define PR1       	0x2
#define PR2       	0x4
#define TCRE      	0x8
#define TOI       	0x80
#define PR        	0x7

#define TFLG1	(*(volatile unsigned char *)(REG_BASE + 0x0000004E))

#define C0F       	0x1
#define C1F       	0x2
#define C2F       	0x4
#define C3F       	0x8
#define C4F       	0x10
#define C5F       	0x20
#define C6F       	0x40
#define C7F       	0x80

#define TFLG2	(*(volatile unsigned char *)(REG_BASE + 0x0000004F))

#define TOF       	0x80

#define TC0	(*(volatile unsigned *)(REG_BASE + 0x00000050))
#define TC1	(*(volatile unsigned *)(REG_BASE + 0x00000052))
#define TC2	(*(volatile unsigned *)(REG_BASE + 0x00000054))
#define TC3	(*(volatile unsigned *)(REG_BASE + 0x00000056))
#define TC4	(*(volatile unsigned *)(REG_BASE + 0x00000058))
#define TC5	(*(volatile unsigned *)(REG_BASE + 0x0000005A))
#define TC6	(*(volatile unsigned *)(REG_BASE + 0x0000005C))
#define TC7	(*(volatile unsigned *)(REG_BASE + 0x0000005E))
#define PACTL	(*(volatile unsigned char *)(REG_BASE + 0x00000060))

#define PAI       	0x1
#define PAOVI     	0x2
#define CLK0      	0x4
#define CLK1      	0x8
#define PEDGE     	0x10
#define PAMOD     	0x20
#define PAEN      	0x40
#define CLK       	0xc

#define PAFLG	(*(volatile unsigned char *)(REG_BASE + 0x00000061))

#define PAIF      	0x1
#define PAOVF     	0x2

#define PACN32	(*(volatile unsigned *)(REG_BASE + 0x00000062))
#define PACN10	(*(volatile unsigned *)(REG_BASE + 0x00000064))
#define MCCTL	(*(volatile unsigned char *)(REG_BASE + 0x00000066))

#define MCPR0     	0x1
#define MCPR1     	0x2
#define MCEN      	0x4
#define FLMC      	0x8
#define ICLAT     	0x10
#define RDMCL     	0x20
#define MODMC     	0x40
#define MCZI      	0x80
#define MCPR      	0x3

#define MCFLG	(*(volatile unsigned char *)(REG_BASE + 0x00000067))

#define POLF0     	0x1
#define POLF1     	0x2
#define POLF2     	0x4
#define POLF3     	0x8
#define MCZF      	0x80
#define POLF      	0xf

#define ICPAR	(*(volatile unsigned char *)(REG_BASE + 0x00000068))

#define PA0EN     	0x1
#define PA1EN     	0x2
#define PA2EN     	0x4
#define PA3EN     	0x8

#define DLYCT	(*(volatile unsigned char *)(REG_BASE + 0x00000069))

#define DLY0      	0x1
#define DLY1      	0x2
#define DLY       	0x3

#define ICOVW	(*(volatile unsigned char *)(REG_BASE + 0x0000006A))

#define NOVW0     	0x1
#define NOVW1     	0x2
#define NOVW2     	0x4
#define NOVW3     	0x8
#define NOVW4     	0x10
#define NOVW5     	0x20
#define NOVW6     	0x40
#define NOVW7     	0x80
#define NOVW      	0xff

#define ICSYS	(*(volatile unsigned char *)(REG_BASE + 0x0000006B))

#define LATQ      	0x1
#define BUFEN     	0x2
#define PACMX     	0x4
#define TFMOD     	0x8
#define SH04      	0x10
#define SH15      	0x20
#define SH26      	0x40
#define SH37      	0x80

#define PBCTL	(*(volatile unsigned char *)(REG_BASE + 0x00000070))

#define PBOVI     	0x2
#define PBEN      	0x40

#define PBFLG	(*(volatile unsigned char *)(REG_BASE + 0x00000071))

#define PBOVF     	0x2

#define PA32H	(*(volatile unsigned *)(REG_BASE + 0x00000072))
#define PA10H	(*(volatile unsigned *)(REG_BASE + 0x00000074))
#define MCCNT	(*(volatile unsigned *)(REG_BASE + 0x00000076))
#define TC0H	(*(volatile unsigned *)(REG_BASE + 0x00000078))
#define TC1H	(*(volatile unsigned *)(REG_BASE + 0x0000007A))
#define TC2H	(*(volatile unsigned *)(REG_BASE + 0x0000007C))
#define TC3H	(*(volatile unsigned *)(REG_BASE + 0x0000007E))
#define ATD0CTL23	(*(volatile unsigned *)(REG_BASE + 0x00000082))

#define ATD0CTL2	(*(volatile unsigned char*)(REG_BASE + 0x00000082))
#define ATD0CTL3	(*(volatile unsigned char*)(REG_BASE + 0x00000083))


#define FRZ0      	0x1
#define FRZ1      	0x2
#define FIFO      	0x4
#define S1C       	0x8
#define S2C       	0x10
#define S4C       	0x20
#define S8C       	0x40
#define ASCIF     	0x100
#define ASCIE     	0x200
#define ETRIGE    	0x400
#define ETRIGP    	0x800
#define ETRIGLE   	0x1000
#define AWAI      	0x2000
#define AFFC      	0x4000
#define ADPU      	0x8000
#define FRZ       	0x3

#define ATD0CTL45	(*(volatile unsigned *)(REG_BASE + 0x00000084))

#define ATD0CTL4	(*(volatile unsigned char*)(REG_BASE + 0x00000084))
#define ATD0CTL5	(*(volatile unsigned char*)(REG_BASE + 0x00000085))

#define CA        	0x1
#define CB        	0x2
#define CC        	0x4
#define MULT      	0x10
#define SCAN      	0x20
#define DSGN      	0x40
#define DJM       	0x80
#define PRS0      	0x100
#define PRS1      	0x200
#define PRS2      	0x400
#define PRS3      	0x800
#define PRS4      	0x1000
#define SMP0      	0x2000
#define SMP1      	0x4000
#define SRES8     	0x8000
#define Cx        	0x7
#define PRS       	0x1f00
#define SMP       	0x6000

#define ATD0STAT0	(*(volatile unsigned char *)(REG_BASE + 0x00000086))

#define CC0       	0x1
#define CC1       	0x2
#define CC2       	0x4
#define FIFOR     	0x10
#define ETORF     	0x20
#define SCF       	0x80

/* duplicate resolved by name mangling -- prepend ATD0STAT0 */
#define ATD0STAT0_CC	0x7

#define ATD0STAT1	(*(volatile unsigned char *)(REG_BASE + 0x0000008B))

#define CCF0      	0x1
#define CCF1      	0x2
#define CCF2      	0x4
#define CCF3      	0x8
#define CCF4      	0x10
#define CCF5      	0x20
#define CCF6      	0x40
#define CCF7      	0x80
#define CCF       	0xff

#define ATD0DIEN	(*(volatile unsigned char *)(REG_BASE + 0x0000008D))
#define PORTAD0	(*(volatile unsigned char *)(REG_BASE + 0x0000008F))
#define ATD0DR0	(*(volatile unsigned *)(REG_BASE + 0x00000090))
#define ATD0DR1	(*(volatile unsigned *)(REG_BASE + 0x00000092))
#define ATD0DR2	(*(volatile unsigned *)(REG_BASE + 0x00000094))
#define ATD0DR3	(*(volatile unsigned *)(REG_BASE + 0x00000096))
#define ATD0DR4	(*(volatile unsigned *)(REG_BASE + 0x00000098))
#define ATD0DR5	(*(volatile unsigned *)(REG_BASE + 0x0000009A))
#define ATD0DR6	(*(volatile unsigned *)(REG_BASE + 0x0000009C))
#define ATD0DR7	(*(volatile unsigned *)(REG_BASE + 0x0000009E))
#define PWME	(*(volatile unsigned char *)(REG_BASE + 0x000000A0))

#define PWME0     	0x1
#define PWME1     	0x2
#define PWME2     	0x4
#define PWME3     	0x8
#define PWME4     	0x10
#define PWME5     	0x20
#define PWME6     	0x40
#define PWME7     	0x80

/* duplicate resolved by name mangling -- prepend PWME */
#define PWME_PWME 	0xff

#define PWMPOL	(*(volatile unsigned char *)(REG_BASE + 0x000000A1))

#define PPOL0     	0x1
#define PPOL1     	0x2
#define PPOL2     	0x4
#define PPOL3     	0x8
#define PPOL4     	0x10
#define PPOL5     	0x20
#define PPOL6     	0x40
#define PPOL7     	0x80
#define PPOL      	0xff

#define PWMCLK	(*(volatile unsigned char *)(REG_BASE + 0x000000A2))

#define PCLK0     	0x1
#define PCLK1     	0x2
#define PCLK2     	0x4
#define PCLK3     	0x8
#define PCLK4     	0x10
#define PCLK5     	0x20
#define PCLK6     	0x40
#define PCLK7     	0x80
#define PCLK      	0xff

#define PWMPRCLK	(*(volatile unsigned char *)(REG_BASE + 0x000000A3))

#define PCKA0     	0x1
#define PCKA1     	0x2
#define PCKA2     	0x4
#define PCKB0     	0x10
#define PCKB1     	0x20
#define PCKB2     	0x40
#define PCKA      	0x7
#define PCKB      	0x70

#define PWMCAE	(*(volatile unsigned char *)(REG_BASE + 0x000000A4))

#define CAE0      	0x1
#define CAE1      	0x2
#define CAE2      	0x4
#define CAE3      	0x8
#define CAE4      	0x10
#define CAE5      	0x20
#define CAE6      	0x40
#define CAE7      	0x80
#define CAE       	0xff

#define PWMCTL	(*(volatile unsigned char *)(REG_BASE + 0x000000A5))

#define PFRZ      	0x4
#define PSWAI     	0x8
#define CON01     	0x10
#define CON23     	0x20
#define CON45     	0x40
#define CON67     	0x80

#define PWMSCLA	(*(volatile unsigned char *)(REG_BASE + 0x000000A8))
#define PWMSCLB	(*(volatile unsigned char *)(REG_BASE + 0x000000A9))
#define PWMCNT01	(*(volatile unsigned *)(REG_BASE + 0x000000AC))
#define PWMCNT23	(*(volatile unsigned *)(REG_BASE + 0x000000AE))
#define PWMCNT45	(*(volatile unsigned *)(REG_BASE + 0x000000B0))
#define PWMCNT67	(*(volatile unsigned *)(REG_BASE + 0x000000B2))
#define PWMPER01	(*(volatile unsigned *)(REG_BASE + 0x000000B4))
#define PWMPER23	(*(volatile unsigned *)(REG_BASE + 0x000000B6))
#define PWMPER45	(*(volatile unsigned *)(REG_BASE + 0x000000B8))
#define PWMPER67	(*(volatile unsigned *)(REG_BASE + 0x000000BA))
#define PWMDTY01	(*(volatile unsigned *)(REG_BASE + 0x000000BC))
#define PWMDTY23	(*(volatile unsigned *)(REG_BASE + 0x000000BE))
#define PWMDTY45	(*(volatile unsigned *)(REG_BASE + 0x000000C0))
#define PWMDTY67	(*(volatile unsigned *)(REG_BASE + 0x000000C2))
#define PWMSDN	(*(volatile unsigned char *)(REG_BASE + 0x000000C4))

#define PWMCNT0	(*(volatile unsigned  char *)(REG_BASE + 0x000000AC))
#define PWMCNT1	(*(volatile unsigned  char *)(REG_BASE + 0x000000AD))
#define PWMCNT2	(*(volatile unsigned  char *)(REG_BASE + 0x000000AE))
#define PWMCNT3	(*(volatile unsigned  char *)(REG_BASE + 0x000000AF))
#define PWMCNT4	(*(volatile unsigned  char *)(REG_BASE + 0x000000B0))
#define PWMCNT5 (*(volatile unsigned  char *)(REG_BASE + 0x000000B1))
#define PWMCNT6	(*(volatile unsigned  char *)(REG_BASE + 0x000000B2))
#define PWMCNT7	(*(volatile unsigned  char *)(REG_BASE + 0x000000B3))

#define PWMPER0	(*(volatile unsigned  char *)(REG_BASE + 0x000000B4))
#define PWMPER1	(*(volatile unsigned  char *)(REG_BASE + 0x000000B5))
#define PWMPER2	(*(volatile unsigned  char *)(REG_BASE + 0x000000B6))
#define PWMPER3	(*(volatile unsigned  char *)(REG_BASE + 0x000000B7))
#define PWMPER4	(*(volatile unsigned  char *)(REG_BASE + 0x000000B8))
#define PWMPER5	(*(volatile unsigned  char *)(REG_BASE + 0x000000B9))
#define PWMPER6	(*(volatile unsigned  char *)(REG_BASE + 0x000000BA))
#define PWMPER7	(*(volatile unsigned  char *)(REG_BASE + 0x000000BB))

#define PWMDTY0	(*(volatile unsigned  char *)(REG_BASE + 0x000000BC))
#define PWMDTY1	(*(volatile unsigned  char *)(REG_BASE + 0x000000BD))
#define PWMDTY2	(*(volatile unsigned  char *)(REG_BASE + 0x000000BE))
#define PWMDTY3	(*(volatile unsigned  char *)(REG_BASE + 0x000000BF))
#define PWMDTY4	(*(volatile unsigned  char *)(REG_BASE + 0x000000C0))
#define PWMDTY5	(*(volatile unsigned  char *)(REG_BASE + 0x000000C1))
#define PWMDTY6	(*(volatile unsigned  char *)(REG_BASE + 0x000000C2))
#define PWMDTY7	(*(volatile unsigned  char *)(REG_BASE + 0x000000C3))

#define PWM7ENA   	0x1
#define PWM7INL   	0x2
#define PWM7IN    	0x4
#define PWMLVL    	0x10
#define PWMRSTRT  	0x20
#define PWMIE     	0x40
#define PWMIF     	0x80

#define SCI0BD	(*(volatile unsigned *)(REG_BASE + 0x000000C8))

#define SBR0      	0x1
#define SBR1      	0x2
#define SBR2      	0x4
#define SBR3      	0x8
#define SBR4      	0x10
#define SBR5      	0x20
#define SBR6      	0x40
#define SBR7      	0x80
#define SBR8      	0x100
#define SBR9      	0x200
#define SBR10     	0x400
#define SBR11     	0x800
#define SBR12     	0x1000
#define SBR       	0x1fff

#define SCI0CR1	(*(volatile unsigned char *)(REG_BASE + 0x000000CA))

#define PT        	0x1
#define PE        	0x2
#define ILT       	0x4
#define WAKE      	0x8
#define M         	0x10
#define RSRC      	0x20
#define SCISWAI   	0x40
#define LOOPS     	0x80

#define SCI0CR2	(*(volatile unsigned char *)(REG_BASE + 0x000000CB))

#define SBK       	0x1
#define RWU       	0x2
#define RE        	0x4
#define TE        	0x8
#define ILIE      	0x10
#define RIE       	0x20
#define TCIE      	0x40
#define SCTIE     	0x80

#define SCI0SR1	(*(volatile unsigned char *)(REG_BASE + 0x000000CC))

#define PF        	0x1
#define FE        	0x2
#define NF        	0x4
#define OR        	0x8
#define IDLE      	0x10
#define RDRF      	0x20
#define TC        	0x40
#define TDRE      	0x80

#define SCI0SR2	(*(volatile unsigned char *)(REG_BASE + 0x000000CD))

#define RAF       	0x1
#define TXDIR     	0x2
#define BRK13     	0x4

#define SCI0DRH	(*(volatile unsigned char *)(REG_BASE + 0x000000CE))

#define T8        	0x40
#define R8        	0x80

#define SCI0DRL	(*(volatile unsigned char *)(REG_BASE + 0x000000CF))

#define T0        	0x1
#define T1        	0x2
#define T2        	0x4
#define T3        	0x8
#define T4        	0x10
#define T5        	0x20
#define T6        	0x40
#define T7        	0x80

#define SCI1BD	(*(volatile unsigned *)(REG_BASE + 0x000000D0))

/* duplicate resolved by name mangling -- prepend SCI1BD */

#define SCI1BD_SBR0	0x1

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR1	0x2

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR2	0x4

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR3	0x8

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR4	0x10

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR5	0x20

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR6	0x40

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR7	0x80

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR8	0x100

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR9	0x200

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR10	0x400

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR11	0x800

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR12	0x1000

/* duplicate resolved by name mangling -- prepend SCI1BD */
#define SCI1BD_SBR	0x1fff

#define SCI1CR1	(*(volatile unsigned char *)(REG_BASE + 0x000000D2))

/* duplicate resolved by name mangling -- prepend SCI1CR1 */

#define SCI1CR1_PT	0x1

/* duplicate resolved by name mangling -- prepend SCI1CR1 */
#define SCI1CR1_PE	0x2

/* duplicate resolved by name mangling -- prepend SCI1CR1 */
#define SCI1CR1_ILT	0x4

/* duplicate resolved by name mangling -- prepend SCI1CR1 */
#define SCI1CR1_WAKE	0x8

/* duplicate resolved by name mangling -- prepend SCI1CR1 */
#define SCI1CR1_M 	0x10

/* duplicate resolved by name mangling -- prepend SCI1CR1 */
#define SCI1CR1_RSRC	0x20

/* duplicate resolved by name mangling -- prepend SCI1CR1 */
#define SCI1CR1_SCISWAI	0x40

/* duplicate resolved by name mangling -- prepend SCI1CR1 */
#define SCI1CR1_LOOPS	0x80

#define SCI1CR2	(*(volatile unsigned char *)(REG_BASE + 0x000000D3))

/* duplicate resolved by name mangling -- prepend SCI1CR2 */

#define SCI1CR2_SBK	0x1

/* duplicate resolved by name mangling -- prepend SCI1CR2 */
#define SCI1CR2_RWU	0x2

/* duplicate resolved by name mangling -- prepend SCI1CR2 */
#define SCI1CR2_RE	0x4

/* duplicate resolved by name mangling -- prepend SCI1CR2 */
#define SCI1CR2_TE	0x8

/* duplicate resolved by name mangling -- prepend SCI1CR2 */
#define SCI1CR2_ILIE	0x10

/* duplicate resolved by name mangling -- prepend SCI1CR2 */
#define SCI1CR2_RIE	0x20

/* duplicate resolved by name mangling -- prepend SCI1CR2 */
#define SCI1CR2_TCIE	0x40

/* duplicate resolved by name mangling -- prepend SCI1CR2 */
#define SCI1CR2_SCTIE	0x80

#define SCI1SR1	(*(volatile unsigned char *)(REG_BASE + 0x000000D4))

/* duplicate resolved by name mangling -- prepend SCI1SR1 */

#define SCI1SR1_PF	0x1

/* duplicate resolved by name mangling -- prepend SCI1SR1 */
#define SCI1SR1_FE	0x2

/* duplicate resolved by name mangling -- prepend SCI1SR1 */
#define SCI1SR1_NF	0x4

/* duplicate resolved by name mangling -- prepend SCI1SR1 */
#define SCI1SR1_OR	0x8

/* duplicate resolved by name mangling -- prepend SCI1SR1 */
#define SCI1SR1_IDLE	0x10

/* duplicate resolved by name mangling -- prepend SCI1SR1 */
#define SCI1SR1_RDRF	0x20

/* duplicate resolved by name mangling -- prepend SCI1SR1 */
#define SCI1SR1_TC	0x40

/* duplicate resolved by name mangling -- prepend SCI1SR1 */
#define SCI1SR1_TDRE	0x80

#define SCI1SR2	(*(volatile unsigned char *)(REG_BASE + 0x000000D5))

/* duplicate resolved by name mangling -- prepend SCI1SR2 */

#define SCI1SR2_RAF	0x1

/* duplicate resolved by name mangling -- prepend SCI1SR2 */
#define SCI1SR2_TXDIR	0x2

/* duplicate resolved by name mangling -- prepend SCI1SR2 */
#define SCI1SR2_BRK13	0x4

#define SCI1DRH	(*(volatile unsigned char *)(REG_BASE + 0x000000D6))

/* duplicate resolved by name mangling -- prepend SCI1DRH */

#define SCI1DRH_T8	0x40

/* duplicate resolved by name mangling -- prepend SCI1DRH */
#define SCI1DRH_R8	0x80

#define SCI1DRL	(*(volatile unsigned char *)(REG_BASE + 0x000000D7))

/* duplicate resolved by name mangling -- prepend SCI1DRL_R0 */

#define SCI1DRL_R0_T0	0x1

/* duplicate resolved by name mangling -- prepend SCI1DRL_R1 */
#define SCI1DRL_R1_T1	0x2

/* duplicate resolved by name mangling -- prepend SCI1DRL_R2 */
#define SCI1DRL_R2_T2	0x4

/* duplicate resolved by name mangling -- prepend SCI1DRL_R3 */
#define SCI1DRL_R3_T3	0x8

/* duplicate resolved by name mangling -- prepend SCI1DRL_R4 */
#define SCI1DRL_R4_T4	0x10

/* duplicate resolved by name mangling -- prepend SCI1DRL_R5 */
#define SCI1DRL_R5_T5	0x20

/* duplicate resolved by name mangling -- prepend SCI1DRL_R6 */
#define SCI1DRL_R6_T6	0x40

/* duplicate resolved by name mangling -- prepend SCI1DRL_R7 */
#define SCI1DRL_R7_T7	0x80

#define SPI0CR1	(*(volatile unsigned char *)(REG_BASE + 0x000000D8))

#define LSBFE     	0x1
#define SSOE      	0x2
#define CPHA      	0x4
#define CPOL      	0x8
#define MSTR      	0x10
#define SPTIE     	0x20
#define SPE       	0x40
#define SPIE      	0x80

#define SPI0CR2	(*(volatile unsigned char *)(REG_BASE + 0x000000D9))

#define SPC0      	0x1
#define SPISWAI   	0x2
#define BIDIROE   	0x8
#define MODFEN    	0x10

#define SPI0BR	(*(volatile unsigned char *)(REG_BASE + 0x000000DA))

#define SPR0      	0x1
#define SPR1      	0x2
#define SPR2      	0x4
#define SPPR0     	0x10
#define SPPR1     	0x20
#define SPPR2     	0x40
#define SPR       	0x7
#define SPPR      	0x70

#define SPI0SR	(*(volatile unsigned char *)(REG_BASE + 0x000000DB))

#define MODF      	0x10
#define SPTEF     	0x20
#define SPIF      	0x80

#define SPI0DR	(*(volatile unsigned char *)(REG_BASE + 0x000000DD))
#define IBAD	(*(volatile unsigned char *)(REG_BASE + 0x000000E0))

/* duplicate resolved by name mangling -- prepend IBAD */

#define IBAD_ADR1 	0x2

/* duplicate resolved by name mangling -- prepend IBAD */
#define IBAD_ADR2 	0x4

/* duplicate resolved by name mangling -- prepend IBAD */
#define IBAD_ADR3 	0x8
#define ADR4      	0x10
#define ADR5      	0x20
#define ADR6      	0x40
#define ADR7      	0x80
#define ADR_1     	0xfe

#define IBFD	(*(volatile unsigned char *)(REG_BASE + 0x000000E1))

#define IBC0      	0x1
#define IBC1      	0x2
#define IBC2      	0x4
#define IBC3      	0x8
#define IBC4      	0x10
#define IBC5      	0x20
#define IBC6      	0x40
#define IBC7      	0x80
#define IBC       	0xff

#define IBCR	(*(volatile unsigned char *)(REG_BASE + 0x000000E2))

#define IBSWAI    	0x1
#define RSTA      	0x4
#define TXAK      	0x8
#define RX        	0x10
#define SL        	0x20
#define IBIE      	0x40
#define IBEN      	0x80

#define IBSR	(*(volatile unsigned char *)(REG_BASE + 0x000000E3))

#define RXAK      	0x1
#define IBIF      	0x2
#define SRW       	0x4
#define IBAL      	0x10
#define IBB       	0x20
#define IAAS      	0x40
#define TCF       	0x80

#define IBDR	(*(volatile unsigned char *)(REG_BASE + 0x000000E4))

#define D0        	0x1
#define D1        	0x2
#define D2        	0x4
#define D3        	0x8
#define D4        	0x10
#define D5        	0x20
#define D6        	0x40
#define D7        	0x80
#define D         	0xff

#define SPI1CR1	(*(volatile unsigned char *)(REG_BASE + 0x000000F0))

/* duplicate resolved by name mangling -- prepend SPI1CR1 */

#define SPI1CR1_LSBFE	0x1

/* duplicate resolved by name mangling -- prepend SPI1CR1 */
#define SPI1CR1_SSOE	0x2

/* duplicate resolved by name mangling -- prepend SPI1CR1 */
#define SPI1CR1_CPHA	0x4

/* duplicate resolved by name mangling -- prepend SPI1CR1 */
#define SPI1CR1_CPOL	0x8

/* duplicate resolved by name mangling -- prepend SPI1CR1 */
#define SPI1CR1_MSTR	0x10

/* duplicate resolved by name mangling -- prepend SPI1CR1 */
#define SPI1CR1_SPTIE	0x20

/* duplicate resolved by name mangling -- prepend SPI1CR1 */
#define SPI1CR1_SPE	0x40

/* duplicate resolved by name mangling -- prepend SPI1CR1 */
#define SPI1CR1_SPIE	0x80

#define SPI1CR2	(*(volatile unsigned char *)(REG_BASE + 0x000000F1))

/* duplicate resolved by name mangling -- prepend SPI1CR2 */

#define SPI1CR2_SPC0	0x1

/* duplicate resolved by name mangling -- prepend SPI1CR2 */
#define SPI1CR2_SPISWAI	0x2

/* duplicate resolved by name mangling -- prepend SPI1CR2 */
#define SPI1CR2_BIDIROE	0x8

/* duplicate resolved by name mangling -- prepend SPI1CR2 */
#define SPI1CR2_MODFEN	0x10

#define SPI1BR	(*(volatile unsigned char *)(REG_BASE + 0x000000F2))

/* duplicate resolved by name mangling -- prepend SPI1BR */

#define SPI1BR_SPR0	0x1

/* duplicate resolved by name mangling -- prepend SPI1BR */
#define SPI1BR_SPR1	0x2

/* duplicate resolved by name mangling -- prepend SPI1BR */
#define SPI1BR_SPR2	0x4

/* duplicate resolved by name mangling -- prepend SPI1BR */
#define SPI1BR_SPPR0	0x10

/* duplicate resolved by name mangling -- prepend SPI1BR */
#define SPI1BR_SPPR1	0x20

/* duplicate resolved by name mangling -- prepend SPI1BR */
#define SPI1BR_SPPR2	0x40

/* duplicate resolved by name mangling -- prepend SPI1BR */
#define SPI1BR_SPR	0x7

/* duplicate resolved by name mangling -- prepend SPI1BR */
#define SPI1BR_SPPR	0x70

#define SPI1SR	(*(volatile unsigned char *)(REG_BASE + 0x000000F3))

/* duplicate resolved by name mangling -- prepend SPI1SR */

#define SPI1SR_MODF	0x10

/* duplicate resolved by name mangling -- prepend SPI1SR */
#define SPI1SR_SPTEF	0x20

/* duplicate resolved by name mangling -- prepend SPI1SR */
#define SPI1SR_SPIF	0x80

#define SPI1DR	(*(volatile unsigned char *)(REG_BASE + 0x000000F5))
#define FCLKDIV	(*(volatile unsigned char *)(REG_BASE + 0x00000100))

#define FDIV0     	0x1
#define FDIV1     	0x2
#define FDIV2     	0x4
#define FDIV3     	0x8
#define FDIV4     	0x10
#define FDIV5     	0x20
#define PRDIV8    	0x40
#define FDIVLD    	0x80
#define FDIV      	0x3f

#define FSEC	(*(volatile unsigned char *)(REG_BASE + 0x00000101))

#define SEC0      	0x1
#define SEC1      	0x2
#define NV2       	0x4
#define NV3       	0x8
#define NV4       	0x10
#define NV5       	0x20
#define NV6       	0x40
#define KEYEN     	0x80
#define SEC       	0x3
#define NV_2      	0x7c

#define FCNFG	(*(volatile unsigned char *)(REG_BASE + 0x00000103))

#define BKSEL     	0x1
#define KEYACC    	0x20
#define CCIE      	0x40
#define CBEIE     	0x80

#define FPROT	(*(volatile unsigned char *)(REG_BASE + 0x00000104))

#define FPLS0     	0x1
#define FPLS1     	0x2
#define FPLDIS    	0x4
#define FPHS0     	0x8
#define FPHS1     	0x10
#define FPHDIS    	0x20

/* duplicate resolved by name mangling -- prepend FPROT */
#define FPROT_NV6 	0x40
#define FPOPEN    	0x80
#define FPLS      	0x3
#define FPHS      	0x18

#define FSTAT	(*(volatile unsigned char *)(REG_BASE + 0x00000105))

#define BLANK     	0x4
#define ACCERR    	0x10
#define PVIOL     	0x20
#define CCIF      	0x40
#define CBEIF     	0x80

#define FCMD	(*(volatile unsigned char *)(REG_BASE + 0x00000106))

#define CMDB0     	0x1
#define CMDB2     	0x4
#define CMDB5     	0x20
#define CMDB6     	0x40
#define CMDB_5    	0x60

#define ECLKDIV	(*(volatile unsigned char *)(REG_BASE + 0x00000110))

#define EDIV0     	0x1
#define EDIV1     	0x2
#define EDIV2     	0x4
#define EDIV3     	0x8
#define EDIV4     	0x10
#define EDIV5     	0x20

/* duplicate resolved by name mangling -- prepend ECLKDIV */
#define ECLKDIV_PRDIV8	0x40
#define EDIVLD    	0x80
#define EDIV      	0x3f

#define ECNFG	(*(volatile unsigned char *)(REG_BASE + 0x00000113))

/* duplicate resolved by name mangling -- prepend ECNFG */

#define ECNFG_CCIE	0x40

/* duplicate resolved by name mangling -- prepend ECNFG */
#define ECNFG_CBEIE	0x80

#define EPROT	(*(volatile unsigned char *)(REG_BASE + 0x00000114))

#define EP0       	0x1
#define EP1       	0x2
#define EP2       	0x4
#define EPDIS     	0x8
#define EPOPEN    	0x80
#define EP        	0x7

#define ESTAT	(*(volatile unsigned char *)(REG_BASE + 0x00000115))

/* duplicate resolved by name mangling -- prepend ESTAT */

#define ESTAT_BLANK	0x4

/* duplicate resolved by name mangling -- prepend ESTAT */
#define ESTAT_ACCERR	0x10

/* duplicate resolved by name mangling -- prepend ESTAT */
#define ESTAT_PVIOL	0x20

/* duplicate resolved by name mangling -- prepend ESTAT */
#define ESTAT_CCIF	0x40

/* duplicate resolved by name mangling -- prepend ESTAT */
#define ESTAT_CBEIF	0x80

#define ECMD	(*(volatile unsigned char *)(REG_BASE + 0x00000116))

/* duplicate resolved by name mangling -- prepend ECMD */

#define ECMD_CMDB0	0x1

/* duplicate resolved by name mangling -- prepend ECMD */
#define ECMD_CMDB2	0x4

/* duplicate resolved by name mangling -- prepend ECMD */
#define ECMD_CMDB5	0x20

/* duplicate resolved by name mangling -- prepend ECMD */
#define ECMD_CMDB6	0x40

/* duplicate resolved by name mangling -- prepend ECMD */
#define ECMD_CMDB_5	0x60

#define ATD1CTL23	(*(volatile unsigned *)(REG_BASE + 0x00000122))

#define ATD1CTL2	(*(volatile unsigned char*)(REG_BASE + 0x00000122))
#define ATD1CTL3	(*(volatile unsigned char*)(REG_BASE + 0x00000123))

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */

#define ATD1CTL23_FRZ0	0x1

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_FRZ1	0x2

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_FIFO	0x4

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_S1C	0x8

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_S2C	0x10

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_S4C	0x20

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_S8C	0x40

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_ASCIF	0x100

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_ASCIE	0x200

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_ETRIGE	0x400

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_ETRIGP	0x800

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_ETRIGLE	0x1000

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_AWAI	0x2000

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_AFFC	0x4000

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_ADPU	0x8000

/* duplicate resolved by name mangling -- prepend ATD1CTL23 */
#define ATD1CTL23_FRZ	0x3

#define ATD1CTL45	(*(volatile unsigned *)(REG_BASE + 0x00000124))

#define ATD1CTL4	(*(volatile unsigned char*)(REG_BASE + 0x00000124))
#define ATD1CTL5	(*(volatile unsigned char*)(REG_BASE + 0x00000125))

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */

#define ATD1CTL45_CA	0x1

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_CB	0x2

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_CC	0x4

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_MULT	0x10

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_SCAN	0x20

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_DSGN	0x40

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_DJM	0x80

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_PRS0	0x100

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_PRS1	0x200

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_PRS2	0x400

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_PRS3	0x800

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_PRS4	0x1000

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_SMP0	0x2000

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_SMP1	0x4000

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_SRES8	0x8000

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_Cx	0x7

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_PRS	0x1f00

/* duplicate resolved by name mangling -- prepend ATD1CTL45 */
#define ATD1CTL45_SMP	0x6000

#define ATD1STAT0	(*(volatile unsigned char *)(REG_BASE + 0x00000126))

/* duplicate resolved by name mangling -- prepend ATD1STAT0 */

#define ATD1STAT0_CC0	0x1

/* duplicate resolved by name mangling -- prepend ATD1STAT0 */
#define ATD1STAT0_CC1	0x2

/* duplicate resolved by name mangling -- prepend ATD1STAT0 */
#define ATD1STAT0_CC2	0x4

/* duplicate resolved by name mangling -- prepend ATD1STAT0 */
#define ATD1STAT0_FIFOR	0x10

/* duplicate resolved by name mangling -- prepend ATD1STAT0 */
#define ATD1STAT0_ETORF	0x20

/* duplicate resolved by name mangling -- prepend ATD1STAT0 */
#define ATD1STAT0_SCF	0x80

/* duplicate resolved by name mangling -- prepend ATD1STAT0 */
#define ATD1STAT0_CC	0x7

#define ATD1STAT1	(*(volatile unsigned char *)(REG_BASE + 0x0000012B))

/* duplicate resolved by name mangling -- prepend ATD1STAT1 */

#define ATD1STAT1_CCF0	0x1

/* duplicate resolved by name mangling -- prepend ATD1STAT1 */
#define ATD1STAT1_CCF1	0x2

/* duplicate resolved by name mangling -- prepend ATD1STAT1 */
#define ATD1STAT1_CCF2	0x4

/* duplicate resolved by name mangling -- prepend ATD1STAT1 */
#define ATD1STAT1_CCF3	0x8

/* duplicate resolved by name mangling -- prepend ATD1STAT1 */
#define ATD1STAT1_CCF4	0x10

/* duplicate resolved by name mangling -- prepend ATD1STAT1 */
#define ATD1STAT1_CCF5	0x20

/* duplicate resolved by name mangling -- prepend ATD1STAT1 */
#define ATD1STAT1_CCF6	0x40

/* duplicate resolved by name mangling -- prepend ATD1STAT1 */
#define ATD1STAT1_CCF7	0x80

/* duplicate resolved by name mangling -- prepend ATD1STAT1 */
#define ATD1STAT1_CCF	0xff

#define ATD1DIEN	(*(volatile unsigned char *)(REG_BASE + 0x0000012D))
#define PORTAD1	(*(volatile unsigned char *)(REG_BASE + 0x0000012F))
#define ATD1DR0	(*(volatile unsigned *)(REG_BASE + 0x00000130))
#define ATD1DR1	(*(volatile unsigned *)(REG_BASE + 0x00000132))
#define ATD1DR2	(*(volatile unsigned *)(REG_BASE + 0x00000134))
#define ATD1DR3	(*(volatile unsigned *)(REG_BASE + 0x00000136))
#define ATD1DR4	(*(volatile unsigned *)(REG_BASE + 0x00000138))
#define ATD1DR5	(*(volatile unsigned *)(REG_BASE + 0x0000013A))
#define ATD1DR6	(*(volatile unsigned *)(REG_BASE + 0x0000013C))
#define ATD1DR7	(*(volatile unsigned *)(REG_BASE + 0x0000013E))
#define CANCTL0	(*(volatile unsigned char *)(REG_BASE + 0x00000140))

#define INITRQ    	0x1
#define SLPRQ     	0x2
#define WUPE      	0x4
#define TIME      	0x8
#define SYNCH     	0x10
#define CSWAI     	0x20
#define RXACT     	0x40
#define RXFRM     	0x80

#define CANCTL1	(*(volatile unsigned char *)(REG_BASE + 0x00000141))

#define INITAK    	0x1
#define SLPAK     	0x2
#define WUPM      	0x4
#define LISTEN    	0x10
#define LOOPB     	0x20
#define CLKSRC    	0x40
#define CANE      	0x80

#define CANBTR0	(*(volatile unsigned char *)(REG_BASE + 0x00000142))

#define BRP0      	0x1
#define BRP1      	0x2
#define BRP2      	0x4
#define BRP3      	0x8
#define BRP4      	0x10
#define BRP5      	0x20
#define SJW0      	0x40
#define SJW1      	0x80
#define BRP       	0x3f
#define SJW       	0xc0

#define CANBTR1	(*(volatile unsigned char *)(REG_BASE + 0x00000143))

#define TSEG10    	0x1
#define TSEG11    	0x2
#define TSEG12    	0x4
#define TSEG13    	0x8
#define TSEG20    	0x10
#define TSEG21    	0x20
#define TSEG22    	0x40
#define SAMP      	0x80
#define TSEG_10   	0xf
#define TSEG_20   	0x70

#define CANRFLG	(*(volatile unsigned char *)(REG_BASE + 0x00000144))

#define RXF       	0x1
#define OVRIF     	0x2
#define TSTAT0    	0x4
#define TSTAT1    	0x8
#define RSTAT0    	0x10
#define RSTAT1    	0x20
#define CSCIF     	0x40
#define WUPIF     	0x80
#define TSTAT     	0xc
#define RSTAT     	0x30

#define CANRIER	(*(volatile unsigned char *)(REG_BASE + 0x00000145))

#define RXFIE     	0x1
#define OVRIE     	0x2
#define TSTATE0   	0x4
#define TSTATE1   	0x8
#define RSTATE0   	0x10
#define RSTATE1   	0x20
#define CSCIE     	0x40
#define WUPIE     	0x80
#define TSTATE    	0xc
#define RSTATE    	0x30

#define CANTFLG	(*(volatile unsigned char *)(REG_BASE + 0x00000146))

#define TXE0      	0x1
#define TXE1      	0x2
#define TXE2      	0x4
#define TXE       	0x7

#define CANTIER	(*(volatile unsigned char *)(REG_BASE + 0x00000147))

#define TXEIE0    	0x1
#define TXEIE1    	0x2
#define TXEIE2    	0x4
#define TXEIE     	0x7

#define CANTARQ	(*(volatile unsigned char *)(REG_BASE + 0x00000148))

#define ABTRQ0    	0x1
#define ABTRQ1    	0x2
#define ABTRQ2    	0x4
#define ABTRQ     	0x7

#define CANTAAK	(*(volatile unsigned char *)(REG_BASE + 0x00000149))

#define ABTAK0    	0x1
#define ABTAK1    	0x2
#define ABTAK2    	0x4
#define ABTAK     	0x7

#define CANTBSEL	(*(volatile unsigned char *)(REG_BASE + 0x0000014A))

#define TX0       	0x1
#define TX1       	0x2
#define TX2       	0x4
#define TX        	0x7

#define CANIDAC	(*(volatile unsigned char *)(REG_BASE + 0x0000014B))

#define IDHIT0    	0x1
#define IDHIT1    	0x2
#define IDHIT2    	0x4
#define IDAM0     	0x10
#define IDAM1     	0x20
#define IDHIT     	0x7
#define IDAM      	0x30

#define CANRXERR	(*(volatile unsigned char *)(REG_BASE + 0x0000014E))

#define RXERR0    	0x1
#define RXERR1    	0x2
#define RXERR2    	0x4
#define RXERR3    	0x8
#define RXERR4    	0x10
#define RXERR5    	0x20
#define RXERR6    	0x40
#define RXERR7    	0x80
#define RXERR     	0xff

#define CANTXERR	(*(volatile unsigned char *)(REG_BASE + 0x0000014F))

#define TXERR0    	0x1
#define TXERR1    	0x2
#define TXERR2    	0x4
#define TXERR3    	0x8
#define TXERR4    	0x10
#define TXERR5    	0x20
#define TXERR6    	0x40
#define TXERR7    	0x80
#define TXERR     	0xff

#define CANIDAR0	(*(volatile unsigned char *)(REG_BASE + 0x00000150))

#define AC0       	0x1
#define AC1       	0x2
#define AC2       	0x4
#define AC3       	0x8
#define AC4       	0x10
#define AC5       	0x20
#define AC6       	0x40
#define AC7       	0x80
#define AC        	0xff

#define CANIDAR1	(*(volatile unsigned char *)(REG_BASE + 0x00000151))

/* duplicate resolved by name mangling -- prepend CANIDAR1 */

#define CANIDAR1_AC0	0x1

/* duplicate resolved by name mangling -- prepend CANIDAR1 */
#define CANIDAR1_AC1	0x2

/* duplicate resolved by name mangling -- prepend CANIDAR1 */
#define CANIDAR1_AC2	0x4

/* duplicate resolved by name mangling -- prepend CANIDAR1 */
#define CANIDAR1_AC3	0x8

/* duplicate resolved by name mangling -- prepend CANIDAR1 */
#define CANIDAR1_AC4	0x10

/* duplicate resolved by name mangling -- prepend CANIDAR1 */
#define CANIDAR1_AC5	0x20

/* duplicate resolved by name mangling -- prepend CANIDAR1 */
#define CANIDAR1_AC6	0x40

/* duplicate resolved by name mangling -- prepend CANIDAR1 */
#define CANIDAR1_AC7	0x80

/* duplicate resolved by name mangling -- prepend CANIDAR1 */
#define CANIDAR1_AC	0xff

#define CANIDAR2	(*(volatile unsigned char *)(REG_BASE + 0x00000152))

/* duplicate resolved by name mangling -- prepend CANIDAR2 */

#define CANIDAR2_AC0	0x1

/* duplicate resolved by name mangling -- prepend CANIDAR2 */
#define CANIDAR2_AC1	0x2

/* duplicate resolved by name mangling -- prepend CANIDAR2 */
#define CANIDAR2_AC2	0x4

/* duplicate resolved by name mangling -- prepend CANIDAR2 */
#define CANIDAR2_AC3	0x8

/* duplicate resolved by name mangling -- prepend CANIDAR2 */
#define CANIDAR2_AC4	0x10

/* duplicate resolved by name mangling -- prepend CANIDAR2 */
#define CANIDAR2_AC5	0x20

/* duplicate resolved by name mangling -- prepend CANIDAR2 */
#define CANIDAR2_AC6	0x40

/* duplicate resolved by name mangling -- prepend CANIDAR2 */
#define CANIDAR2_AC7	0x80

/* duplicate resolved by name mangling -- prepend CANIDAR2 */
#define CANIDAR2_AC	0xff

#define CANIDAR3	(*(volatile unsigned char *)(REG_BASE + 0x00000153))

/* duplicate resolved by name mangling -- prepend CANIDAR3 */

#define CANIDAR3_AC0	0x1

/* duplicate resolved by name mangling -- prepend CANIDAR3 */
#define CANIDAR3_AC1	0x2

/* duplicate resolved by name mangling -- prepend CANIDAR3 */
#define CANIDAR3_AC2	0x4

/* duplicate resolved by name mangling -- prepend CANIDAR3 */
#define CANIDAR3_AC3	0x8

/* duplicate resolved by name mangling -- prepend CANIDAR3 */
#define CANIDAR3_AC4	0x10

/* duplicate resolved by name mangling -- prepend CANIDAR3 */
#define CANIDAR3_AC5	0x20

/* duplicate resolved by name mangling -- prepend CANIDAR3 */
#define CANIDAR3_AC6	0x40

/* duplicate resolved by name mangling -- prepend CANIDAR3 */
#define CANIDAR3_AC7	0x80

/* duplicate resolved by name mangling -- prepend CANIDAR3 */
#define CANIDAR3_AC	0xff

#define CANIDMR0	(*(volatile unsigned char *)(REG_BASE + 0x00000154))

#define AM0       	0x1
#define AM1       	0x2
#define AM2       	0x4
#define AM3       	0x8
#define AM4       	0x10
#define AM5       	0x20
#define AM6       	0x40
#define AM7       	0x80
#define AM        	0xff

#define CANIDMR1	(*(volatile unsigned char *)(REG_BASE + 0x00000155))

/* duplicate resolved by name mangling -- prepend CANIDMR1 */

#define CANIDMR1_AM0	0x1

/* duplicate resolved by name mangling -- prepend CANIDMR1 */
#define CANIDMR1_AM1	0x2

/* duplicate resolved by name mangling -- prepend CANIDMR1 */
#define CANIDMR1_AM2	0x4

/* duplicate resolved by name mangling -- prepend CANIDMR1 */
#define CANIDMR1_AM3	0x8

/* duplicate resolved by name mangling -- prepend CANIDMR1 */
#define CANIDMR1_AM4	0x10

/* duplicate resolved by name mangling -- prepend CANIDMR1 */
#define CANIDMR1_AM5	0x20

/* duplicate resolved by name mangling -- prepend CANIDMR1 */
#define CANIDMR1_AM6	0x40

/* duplicate resolved by name mangling -- prepend CANIDMR1 */
#define CANIDMR1_AM7	0x80

/* duplicate resolved by name mangling -- prepend CANIDMR1 */
#define CANIDMR1_AM	0xff

#define CANIDMR2	(*(volatile unsigned char *)(REG_BASE + 0x00000156))

/* duplicate resolved by name mangling -- prepend CANIDMR2 */

#define CANIDMR2_AM0	0x1

/* duplicate resolved by name mangling -- prepend CANIDMR2 */
#define CANIDMR2_AM1	0x2

/* duplicate resolved by name mangling -- prepend CANIDMR2 */
#define CANIDMR2_AM2	0x4

/* duplicate resolved by name mangling -- prepend CANIDMR2 */
#define CANIDMR2_AM3	0x8

/* duplicate resolved by name mangling -- prepend CANIDMR2 */
#define CANIDMR2_AM4	0x10

/* duplicate resolved by name mangling -- prepend CANIDMR2 */
#define CANIDMR2_AM5	0x20

/* duplicate resolved by name mangling -- prepend CANIDMR2 */
#define CANIDMR2_AM6	0x40

/* duplicate resolved by name mangling -- prepend CANIDMR2 */
#define CANIDMR2_AM7	0x80

/* duplicate resolved by name mangling -- prepend CANIDMR2 */
#define CANIDMR2_AM	0xff

#define CANIDMR3	(*(volatile unsigned char *)(REG_BASE + 0x00000157))

/* duplicate resolved by name mangling -- prepend CANIDMR3 */

#define CANIDMR3_AM0	0x1

/* duplicate resolved by name mangling -- prepend CANIDMR3 */
#define CANIDMR3_AM1	0x2

/* duplicate resolved by name mangling -- prepend CANIDMR3 */
#define CANIDMR3_AM2	0x4

/* duplicate resolved by name mangling -- prepend CANIDMR3 */
#define CANIDMR3_AM3	0x8

/* duplicate resolved by name mangling -- prepend CANIDMR3 */
#define CANIDMR3_AM4	0x10

/* duplicate resolved by name mangling -- prepend CANIDMR3 */
#define CANIDMR3_AM5	0x20

/* duplicate resolved by name mangling -- prepend CANIDMR3 */
#define CANIDMR3_AM6	0x40

/* duplicate resolved by name mangling -- prepend CANIDMR3 */
#define CANIDMR3_AM7	0x80

/* duplicate resolved by name mangling -- prepend CANIDMR3 */
#define CANIDMR3_AM	0xff

#define CANIDAR4	(*(volatile unsigned char *)(REG_BASE + 0x00000158))

/* duplicate resolved by name mangling -- prepend CANIDAR4 */

#define CANIDAR4_AC0	0x1

/* duplicate resolved by name mangling -- prepend CANIDAR4 */
#define CANIDAR4_AC1	0x2

/* duplicate resolved by name mangling -- prepend CANIDAR4 */
#define CANIDAR4_AC2	0x4

/* duplicate resolved by name mangling -- prepend CANIDAR4 */
#define CANIDAR4_AC3	0x8

/* duplicate resolved by name mangling -- prepend CANIDAR4 */
#define CANIDAR4_AC4	0x10

/* duplicate resolved by name mangling -- prepend CANIDAR4 */
#define CANIDAR4_AC5	0x20

/* duplicate resolved by name mangling -- prepend CANIDAR4 */
#define CANIDAR4_AC6	0x40

/* duplicate resolved by name mangling -- prepend CANIDAR4 */
#define CANIDAR4_AC7	0x80

/* duplicate resolved by name mangling -- prepend CANIDAR4 */
#define CANIDAR4_AC	0xff

#define CANIDAR5	(*(volatile unsigned char *)(REG_BASE + 0x00000159))

/* duplicate resolved by name mangling -- prepend CANIDAR5 */

#define CANIDAR5_AC0	0x1

/* duplicate resolved by name mangling -- prepend CANIDAR5 */
#define CANIDAR5_AC1	0x2

/* duplicate resolved by name mangling -- prepend CANIDAR5 */
#define CANIDAR5_AC2	0x4

/* duplicate resolved by name mangling -- prepend CANIDAR5 */
#define CANIDAR5_AC3	0x8

/* duplicate resolved by name mangling -- prepend CANIDAR5 */
#define CANIDAR5_AC4	0x10

/* duplicate resolved by name mangling -- prepend CANIDAR5 */
#define CANIDAR5_AC5	0x20

/* duplicate resolved by name mangling -- prepend CANIDAR5 */
#define CANIDAR5_AC6	0x40

/* duplicate resolved by name mangling -- prepend CANIDAR5 */
#define CANIDAR5_AC7	0x80

/* duplicate resolved by name mangling -- prepend CANIDAR5 */
#define CANIDAR5_AC	0xff

#define CANIDAR6	(*(volatile unsigned char *)(REG_BASE + 0x0000015A))

/* duplicate resolved by name mangling -- prepend CANIDAR6 */

#define CANIDAR6_AC0	0x1

/* duplicate resolved by name mangling -- prepend CANIDAR6 */
#define CANIDAR6_AC1	0x2

/* duplicate resolved by name mangling -- prepend CANIDAR6 */
#define CANIDAR6_AC2	0x4

/* duplicate resolved by name mangling -- prepend CANIDAR6 */
#define CANIDAR6_AC3	0x8

/* duplicate resolved by name mangling -- prepend CANIDAR6 */
#define CANIDAR6_AC4	0x10

/* duplicate resolved by name mangling -- prepend CANIDAR6 */
#define CANIDAR6_AC5	0x20

/* duplicate resolved by name mangling -- prepend CANIDAR6 */
#define CANIDAR6_AC6	0x40

/* duplicate resolved by name mangling -- prepend CANIDAR6 */
#define CANIDAR6_AC7	0x80

/* duplicate resolved by name mangling -- prepend CANIDAR6 */
#define CANIDAR6_AC	0xff

#define CANIDAR7	(*(volatile unsigned char *)(REG_BASE + 0x0000015B))

/* duplicate resolved by name mangling -- prepend CANIDAR7 */

#define CANIDAR7_AC0	0x1

/* duplicate resolved by name mangling -- prepend CANIDAR7 */
#define CANIDAR7_AC1	0x2

/* duplicate resolved by name mangling -- prepend CANIDAR7 */
#define CANIDAR7_AC2	0x4

/* duplicate resolved by name mangling -- prepend CANIDAR7 */
#define CANIDAR7_AC3	0x8

/* duplicate resolved by name mangling -- prepend CANIDAR7 */
#define CANIDAR7_AC4	0x10

/* duplicate resolved by name mangling -- prepend CANIDAR7 */
#define CANIDAR7_AC5	0x20

/* duplicate resolved by name mangling -- prepend CANIDAR7 */
#define CANIDAR7_AC6	0x40

/* duplicate resolved by name mangling -- prepend CANIDAR7 */
#define CANIDAR7_AC7	0x80

/* duplicate resolved by name mangling -- prepend CANIDAR7 */
#define CANIDAR7_AC	0xff

#define CANIDMR4	(*(volatile unsigned char *)(REG_BASE + 0x0000015C))

/* duplicate resolved by name mangling -- prepend CANIDMR4 */

#define CANIDMR4_AM0	0x1

/* duplicate resolved by name mangling -- prepend CANIDMR4 */
#define CANIDMR4_AM1	0x2

/* duplicate resolved by name mangling -- prepend CANIDMR4 */
#define CANIDMR4_AM2	0x4

/* duplicate resolved by name mangling -- prepend CANIDMR4 */
#define CANIDMR4_AM3	0x8

/* duplicate resolved by name mangling -- prepend CANIDMR4 */
#define CANIDMR4_AM4	0x10

/* duplicate resolved by name mangling -- prepend CANIDMR4 */
#define CANIDMR4_AM5	0x20

/* duplicate resolved by name mangling -- prepend CANIDMR4 */
#define CANIDMR4_AM6	0x40

/* duplicate resolved by name mangling -- prepend CANIDMR4 */
#define CANIDMR4_AM7	0x80

/* duplicate resolved by name mangling -- prepend CANIDMR4 */
#define CANIDMR4_AM	0xff

#define CANIDMR5	(*(volatile unsigned char *)(REG_BASE + 0x0000015D))

/* duplicate resolved by name mangling -- prepend CANIDMR5 */

#define CANIDMR5_AM0	0x1

/* duplicate resolved by name mangling -- prepend CANIDMR5 */
#define CANIDMR5_AM1	0x2

/* duplicate resolved by name mangling -- prepend CANIDMR5 */
#define CANIDMR5_AM2	0x4

/* duplicate resolved by name mangling -- prepend CANIDMR5 */
#define CANIDMR5_AM3	0x8

/* duplicate resolved by name mangling -- prepend CANIDMR5 */
#define CANIDMR5_AM4	0x10

/* duplicate resolved by name mangling -- prepend CANIDMR5 */
#define CANIDMR5_AM5	0x20

/* duplicate resolved by name mangling -- prepend CANIDMR5 */
#define CANIDMR5_AM6	0x40

/* duplicate resolved by name mangling -- prepend CANIDMR5 */
#define CANIDMR5_AM7	0x80

/* duplicate resolved by name mangling -- prepend CANIDMR5 */
#define CANIDMR5_AM	0xff

#define CANIDMR6	(*(volatile unsigned char *)(REG_BASE + 0x0000015E))

/* duplicate resolved by name mangling -- prepend CANIDMR6 */

#define CANIDMR6_AM0	0x1

/* duplicate resolved by name mangling -- prepend CANIDMR6 */
#define CANIDMR6_AM1	0x2

/* duplicate resolved by name mangling -- prepend CANIDMR6 */
#define CANIDMR6_AM2	0x4

/* duplicate resolved by name mangling -- prepend CANIDMR6 */
#define CANIDMR6_AM3	0x8

/* duplicate resolved by name mangling -- prepend CANIDMR6 */
#define CANIDMR6_AM4	0x10

/* duplicate resolved by name mangling -- prepend CANIDMR6 */
#define CANIDMR6_AM5	0x20

/* duplicate resolved by name mangling -- prepend CANIDMR6 */
#define CANIDMR6_AM6	0x40

/* duplicate resolved by name mangling -- prepend CANIDMR6 */
#define CANIDMR6_AM7	0x80

/* duplicate resolved by name mangling -- prepend CANIDMR6 */
#define CANIDMR6_AM	0xff

#define CANIDMR7	(*(volatile unsigned char *)(REG_BASE + 0x0000015F))

/* duplicate resolved by name mangling -- prepend CANIDMR7 */

#define CANIDMR7_AM0	0x1

/* duplicate resolved by name mangling -- prepend CANIDMR7 */
#define CANIDMR7_AM1	0x2

/* duplicate resolved by name mangling -- prepend CANIDMR7 */
#define CANIDMR7_AM2	0x4

/* duplicate resolved by name mangling -- prepend CANIDMR7 */
#define CANIDMR7_AM3	0x8

/* duplicate resolved by name mangling -- prepend CANIDMR7 */
#define CANIDMR7_AM4	0x10

/* duplicate resolved by name mangling -- prepend CANIDMR7 */
#define CANIDMR7_AM5	0x20

/* duplicate resolved by name mangling -- prepend CANIDMR7 */
#define CANIDMR7_AM6	0x40

/* duplicate resolved by name mangling -- prepend CANIDMR7 */
#define CANIDMR7_AM7	0x80

/* duplicate resolved by name mangling -- prepend CANIDMR7 */
#define CANIDMR7_AM	0xff

#define CANRXIDR0	(*(volatile unsigned char *)(REG_BASE + 0x00000160))

#define ID21      	0x1
#define ID22      	0x2
#define ID23      	0x4
#define ID24      	0x8
#define ID25      	0x10
#define ID26      	0x20
#define ID27      	0x40
#define ID28      	0x80
#define ID_21     	0xff

#define CANRXIDR1	(*(volatile unsigned char *)(REG_BASE + 0x00000161))

/* duplicate resolved by name mangling -- prepend CANRXIDR1 */

#define CANRXIDR1_ID15	0x1
#define ID16      	0x2
#define ID17      	0x4
#define IDE       	0x8
#define SRR       	0x10
#define ID18      	0x20
#define ID19      	0x40
#define ID20      	0x80
#define ID_15     	0x7
#define ID_18     	0xe0

#define CANRXIDR2	(*(volatile unsigned char *)(REG_BASE + 0x00000162))

/* duplicate resolved by name mangling -- prepend CANRXIDR2 */

#define CANRXIDR2_ID7	0x1

/* duplicate resolved by name mangling -- prepend CANRXIDR2 */
#define CANRXIDR2_ID8	0x2

/* duplicate resolved by name mangling -- prepend CANRXIDR2 */
#define CANRXIDR2_ID9	0x4

/* duplicate resolved by name mangling -- prepend CANRXIDR2 */
#define CANRXIDR2_ID10	0x8

/* duplicate resolved by name mangling -- prepend CANRXIDR2 */
#define CANRXIDR2_ID11	0x10

/* duplicate resolved by name mangling -- prepend CANRXIDR2 */
#define CANRXIDR2_ID12	0x20

/* duplicate resolved by name mangling -- prepend CANRXIDR2 */
#define CANRXIDR2_ID13	0x40

/* duplicate resolved by name mangling -- prepend CANRXIDR2 */
#define CANRXIDR2_ID14	0x80
#define ID_7      	0xff

#define CANRXIDR3	(*(volatile unsigned char *)(REG_BASE + 0x00000163))

/* duplicate resolved by name mangling -- prepend CANRXIDR3 */

#define CANRXIDR3_RTR	0x1

/* duplicate resolved by name mangling -- prepend CANRXIDR3 */
#define CANRXIDR3_ID0	0x2

/* duplicate resolved by name mangling -- prepend CANRXIDR3 */
#define CANRXIDR3_ID1	0x4

/* duplicate resolved by name mangling -- prepend CANRXIDR3 */
#define CANRXIDR3_ID2	0x8

/* duplicate resolved by name mangling -- prepend CANRXIDR3 */
#define CANRXIDR3_ID3	0x10

/* duplicate resolved by name mangling -- prepend CANRXIDR3 */
#define CANRXIDR3_ID4	0x20

/* duplicate resolved by name mangling -- prepend CANRXIDR3 */
#define CANRXIDR3_ID5	0x40

/* duplicate resolved by name mangling -- prepend CANRXIDR3 */
#define CANRXIDR3_ID6	0x80

/* duplicate resolved by name mangling -- prepend CANRXIDR3 */
#define CANRXIDR3_ID	0xfe

#define CANRXDSR0	(*(volatile unsigned char *)(REG_BASE + 0x00000164))

#define DB0       	0x1
#define DB1       	0x2
#define DB2       	0x4
#define DB3       	0x8
#define DB4       	0x10
#define DB5       	0x20
#define DB6       	0x40
#define DB7       	0x80
#define DB        	0xff

#define CANRXDSR1	(*(volatile unsigned char *)(REG_BASE + 0x00000165))

/* duplicate resolved by name mangling -- prepend CANRXDSR1 */

#define CANRXDSR1_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANRXDSR1 */
#define CANRXDSR1_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANRXDSR1 */
#define CANRXDSR1_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANRXDSR1 */
#define CANRXDSR1_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANRXDSR1 */
#define CANRXDSR1_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANRXDSR1 */
#define CANRXDSR1_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANRXDSR1 */
#define CANRXDSR1_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANRXDSR1 */
#define CANRXDSR1_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANRXDSR1 */
#define CANRXDSR1_DB	0xff

#define CANRXDSR2	(*(volatile unsigned char *)(REG_BASE + 0x00000166))

/* duplicate resolved by name mangling -- prepend CANRXDSR2 */

#define CANRXDSR2_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANRXDSR2 */
#define CANRXDSR2_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANRXDSR2 */
#define CANRXDSR2_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANRXDSR2 */
#define CANRXDSR2_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANRXDSR2 */
#define CANRXDSR2_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANRXDSR2 */
#define CANRXDSR2_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANRXDSR2 */
#define CANRXDSR2_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANRXDSR2 */
#define CANRXDSR2_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANRXDSR2 */
#define CANRXDSR2_DB	0xff

#define CANRXDSR3	(*(volatile unsigned char *)(REG_BASE + 0x00000167))

/* duplicate resolved by name mangling -- prepend CANRXDSR3 */

#define CANRXDSR3_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANRXDSR3 */
#define CANRXDSR3_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANRXDSR3 */
#define CANRXDSR3_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANRXDSR3 */
#define CANRXDSR3_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANRXDSR3 */
#define CANRXDSR3_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANRXDSR3 */
#define CANRXDSR3_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANRXDSR3 */
#define CANRXDSR3_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANRXDSR3 */
#define CANRXDSR3_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANRXDSR3 */
#define CANRXDSR3_DB	0xff

#define CANRXDSR4	(*(volatile unsigned char *)(REG_BASE + 0x00000168))

/* duplicate resolved by name mangling -- prepend CANRXDSR4 */

#define CANRXDSR4_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANRXDSR4 */
#define CANRXDSR4_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANRXDSR4 */
#define CANRXDSR4_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANRXDSR4 */
#define CANRXDSR4_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANRXDSR4 */
#define CANRXDSR4_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANRXDSR4 */
#define CANRXDSR4_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANRXDSR4 */
#define CANRXDSR4_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANRXDSR4 */
#define CANRXDSR4_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANRXDSR4 */
#define CANRXDSR4_DB	0xff

#define CANRXDSR5	(*(volatile unsigned char *)(REG_BASE + 0x00000169))

/* duplicate resolved by name mangling -- prepend CANRXDSR5 */

#define CANRXDSR5_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANRXDSR5 */
#define CANRXDSR5_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANRXDSR5 */
#define CANRXDSR5_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANRXDSR5 */
#define CANRXDSR5_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANRXDSR5 */
#define CANRXDSR5_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANRXDSR5 */
#define CANRXDSR5_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANRXDSR5 */
#define CANRXDSR5_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANRXDSR5 */
#define CANRXDSR5_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANRXDSR5 */
#define CANRXDSR5_DB	0xff

#define CANRXDSR6	(*(volatile unsigned char *)(REG_BASE + 0x0000016A))

/* duplicate resolved by name mangling -- prepend CANRXDSR6 */

#define CANRXDSR6_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANRXDSR6 */
#define CANRXDSR6_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANRXDSR6 */
#define CANRXDSR6_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANRXDSR6 */
#define CANRXDSR6_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANRXDSR6 */
#define CANRXDSR6_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANRXDSR6 */
#define CANRXDSR6_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANRXDSR6 */
#define CANRXDSR6_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANRXDSR6 */
#define CANRXDSR6_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANRXDSR6 */
#define CANRXDSR6_DB	0xff

#define CANRXDSR7	(*(volatile unsigned char *)(REG_BASE + 0x0000016B))

/* duplicate resolved by name mangling -- prepend CANRXDSR7 */

#define CANRXDSR7_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANRXDSR7 */
#define CANRXDSR7_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANRXDSR7 */
#define CANRXDSR7_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANRXDSR7 */
#define CANRXDSR7_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANRXDSR7 */
#define CANRXDSR7_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANRXDSR7 */
#define CANRXDSR7_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANRXDSR7 */
#define CANRXDSR7_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANRXDSR7 */
#define CANRXDSR7_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANRXDSR7 */
#define CANRXDSR7_DB	0xff

#define CANRXDLR	(*(volatile unsigned char *)(REG_BASE + 0x0000016C))

#define DLC0      	0x1
#define DLC1      	0x2
#define DLC2      	0x4
#define DLC3      	0x8
#define DLC       	0xf

#define CANTXIDR0	(*(volatile unsigned char *)(REG_BASE + 0x00000170))

/* duplicate resolved by name mangling -- prepend CANTXIDR0 */

#define CANTXIDR0_ID21	0x1

/* duplicate resolved by name mangling -- prepend CANTXIDR0 */
#define CANTXIDR0_ID22	0x2

/* duplicate resolved by name mangling -- prepend CANTXIDR0 */
#define CANTXIDR0_ID23	0x4

/* duplicate resolved by name mangling -- prepend CANTXIDR0 */
#define CANTXIDR0_ID24	0x8

/* duplicate resolved by name mangling -- prepend CANTXIDR0 */
#define CANTXIDR0_ID25	0x10

/* duplicate resolved by name mangling -- prepend CANTXIDR0 */
#define CANTXIDR0_ID26	0x20

/* duplicate resolved by name mangling -- prepend CANTXIDR0 */
#define CANTXIDR0_ID27	0x40

/* duplicate resolved by name mangling -- prepend CANTXIDR0 */
#define CANTXIDR0_ID28	0x80

/* duplicate resolved by name mangling -- prepend CANTXIDR0 */
#define CANTXIDR0_ID_21	0xff

#define CANTXIDR1	(*(volatile unsigned char *)(REG_BASE + 0x00000171))

/* duplicate resolved by name mangling -- prepend CANTXIDR1 */

#define CANTXIDR1_ID15	0x1

/* duplicate resolved by name mangling -- prepend CANTXIDR1 */
#define CANTXIDR1_ID16	0x2

/* duplicate resolved by name mangling -- prepend CANTXIDR1 */
#define CANTXIDR1_ID17	0x4

/* duplicate resolved by name mangling -- prepend CANTXIDR1 */
#define CANTXIDR1_IDE	0x8

/* duplicate resolved by name mangling -- prepend CANTXIDR1 */
#define CANTXIDR1_SRR	0x10

/* duplicate resolved by name mangling -- prepend CANTXIDR1 */
#define CANTXIDR1_ID18	0x20

/* duplicate resolved by name mangling -- prepend CANTXIDR1 */
#define CANTXIDR1_ID19	0x40

/* duplicate resolved by name mangling -- prepend CANTXIDR1 */
#define CANTXIDR1_ID20	0x80

/* duplicate resolved by name mangling -- prepend CANTXIDR1 */
#define CANTXIDR1_ID_15	0x7

/* duplicate resolved by name mangling -- prepend CANTXIDR1 */
#define CANTXIDR1_ID_18	0xe0

#define CANTXIDR2	(*(volatile unsigned char *)(REG_BASE + 0x00000172))

/* duplicate resolved by name mangling -- prepend CANTXIDR2 */

#define CANTXIDR2_ID7	0x1

/* duplicate resolved by name mangling -- prepend CANTXIDR2 */
#define CANTXIDR2_ID8	0x2

/* duplicate resolved by name mangling -- prepend CANTXIDR2 */
#define CANTXIDR2_ID9	0x4

/* duplicate resolved by name mangling -- prepend CANTXIDR2 */
#define CANTXIDR2_ID10	0x8

/* duplicate resolved by name mangling -- prepend CANTXIDR2 */
#define CANTXIDR2_ID11	0x10

/* duplicate resolved by name mangling -- prepend CANTXIDR2 */
#define CANTXIDR2_ID12	0x20

/* duplicate resolved by name mangling -- prepend CANTXIDR2 */
#define CANTXIDR2_ID13	0x40

/* duplicate resolved by name mangling -- prepend CANTXIDR2 */
#define CANTXIDR2_ID14	0x80

/* duplicate resolved by name mangling -- prepend CANTXIDR2 */
#define CANTXIDR2_ID_7	0xff

#define CANTXIDR3	(*(volatile unsigned char *)(REG_BASE + 0x00000173))

/* duplicate resolved by name mangling -- prepend CANTXIDR3 */

#define CANTXIDR3_RTR	0x1

/* duplicate resolved by name mangling -- prepend CANTXIDR3 */
#define CANTXIDR3_ID0	0x2

/* duplicate resolved by name mangling -- prepend CANTXIDR3 */
#define CANTXIDR3_ID1	0x4

/* duplicate resolved by name mangling -- prepend CANTXIDR3 */
#define CANTXIDR3_ID2	0x8

/* duplicate resolved by name mangling -- prepend CANTXIDR3 */
#define CANTXIDR3_ID3	0x10

/* duplicate resolved by name mangling -- prepend CANTXIDR3 */
#define CANTXIDR3_ID4	0x20

/* duplicate resolved by name mangling -- prepend CANTXIDR3 */
#define CANTXIDR3_ID5	0x40

/* duplicate resolved by name mangling -- prepend CANTXIDR3 */
#define CANTXIDR3_ID6	0x80

/* duplicate resolved by name mangling -- prepend CANTXIDR3 */
#define CANTXIDR3_ID	0xfe

#define CANTXDSR0	(*(volatile unsigned char *)(REG_BASE + 0x00000174))

/* duplicate resolved by name mangling -- prepend CANTXDSR0 */

#define CANTXDSR0_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANTXDSR0 */
#define CANTXDSR0_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANTXDSR0 */
#define CANTXDSR0_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANTXDSR0 */
#define CANTXDSR0_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANTXDSR0 */
#define CANTXDSR0_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANTXDSR0 */
#define CANTXDSR0_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANTXDSR0 */
#define CANTXDSR0_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANTXDSR0 */
#define CANTXDSR0_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANTXDSR0 */
#define CANTXDSR0_DB	0xff

#define CANTXDSR1	(*(volatile unsigned char *)(REG_BASE + 0x00000175))

/* duplicate resolved by name mangling -- prepend CANTXDSR1 */

#define CANTXDSR1_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANTXDSR1 */
#define CANTXDSR1_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANTXDSR1 */
#define CANTXDSR1_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANTXDSR1 */
#define CANTXDSR1_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANTXDSR1 */
#define CANTXDSR1_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANTXDSR1 */
#define CANTXDSR1_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANTXDSR1 */
#define CANTXDSR1_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANTXDSR1 */
#define CANTXDSR1_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANTXDSR1 */
#define CANTXDSR1_DB	0xff

#define CANTXDSR2	(*(volatile unsigned char *)(REG_BASE + 0x00000176))

/* duplicate resolved by name mangling -- prepend CANTXDSR2 */

#define CANTXDSR2_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANTXDSR2 */
#define CANTXDSR2_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANTXDSR2 */
#define CANTXDSR2_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANTXDSR2 */
#define CANTXDSR2_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANTXDSR2 */
#define CANTXDSR2_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANTXDSR2 */
#define CANTXDSR2_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANTXDSR2 */
#define CANTXDSR2_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANTXDSR2 */
#define CANTXDSR2_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANTXDSR2 */
#define CANTXDSR2_DB	0xff

#define CANTXDSR3	(*(volatile unsigned char *)(REG_BASE + 0x00000177))

/* duplicate resolved by name mangling -- prepend CANTXDSR3 */

#define CANTXDSR3_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANTXDSR3 */
#define CANTXDSR3_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANTXDSR3 */
#define CANTXDSR3_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANTXDSR3 */
#define CANTXDSR3_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANTXDSR3 */
#define CANTXDSR3_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANTXDSR3 */
#define CANTXDSR3_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANTXDSR3 */
#define CANTXDSR3_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANTXDSR3 */
#define CANTXDSR3_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANTXDSR3 */
#define CANTXDSR3_DB	0xff

#define CANTXDSR4	(*(volatile unsigned char *)(REG_BASE + 0x00000178))

/* duplicate resolved by name mangling -- prepend CANTXDSR4 */

#define CANTXDSR4_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANTXDSR4 */
#define CANTXDSR4_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANTXDSR4 */
#define CANTXDSR4_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANTXDSR4 */
#define CANTXDSR4_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANTXDSR4 */
#define CANTXDSR4_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANTXDSR4 */
#define CANTXDSR4_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANTXDSR4 */
#define CANTXDSR4_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANTXDSR4 */
#define CANTXDSR4_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANTXDSR4 */
#define CANTXDSR4_DB	0xff

#define CANTXDSR5	(*(volatile unsigned char *)(REG_BASE + 0x00000179))

/* duplicate resolved by name mangling -- prepend CANTXDSR5 */

#define CANTXDSR5_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANTXDSR5 */
#define CANTXDSR5_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANTXDSR5 */
#define CANTXDSR5_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANTXDSR5 */
#define CANTXDSR5_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANTXDSR5 */
#define CANTXDSR5_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANTXDSR5 */
#define CANTXDSR5_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANTXDSR5 */
#define CANTXDSR5_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANTXDSR5 */
#define CANTXDSR5_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANTXDSR5 */
#define CANTXDSR5_DB	0xff

#define CANTXDSR6	(*(volatile unsigned char *)(REG_BASE + 0x0000017A))

/* duplicate resolved by name mangling -- prepend CANTXDSR6 */

#define CANTXDSR6_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANTXDSR6 */
#define CANTXDSR6_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANTXDSR6 */
#define CANTXDSR6_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANTXDSR6 */
#define CANTXDSR6_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANTXDSR6 */
#define CANTXDSR6_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANTXDSR6 */
#define CANTXDSR6_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANTXDSR6 */
#define CANTXDSR6_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANTXDSR6 */
#define CANTXDSR6_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANTXDSR6 */
#define CANTXDSR6_DB	0xff

#define CANTXDSR7	(*(volatile unsigned char *)(REG_BASE + 0x0000017B))

/* duplicate resolved by name mangling -- prepend CANTXDSR7 */

#define CANTXDSR7_DB0	0x1

/* duplicate resolved by name mangling -- prepend CANTXDSR7 */
#define CANTXDSR7_DB1	0x2

/* duplicate resolved by name mangling -- prepend CANTXDSR7 */
#define CANTXDSR7_DB2	0x4

/* duplicate resolved by name mangling -- prepend CANTXDSR7 */
#define CANTXDSR7_DB3	0x8

/* duplicate resolved by name mangling -- prepend CANTXDSR7 */
#define CANTXDSR7_DB4	0x10

/* duplicate resolved by name mangling -- prepend CANTXDSR7 */
#define CANTXDSR7_DB5	0x20

/* duplicate resolved by name mangling -- prepend CANTXDSR7 */
#define CANTXDSR7_DB6	0x40

/* duplicate resolved by name mangling -- prepend CANTXDSR7 */
#define CANTXDSR7_DB7	0x80

/* duplicate resolved by name mangling -- prepend CANTXDSR7 */
#define CANTXDSR7_DB	0xff

#define CANTXDLR	(*(volatile unsigned char *)(REG_BASE + 0x0000017C))

/* duplicate resolved by name mangling -- prepend CANTXDLR */

#define CANTXDLR_DLC0	0x1

/* duplicate resolved by name mangling -- prepend CANTXDLR */
#define CANTXDLR_DLC1	0x2

/* duplicate resolved by name mangling -- prepend CANTXDLR */
#define CANTXDLR_DLC2	0x4

/* duplicate resolved by name mangling -- prepend CANTXDLR */
#define CANTXDLR_DLC3	0x8

/* duplicate resolved by name mangling -- prepend CANTXDLR */
#define CANTXDLR_DLC	0xf

#define CANTXTBPR	(*(volatile unsigned char *)(REG_BASE + 0x0000017F))

#define PRIO0     	0x1
#define PRIO1     	0x2
#define PRIO2     	0x4
#define PRIO3     	0x8
#define PRIO4     	0x10
#define PRIO5     	0x20
#define PRIO6     	0x40
#define PRIO7     	0x80
#define PRIO      	0xff

#define PTT	(*(volatile unsigned char *)(REG_BASE + 0x00000240))

#define PTT0      	0x1
#define PTT1      	0x2
#define PTT2      	0x4
#define PTT3      	0x8
#define PTT4      	0x10
#define PTT5      	0x20
#define PTT6      	0x40
#define PTT7      	0x80

/* duplicate resolved by name mangling -- prepend PTT */
#define PTT_PTT   	0xff

#define PTIT	(*(volatile unsigned char *)(REG_BASE + 0x00000241))

#define PTIT0     	0x1
#define PTIT1     	0x2
#define PTIT2     	0x4
#define PTIT3     	0x8
#define PTIT4     	0x10
#define PTIT5     	0x20
#define PTIT6     	0x40
#define PTIT7     	0x80

/* duplicate resolved by name mangling -- prepend PTIT */
#define PTIT_PTIT 	0xff

#define DDRT	(*(volatile unsigned char *)(REG_BASE + 0x00000242))

#define DDRT0     	0x1
#define DDRT1     	0x2
#define DDRT2     	0x4
#define DDRT3     	0x8
#define DDRT4     	0x10
#define DDRT5     	0x20
#define DDRT6     	0x40
#define DDRT7     	0x80

/* duplicate resolved by name mangling -- prepend DDRT */
#define DDRT_DDRT 	0xff

#define RDRT	(*(volatile unsigned char *)(REG_BASE + 0x00000243))

#define RDRT0     	0x1
#define RDRT1     	0x2
#define RDRT2     	0x4
#define RDRT3     	0x8
#define RDRT4     	0x10
#define RDRT5     	0x20
#define RDRT6     	0x40
#define RDRT7     	0x80

/* duplicate resolved by name mangling -- prepend RDRT */
#define RDRT_RDRT 	0xff

#define PERT	(*(volatile unsigned char *)(REG_BASE + 0x00000244))

#define PERT0     	0x1
#define PERT1     	0x2
#define PERT2     	0x4
#define PERT3     	0x8
#define PERT4     	0x10
#define PERT5     	0x20
#define PERT6     	0x40
#define PERT7     	0x80

/* duplicate resolved by name mangling -- prepend PERT */
#define PERT_PERT 	0xff

#define PPST	(*(volatile unsigned char *)(REG_BASE + 0x00000245))

#define PPST0     	0x1
#define PPST1     	0x2
#define PPST2     	0x4
#define PPST3     	0x8
#define PPST4     	0x10
#define PPST5     	0x20
#define PPST6     	0x40
#define PPST7     	0x80

/* duplicate resolved by name mangling -- prepend PPST */
#define PPST_PPST 	0xff

#define PTS	(*(volatile unsigned char *)(REG_BASE + 0x00000248))

#define PTS0      	0x1
#define PTS1      	0x2
#define PTS2      	0x4
#define PTS3      	0x8
#define PTS4      	0x10
#define PTS5      	0x20
#define PTS6      	0x40
#define PTS7      	0x80

/* duplicate resolved by name mangling -- prepend PTS */
#define PTS_PTS   	0xff

#define PTIS	(*(volatile unsigned char *)(REG_BASE + 0x00000249))

#define PTIS0     	0x1
#define PTIS1     	0x2
#define PTIS2     	0x4
#define PTIS3     	0x8
#define PTIS4     	0x10
#define PTIS5     	0x20
#define PTIS6     	0x40
#define PTIS7     	0x80

/* duplicate resolved by name mangling -- prepend PTIS */
#define PTIS_PTIS 	0xff

#define DDRS	(*(volatile unsigned char *)(REG_BASE + 0x0000024A))

#define DDRS0     	0x1
#define DDRS1     	0x2
#define DDRS2     	0x4
#define DDRS3     	0x8
#define DDRS4     	0x10
#define DDRS5     	0x20
#define DDRS6     	0x40
#define DDRS7     	0x80

/* duplicate resolved by name mangling -- prepend DDRS */
#define DDRS_DDRS 	0xff

#define RDRS	(*(volatile unsigned char *)(REG_BASE + 0x0000024B))

#define RDRS0     	0x1
#define RDRS1     	0x2
#define RDRS2     	0x4
#define RDRS3     	0x8
#define RDRS4     	0x10
#define RDRS5     	0x20
#define RDRS6     	0x40
#define RDRS7     	0x80

/* duplicate resolved by name mangling -- prepend RDRS */
#define RDRS_RDRS 	0xff

#define PERS	(*(volatile unsigned char *)(REG_BASE + 0x0000024C))

#define PERS0     	0x1
#define PERS1     	0x2
#define PERS2     	0x4
#define PERS3     	0x8
#define PERS4     	0x10
#define PERS5     	0x20
#define PERS6     	0x40
#define PERS7     	0x80

/* duplicate resolved by name mangling -- prepend PERS */
#define PERS_PERS 	0xff

#define PPSS	(*(volatile unsigned char *)(REG_BASE + 0x0000024D))

#define PPSS0     	0x1
#define PPSS1     	0x2
#define PPSS2     	0x4
#define PPSS3     	0x8
#define PPSS4     	0x10
#define PPSS5     	0x20
#define PPSS6     	0x40
#define PPSS7     	0x80

/* duplicate resolved by name mangling -- prepend PPSS */
#define PPSS_PPSS 	0xff

#define WOMS	(*(volatile unsigned char *)(REG_BASE + 0x0000024E))

#define WOMS0     	0x1
#define WOMS1     	0x2
#define WOMS2     	0x4
#define WOMS3     	0x8
#define WOMS4     	0x10
#define WOMS5     	0x20
#define WOMS6     	0x40
#define WOMS7     	0x80

/* duplicate resolved by name mangling -- prepend WOMS */
#define WOMS_WOMS 	0xff

#define PTM	(*(volatile unsigned char *)(REG_BASE + 0x00000250))

#define PTM0      	0x1
#define PTM1      	0x2
#define PTM2      	0x4
#define PTM3      	0x8
#define PTM4      	0x10
#define PTM5      	0x20
#define PTM6      	0x40
#define PTM7      	0x80

/* duplicate resolved by name mangling -- prepend PTM */
#define PTM_PTM   	0xff

#define PTIM	(*(volatile unsigned char *)(REG_BASE + 0x00000251))

#define PTIM0     	0x1
#define PTIM1     	0x2
#define PTIM2     	0x4
#define PTIM3     	0x8
#define PTIM4     	0x10
#define PTIM5     	0x20
#define PTIM6     	0x40
#define PTIM7     	0x80

/* duplicate resolved by name mangling -- prepend PTIM */
#define PTIM_PTIM 	0xff

#define DDRM	(*(volatile unsigned char *)(REG_BASE + 0x00000252))

#define DDRM0     	0x1
#define DDRM1     	0x2
#define DDRM2     	0x4
#define DDRM3     	0x8
#define DDRM4     	0x10
#define DDRM5     	0x20
#define DDRM6     	0x40
#define DDRM7     	0x80

/* duplicate resolved by name mangling -- prepend DDRM */
#define DDRM_DDRM 	0xff

#define RDRM	(*(volatile unsigned char *)(REG_BASE + 0x00000253))

#define RDRM0     	0x1
#define RDRM1     	0x2
#define RDRM2     	0x4
#define RDRM3     	0x8
#define RDRM4     	0x10
#define RDRM5     	0x20
#define RDRM6     	0x40
#define RDRM7     	0x80

/* duplicate resolved by name mangling -- prepend RDRM */
#define RDRM_RDRM 	0xff

#define PERM	(*(volatile unsigned char *)(REG_BASE + 0x00000254))

#define PERM0     	0x1
#define PERM1     	0x2
#define PERM2     	0x4
#define PERM3     	0x8
#define PERM4     	0x10
#define PERM5     	0x20
#define PERM6     	0x40
#define PERM7     	0x80

/* duplicate resolved by name mangling -- prepend PERM */
#define PERM_PERM 	0xff

#define PPSM	(*(volatile unsigned char *)(REG_BASE + 0x00000255))

#define PPSM0     	0x1
#define PPSM1     	0x2
#define PPSM2     	0x4
#define PPSM3     	0x8
#define PPSM4     	0x10
#define PPSM5     	0x20
#define PPSM6     	0x40
#define PPSM7     	0x80

/* duplicate resolved by name mangling -- prepend PPSM */
#define PPSM_PPSM 	0xff

#define WOMM	(*(volatile unsigned char *)(REG_BASE + 0x00000256))

#define WOMM0     	0x1
#define WOMM1     	0x2
#define WOMM2     	0x4
#define WOMM3     	0x8
#define WOMM4     	0x10
#define WOMM5     	0x20
#define WOMM6     	0x40
#define WOMM7     	0x80

/* duplicate resolved by name mangling -- prepend WOMM */
#define WOMM_WOMM 	0xff

#define MODRR	(*(volatile unsigned char *)(REG_BASE + 0x00000257))

#define MODRR0    	0x1
#define MODRR1    	0x2
#define MODRR2    	0x4
#define MODRR3    	0x8
#define MODRR4    	0x10
#define MODRR5    	0x20
#define MODRR6    	0x40

/* duplicate resolved by name mangling -- prepend MODRR */
#define MODRR_MODRR	0x7f

#define PTP	(*(volatile unsigned char *)(REG_BASE + 0x00000258))

#define PTP0      	0x1
#define PTP1      	0x2
#define PTP2      	0x4
#define PTP3      	0x8
#define PTP4      	0x10
#define PTP5      	0x20
#define PTP6      	0x40
#define PTP7      	0x80

/* duplicate resolved by name mangling -- prepend PTP */
#define PTP_PTP   	0xff

#define PTIP	(*(volatile unsigned char *)(REG_BASE + 0x00000259))

#define PTIP0     	0x1
#define PTIP1     	0x2
#define PTIP2     	0x4
#define PTIP3     	0x8
#define PTIP4     	0x10
#define PTIP5     	0x20
#define PTIP6     	0x40
#define PTIP7     	0x80

/* duplicate resolved by name mangling -- prepend PTIP */
#define PTIP_PTIP 	0xff

#define DDRP	(*(volatile unsigned char *)(REG_BASE + 0x0000025A))

#define DDRP0     	0x1
#define DDRP1     	0x2
#define DDRP2     	0x4
#define DDRP3     	0x8
#define DDRP4     	0x10
#define DDRP5     	0x20
#define DDRP6     	0x40
#define DDRP7     	0x80

/* duplicate resolved by name mangling -- prepend DDRP */
#define DDRP_DDRP 	0xff

#define RDRP	(*(volatile unsigned char *)(REG_BASE + 0x0000025B))

#define RDRP0     	0x1
#define RDRP1     	0x2
#define RDRP2     	0x4
#define RDRP3     	0x8
#define RDRP4     	0x10
#define RDRP5     	0x20
#define RDRP6     	0x40
#define RDRP7     	0x80

/* duplicate resolved by name mangling -- prepend RDRP */
#define RDRP_RDRP 	0xff

#define PERP	(*(volatile unsigned char *)(REG_BASE + 0x0000025C))

#define PERP0     	0x1
#define PERP1     	0x2
#define PERP2     	0x4
#define PERP3     	0x8
#define PERP4     	0x10
#define PERP5     	0x20
#define PERP6     	0x40
#define PERP7     	0x80

/* duplicate resolved by name mangling -- prepend PERP */
#define PERP_PERP 	0xff

#define PPSP	(*(volatile unsigned char *)(REG_BASE + 0x0000025D))

#define PPSP0     	0x1
#define PPSP1     	0x2
#define PPSP2     	0x4
#define PPSP3     	0x8
#define PPSP4     	0x10
#define PPSP5     	0x20
#define PPSP6     	0x40
#define PPSP7     	0x80

/* duplicate resolved by name mangling -- prepend PPSP */
#define PPSP_PPSP 	0xff

#define PIEP	(*(volatile unsigned char *)(REG_BASE + 0x0000025E))

#define PIEP0     	0x1
#define PIEP1     	0x2
#define PIEP2     	0x4
#define PIEP3     	0x8
#define PIEP4     	0x10
#define PIEP5     	0x20
#define PIEP6     	0x40
#define PIEP7     	0x80

/* duplicate resolved by name mangling -- prepend PIEP */
#define PIEP_PIEP 	0xff

#define PIFP	(*(volatile unsigned char *)(REG_BASE + 0x0000025F))

#define PIFP0     	0x1
#define PIFP1     	0x2
#define PIFP2     	0x4
#define PIFP3     	0x8
#define PIFP4     	0x10
#define PIFP5     	0x20
#define PIFP6     	0x40
#define PIFP7     	0x80

/* duplicate resolved by name mangling -- prepend PIFP */
#define PIFP_PIFP 	0xff

#define PTH	(*(volatile unsigned char *)(REG_BASE + 0x00000260))

#define PTH0      	0x1
#define PTH1      	0x2
#define PTH2      	0x4
#define PTH3      	0x8
#define PTH4      	0x10
#define PTH5      	0x20
#define PTH6      	0x40
#define PTH7      	0x80

/* duplicate resolved by name mangling -- prepend PTH */
#define PTH_PTH   	0xff

#define PTIH	(*(volatile unsigned char *)(REG_BASE + 0x00000261))

#define PTIH0     	0x1
#define PTIH1     	0x2
#define PTIH2     	0x4
#define PTIH3     	0x8
#define PTIH4     	0x10
#define PTIH5     	0x20
#define PTIH6     	0x40
#define PTIH7     	0x80

/* duplicate resolved by name mangling -- prepend PTIH */
#define PTIH_PTIH 	0xff

#define DDRH	(*(volatile unsigned char *)(REG_BASE + 0x00000262))

#define DDRH0     	0x1
#define DDRH1     	0x2
#define DDRH2     	0x4
#define DDRH3     	0x8
#define DDRH4     	0x10
#define DDRH5     	0x20
#define DDRH6     	0x40
#define DDRH7     	0x80

/* duplicate resolved by name mangling -- prepend DDRH */
#define DDRH_DDRH 	0xff

#define RDRH	(*(volatile unsigned char *)(REG_BASE + 0x00000263))

#define RDRH0     	0x1
#define RDRH1     	0x2
#define RDRH2     	0x4
#define RDRH3     	0x8
#define RDRH4     	0x10
#define RDRH5     	0x20
#define RDRH6     	0x40
#define RDRH7     	0x80

/* duplicate resolved by name mangling -- prepend RDRH */
#define RDRH_RDRH 	0xff

#define PERH	(*(volatile unsigned char *)(REG_BASE + 0x00000264))

#define PERH0     	0x1
#define PERH1     	0x2
#define PERH2     	0x4
#define PERH3     	0x8
#define PERH4     	0x10
#define PERH5     	0x20
#define PERH6     	0x40
#define PERH7     	0x80

/* duplicate resolved by name mangling -- prepend PERH */
#define PERH_PERH 	0xff

#define PPSH	(*(volatile unsigned char *)(REG_BASE + 0x00000265))

#define PPSH0     	0x1
#define PPSH1     	0x2
#define PPSH2     	0x4
#define PPSH3     	0x8
#define PPSH4     	0x10
#define PPSH5     	0x20
#define PPSH6     	0x40
#define PPSH7     	0x80

/* duplicate resolved by name mangling -- prepend PPSH */
#define PPSH_PPSH 	0xff

#define PIEH	(*(volatile unsigned char *)(REG_BASE + 0x00000266))

#define PIEH0     	0x1
#define PIEH1     	0x2
#define PIEH2     	0x4
#define PIEH3     	0x8
#define PIEH4     	0x10
#define PIEH5     	0x20
#define PIEH6     	0x40
#define PIEH7     	0x80

/* duplicate resolved by name mangling -- prepend PIEH */
#define PIEH_PIEH 	0xff

#define PIFH	(*(volatile unsigned char *)(REG_BASE + 0x00000267))

#define PIFH0     	0x1
#define PIFH1     	0x2
#define PIFH2     	0x4
#define PIFH3     	0x8
#define PIFH4     	0x10
#define PIFH5     	0x20
#define PIFH6     	0x40
#define PIFH7     	0x80

/* duplicate resolved by name mangling -- prepend PIFH */
#define PIFH_PIFH 	0xff

#define PTJ	(*(volatile unsigned char *)(REG_BASE + 0x00000268))

#define PTJ0      	0x1
#define PTJ1      	0x2
#define PTJ6      	0x40
#define PTJ7      	0x80

/* duplicate resolved by name mangling -- prepend PTJ */
#define PTJ_PTJ   	0x3
#define PTJ_6     	0xc0

#define PTIJ	(*(volatile unsigned char *)(REG_BASE + 0x00000269))

#define PTIJ0     	0x1
#define PTIJ1     	0x2
#define PTIJ6     	0x40
#define PTIJ7     	0x80

/* duplicate resolved by name mangling -- prepend PTIJ */
#define PTIJ_PTIJ 	0x3
#define PTIJ_6    	0xc0

#define DDRJ	(*(volatile unsigned char *)(REG_BASE + 0x0000026A))

#define DDRJ0     	0x1
#define DDRJ1     	0x2
#define DDRJ6     	0x40
#define DDRJ7     	0x80

/* duplicate resolved by name mangling -- prepend DDRJ */
#define DDRJ_DDRJ 	0x3
#define DDRJ_6    	0xc0

#define RDRJ	(*(volatile unsigned char *)(REG_BASE + 0x0000026B))

#define RDRJ0     	0x1
#define RDRJ1     	0x2
#define RDRJ6     	0x40
#define RDRJ7     	0x80

/* duplicate resolved by name mangling -- prepend RDRJ */
#define RDRJ_RDRJ 	0x3
#define RDRJ_6    	0xc0

#define PERJ	(*(volatile unsigned char *)(REG_BASE + 0x0000026C))

#define PERJ0     	0x1
#define PERJ1     	0x2
#define PERJ6     	0x40
#define PERJ7     	0x80

/* duplicate resolved by name mangling -- prepend PERJ */
#define PERJ_PERJ 	0x3
#define PERJ_6    	0xc0

#define PPSJ	(*(volatile unsigned char *)(REG_BASE + 0x0000026D))

#define PPSJ0     	0x1
#define PPSJ1     	0x2
#define PPSJ6     	0x40
#define PPSJ7     	0x80

/* duplicate resolved by name mangling -- prepend PPSJ */
#define PPSJ_PPSJ 	0x3
#define PPSJ_6    	0xc0

#define PIEJ	(*(volatile unsigned char *)(REG_BASE + 0x0000026E))

#define PIEJ0     	0x1
#define PIEJ1     	0x2
#define PIEJ6     	0x40
#define PIEJ7     	0x80

/* duplicate resolved by name mangling -- prepend PIEJ */
#define PIEJ_PIEJ 	0x3
#define PIEJ_6    	0xc0

#define PIFJ	(*(volatile unsigned char *)(REG_BASE + 0x0000026F))

#define PIFJ0     	0x1
#define PIFJ1     	0x2
#define PIFJ6     	0x40
#define PIFJ7     	0x80

/* duplicate resolved by name mangling -- prepend PIFJ */
#define PIFJ_PIFJ 	0x3
#define PIFJ_6    	0xc0

#define CAN4CTL0	(*(volatile unsigned char *)(REG_BASE + 0x00000280))

/* duplicate resolved by name mangling -- prepend CAN4CTL0 */

#define CAN4CTL0_INITRQ	0x1

/* duplicate resolved by name mangling -- prepend CAN4CTL0 */
#define CAN4CTL0_SLPRQ	0x2

/* duplicate resolved by name mangling -- prepend CAN4CTL0 */
#define CAN4CTL0_WUPE	0x4

/* duplicate resolved by name mangling -- prepend CAN4CTL0 */
#define CAN4CTL0_TIME	0x8

/* duplicate resolved by name mangling -- prepend CAN4CTL0 */
#define CAN4CTL0_SYNCH	0x10

/* duplicate resolved by name mangling -- prepend CAN4CTL0 */
#define CAN4CTL0_CSWAI	0x20

/* duplicate resolved by name mangling -- prepend CAN4CTL0 */
#define CAN4CTL0_RXACT	0x40

/* duplicate resolved by name mangling -- prepend CAN4CTL0 */
#define CAN4CTL0_RXFRM	0x80

#define CAN4CTL1	(*(volatile unsigned char *)(REG_BASE + 0x00000281))

/* duplicate resolved by name mangling -- prepend CAN4CTL1 */

#define CAN4CTL1_INITAK	0x1

/* duplicate resolved by name mangling -- prepend CAN4CTL1 */
#define CAN4CTL1_SLPAK	0x2

/* duplicate resolved by name mangling -- prepend CAN4CTL1 */
#define CAN4CTL1_WUPM	0x4

/* duplicate resolved by name mangling -- prepend CAN4CTL1 */
#define CAN4CTL1_LISTEN	0x10

/* duplicate resolved by name mangling -- prepend CAN4CTL1 */
#define CAN4CTL1_LOOPB	0x20

/* duplicate resolved by name mangling -- prepend CAN4CTL1 */
#define CAN4CTL1_CLKSRC	0x40

/* duplicate resolved by name mangling -- prepend CAN4CTL1 */
#define CAN4CTL1_CANE	0x80

#define CAN4BTR0	(*(volatile unsigned char *)(REG_BASE + 0x00000282))

/* duplicate resolved by name mangling -- prepend CAN4BTR0 */

#define CAN4BTR0_BRP0	0x1

/* duplicate resolved by name mangling -- prepend CAN4BTR0 */
#define CAN4BTR0_BRP1	0x2

/* duplicate resolved by name mangling -- prepend CAN4BTR0 */
#define CAN4BTR0_BRP2	0x4

/* duplicate resolved by name mangling -- prepend CAN4BTR0 */
#define CAN4BTR0_BRP3	0x8

/* duplicate resolved by name mangling -- prepend CAN4BTR0 */
#define CAN4BTR0_BRP4	0x10

/* duplicate resolved by name mangling -- prepend CAN4BTR0 */
#define CAN4BTR0_BRP5	0x20

/* duplicate resolved by name mangling -- prepend CAN4BTR0 */
#define CAN4BTR0_SJW0	0x40

/* duplicate resolved by name mangling -- prepend CAN4BTR0 */
#define CAN4BTR0_SJW1	0x80

/* duplicate resolved by name mangling -- prepend CAN4BTR0 */
#define CAN4BTR0_BRP	0x3f

/* duplicate resolved by name mangling -- prepend CAN4BTR0 */
#define CAN4BTR0_SJW	0xc0

#define CAN4BTR1	(*(volatile unsigned char *)(REG_BASE + 0x00000283))

/* duplicate resolved by name mangling -- prepend CAN4BTR1 */

#define CAN4BTR1_TSEG10	0x1

/* duplicate resolved by name mangling -- prepend CAN4BTR1 */
#define CAN4BTR1_TSEG11	0x2

/* duplicate resolved by name mangling -- prepend CAN4BTR1 */
#define CAN4BTR1_TSEG12	0x4

/* duplicate resolved by name mangling -- prepend CAN4BTR1 */
#define CAN4BTR1_TSEG13	0x8

/* duplicate resolved by name mangling -- prepend CAN4BTR1 */
#define CAN4BTR1_TSEG20	0x10

/* duplicate resolved by name mangling -- prepend CAN4BTR1 */
#define CAN4BTR1_TSEG21	0x20

/* duplicate resolved by name mangling -- prepend CAN4BTR1 */
#define CAN4BTR1_TSEG22	0x40

/* duplicate resolved by name mangling -- prepend CAN4BTR1 */
#define CAN4BTR1_SAMP	0x80

/* duplicate resolved by name mangling -- prepend CAN4BTR1 */
#define CAN4BTR1_TSEG_10	0xf

/* duplicate resolved by name mangling -- prepend CAN4BTR1 */
#define CAN4BTR1_TSEG_20	0x70

#define CAN4RFLG	(*(volatile unsigned char *)(REG_BASE + 0x00000284))

/* duplicate resolved by name mangling -- prepend CAN4RFLG */

#define CAN4RFLG_RXF	0x1

/* duplicate resolved by name mangling -- prepend CAN4RFLG */
#define CAN4RFLG_OVRIF	0x2

/* duplicate resolved by name mangling -- prepend CAN4RFLG */
#define CAN4RFLG_TSTAT0	0x4

/* duplicate resolved by name mangling -- prepend CAN4RFLG */
#define CAN4RFLG_TSTAT1	0x8

/* duplicate resolved by name mangling -- prepend CAN4RFLG */
#define CAN4RFLG_RSTAT0	0x10

/* duplicate resolved by name mangling -- prepend CAN4RFLG */
#define CAN4RFLG_RSTAT1	0x20

/* duplicate resolved by name mangling -- prepend CAN4RFLG */
#define CAN4RFLG_CSCIF	0x40

/* duplicate resolved by name mangling -- prepend CAN4RFLG */
#define CAN4RFLG_WUPIF	0x80

/* duplicate resolved by name mangling -- prepend CAN4RFLG */
#define CAN4RFLG_TSTAT	0xc

/* duplicate resolved by name mangling -- prepend CAN4RFLG */
#define CAN4RFLG_RSTAT	0x30

#define CAN4RIER	(*(volatile unsigned char *)(REG_BASE + 0x00000285))

/* duplicate resolved by name mangling -- prepend CAN4RIER */

#define CAN4RIER_RXFIE	0x1

/* duplicate resolved by name mangling -- prepend CAN4RIER */
#define CAN4RIER_OVRIE	0x2

/* duplicate resolved by name mangling -- prepend CAN4RIER */
#define CAN4RIER_TSTATE0	0x4

/* duplicate resolved by name mangling -- prepend CAN4RIER */
#define CAN4RIER_TSTATE1	0x8

/* duplicate resolved by name mangling -- prepend CAN4RIER */
#define CAN4RIER_RSTATE0	0x10

/* duplicate resolved by name mangling -- prepend CAN4RIER */
#define CAN4RIER_RSTATE1	0x20

/* duplicate resolved by name mangling -- prepend CAN4RIER */
#define CAN4RIER_CSCIE	0x40

/* duplicate resolved by name mangling -- prepend CAN4RIER */
#define CAN4RIER_WUPIE	0x80

/* duplicate resolved by name mangling -- prepend CAN4RIER */
#define CAN4RIER_TSTATE	0xc

/* duplicate resolved by name mangling -- prepend CAN4RIER */
#define CAN4RIER_RSTATE	0x30

#define CAN4TFLG	(*(volatile unsigned char *)(REG_BASE + 0x00000286))

/* duplicate resolved by name mangling -- prepend CAN4TFLG */

#define CAN4TFLG_TXE0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TFLG */
#define CAN4TFLG_TXE1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TFLG */
#define CAN4TFLG_TXE2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TFLG */
#define CAN4TFLG_TXE	0x7

#define CAN4TIER	(*(volatile unsigned char *)(REG_BASE + 0x00000287))

/* duplicate resolved by name mangling -- prepend CAN4TIER */

#define CAN4TIER_TXEIE0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TIER */
#define CAN4TIER_TXEIE1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TIER */
#define CAN4TIER_TXEIE2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TIER */
#define CAN4TIER_TXEIE	0x7

#define CAN4TARQ	(*(volatile unsigned char *)(REG_BASE + 0x00000288))

/* duplicate resolved by name mangling -- prepend CAN4TARQ */

#define CAN4TARQ_ABTRQ0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TARQ */
#define CAN4TARQ_ABTRQ1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TARQ */
#define CAN4TARQ_ABTRQ2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TARQ */
#define CAN4TARQ_ABTRQ	0x7

#define CAN4TAAK	(*(volatile unsigned char *)(REG_BASE + 0x00000289))

/* duplicate resolved by name mangling -- prepend CAN4TAAK */

#define CAN4TAAK_ABTAK0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TAAK */
#define CAN4TAAK_ABTAK1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TAAK */
#define CAN4TAAK_ABTAK2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TAAK */
#define CAN4TAAK_ABTAK	0x7

#define CAN4TBSEL	(*(volatile unsigned char *)(REG_BASE + 0x0000028A))

/* duplicate resolved by name mangling -- prepend CAN4TBSEL */

#define CAN4TBSEL_TX0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TBSEL */
#define CAN4TBSEL_TX1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TBSEL */
#define CAN4TBSEL_TX2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TBSEL */
#define CAN4TBSEL_TX	0x7

#define CAN4IDAC	(*(volatile unsigned char *)(REG_BASE + 0x0000028B))

/* duplicate resolved by name mangling -- prepend CAN4IDAC */

#define CAN4IDAC_IDHIT0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDAC */
#define CAN4IDAC_IDHIT1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDAC */
#define CAN4IDAC_IDHIT2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDAC */
#define CAN4IDAC_IDAM0	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDAC */
#define CAN4IDAC_IDAM1	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDAC */
#define CAN4IDAC_IDHIT	0x7

/* duplicate resolved by name mangling -- prepend CAN4IDAC */
#define CAN4IDAC_IDAM	0x30

#define CAN4RXERR	(*(volatile unsigned char *)(REG_BASE + 0x0000028E))

/* duplicate resolved by name mangling -- prepend CAN4RXERR */

#define CAN4RXERR_RXERR0	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXERR */
#define CAN4RXERR_RXERR1	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXERR */
#define CAN4RXERR_RXERR2	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXERR */
#define CAN4RXERR_RXERR3	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXERR */
#define CAN4RXERR_RXERR4	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXERR */
#define CAN4RXERR_RXERR5	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXERR */
#define CAN4RXERR_RXERR6	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXERR */
#define CAN4RXERR_RXERR7	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXERR */
#define CAN4RXERR_RXERR	0xff

#define CAN4TXERR	(*(volatile unsigned char *)(REG_BASE + 0x0000028F))

/* duplicate resolved by name mangling -- prepend CAN4TXERR */

#define CAN4TXERR_TXERR0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXERR */
#define CAN4TXERR_TXERR1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXERR */
#define CAN4TXERR_TXERR2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXERR */
#define CAN4TXERR_TXERR3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXERR */
#define CAN4TXERR_TXERR4	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXERR */
#define CAN4TXERR_TXERR5	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXERR */
#define CAN4TXERR_TXERR6	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXERR */
#define CAN4TXERR_TXERR7	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXERR */
#define CAN4TXERR_TXERR	0xff

#define CAN4IDAR0	(*(volatile unsigned char *)(REG_BASE + 0x00000290))

/* duplicate resolved by name mangling -- prepend CAN4IDAR0 */

#define CAN4IDAR0_AC0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDAR0 */
#define CAN4IDAR0_AC1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDAR0 */
#define CAN4IDAR0_AC2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDAR0 */
#define CAN4IDAR0_AC3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDAR0 */
#define CAN4IDAR0_AC4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDAR0 */
#define CAN4IDAR0_AC5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDAR0 */
#define CAN4IDAR0_AC6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDAR0 */
#define CAN4IDAR0_AC7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDAR0 */
#define CAN4IDAR0_AC	0xff

#define CAN4IDAR1	(*(volatile unsigned char *)(REG_BASE + 0x00000291))

/* duplicate resolved by name mangling -- prepend CAN4IDAR1 */

#define CAN4IDAR1_AC0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDAR1 */
#define CAN4IDAR1_AC1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDAR1 */
#define CAN4IDAR1_AC2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDAR1 */
#define CAN4IDAR1_AC3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDAR1 */
#define CAN4IDAR1_AC4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDAR1 */
#define CAN4IDAR1_AC5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDAR1 */
#define CAN4IDAR1_AC6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDAR1 */
#define CAN4IDAR1_AC7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDAR1 */
#define CAN4IDAR1_AC	0xff

#define CAN4IDAR2	(*(volatile unsigned char *)(REG_BASE + 0x00000292))

/* duplicate resolved by name mangling -- prepend CAN4IDAR2 */

#define CAN4IDAR2_AC0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDAR2 */
#define CAN4IDAR2_AC1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDAR2 */
#define CAN4IDAR2_AC2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDAR2 */
#define CAN4IDAR2_AC3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDAR2 */
#define CAN4IDAR2_AC4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDAR2 */
#define CAN4IDAR2_AC5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDAR2 */
#define CAN4IDAR2_AC6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDAR2 */
#define CAN4IDAR2_AC7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDAR2 */
#define CAN4IDAR2_AC	0xff

#define CAN4IDAR3	(*(volatile unsigned char *)(REG_BASE + 0x00000293))

/* duplicate resolved by name mangling -- prepend CAN4IDAR3 */

#define CAN4IDAR3_AC0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDAR3 */
#define CAN4IDAR3_AC1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDAR3 */
#define CAN4IDAR3_AC2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDAR3 */
#define CAN4IDAR3_AC3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDAR3 */
#define CAN4IDAR3_AC4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDAR3 */
#define CAN4IDAR3_AC5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDAR3 */
#define CAN4IDAR3_AC6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDAR3 */
#define CAN4IDAR3_AC7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDAR3 */
#define CAN4IDAR3_AC	0xff

#define CAN4IDMR0	(*(volatile unsigned char *)(REG_BASE + 0x00000294))

/* duplicate resolved by name mangling -- prepend CAN4IDMR0 */

#define CAN4IDMR0_AM0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDMR0 */
#define CAN4IDMR0_AM1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDMR0 */
#define CAN4IDMR0_AM2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDMR0 */
#define CAN4IDMR0_AM3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDMR0 */
#define CAN4IDMR0_AM4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDMR0 */
#define CAN4IDMR0_AM5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDMR0 */
#define CAN4IDMR0_AM6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDMR0 */
#define CAN4IDMR0_AM7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDMR0 */
#define CAN4IDMR0_AM	0xff

#define CAN4IDMR1	(*(volatile unsigned char *)(REG_BASE + 0x00000295))

/* duplicate resolved by name mangling -- prepend CAN4IDMR1 */

#define CAN4IDMR1_AM0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDMR1 */
#define CAN4IDMR1_AM1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDMR1 */
#define CAN4IDMR1_AM2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDMR1 */
#define CAN4IDMR1_AM3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDMR1 */
#define CAN4IDMR1_AM4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDMR1 */
#define CAN4IDMR1_AM5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDMR1 */
#define CAN4IDMR1_AM6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDMR1 */
#define CAN4IDMR1_AM7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDMR1 */
#define CAN4IDMR1_AM	0xff

#define CAN4IDMR2	(*(volatile unsigned char *)(REG_BASE + 0x00000296))

/* duplicate resolved by name mangling -- prepend CAN4IDMR2 */

#define CAN4IDMR2_AM0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDMR2 */
#define CAN4IDMR2_AM1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDMR2 */
#define CAN4IDMR2_AM2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDMR2 */
#define CAN4IDMR2_AM3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDMR2 */
#define CAN4IDMR2_AM4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDMR2 */
#define CAN4IDMR2_AM5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDMR2 */
#define CAN4IDMR2_AM6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDMR2 */
#define CAN4IDMR2_AM7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDMR2 */
#define CAN4IDMR2_AM	0xff

#define CAN4IDMR3	(*(volatile unsigned char *)(REG_BASE + 0x00000297))

/* duplicate resolved by name mangling -- prepend CAN4IDMR3 */

#define CAN4IDMR3_AM0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDMR3 */
#define CAN4IDMR3_AM1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDMR3 */
#define CAN4IDMR3_AM2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDMR3 */
#define CAN4IDMR3_AM3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDMR3 */
#define CAN4IDMR3_AM4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDMR3 */
#define CAN4IDMR3_AM5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDMR3 */
#define CAN4IDMR3_AM6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDMR3 */
#define CAN4IDMR3_AM7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDMR3 */
#define CAN4IDMR3_AM	0xff

#define CAN4IDAR4	(*(volatile unsigned char *)(REG_BASE + 0x00000298))

/* duplicate resolved by name mangling -- prepend CAN4IDAR4 */

#define CAN4IDAR4_AC0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDAR4 */
#define CAN4IDAR4_AC1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDAR4 */
#define CAN4IDAR4_AC2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDAR4 */
#define CAN4IDAR4_AC3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDAR4 */
#define CAN4IDAR4_AC4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDAR4 */
#define CAN4IDAR4_AC5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDAR4 */
#define CAN4IDAR4_AC6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDAR4 */
#define CAN4IDAR4_AC7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDAR4 */
#define CAN4IDAR4_AC	0xff

#define CAN4IDAR5	(*(volatile unsigned char *)(REG_BASE + 0x00000299))

/* duplicate resolved by name mangling -- prepend CAN4IDAR5 */

#define CAN4IDAR5_AC0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDAR5 */
#define CAN4IDAR5_AC1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDAR5 */
#define CAN4IDAR5_AC2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDAR5 */
#define CAN4IDAR5_AC3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDAR5 */
#define CAN4IDAR5_AC4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDAR5 */
#define CAN4IDAR5_AC5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDAR5 */
#define CAN4IDAR5_AC6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDAR5 */
#define CAN4IDAR5_AC7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDAR5 */
#define CAN4IDAR5_AC	0xff

#define CAN4IDAR6	(*(volatile unsigned char *)(REG_BASE + 0x0000029A))

/* duplicate resolved by name mangling -- prepend CAN4IDAR6 */

#define CAN4IDAR6_AC0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDAR6 */
#define CAN4IDAR6_AC1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDAR6 */
#define CAN4IDAR6_AC2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDAR6 */
#define CAN4IDAR6_AC3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDAR6 */
#define CAN4IDAR6_AC4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDAR6 */
#define CAN4IDAR6_AC5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDAR6 */
#define CAN4IDAR6_AC6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDAR6 */
#define CAN4IDAR6_AC7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDAR6 */
#define CAN4IDAR6_AC	0xff

#define CAN4IDAR7	(*(volatile unsigned char *)(REG_BASE + 0x0000029B))

/* duplicate resolved by name mangling -- prepend CAN4IDAR7 */

#define CAN4IDAR7_AC0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDAR7 */
#define CAN4IDAR7_AC1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDAR7 */
#define CAN4IDAR7_AC2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDAR7 */
#define CAN4IDAR7_AC3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDAR7 */
#define CAN4IDAR7_AC4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDAR7 */
#define CAN4IDAR7_AC5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDAR7 */
#define CAN4IDAR7_AC6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDAR7 */
#define CAN4IDAR7_AC7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDAR7 */
#define CAN4IDAR7_AC	0xff

#define CAN4IDMR4	(*(volatile unsigned char *)(REG_BASE + 0x0000029C))

/* duplicate resolved by name mangling -- prepend CAN4IDMR4 */

#define CAN4IDMR4_AM0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDMR4 */
#define CAN4IDMR4_AM1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDMR4 */
#define CAN4IDMR4_AM2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDMR4 */
#define CAN4IDMR4_AM3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDMR4 */
#define CAN4IDMR4_AM4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDMR4 */
#define CAN4IDMR4_AM5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDMR4 */
#define CAN4IDMR4_AM6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDMR4 */
#define CAN4IDMR4_AM7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDMR4 */
#define CAN4IDMR4_AM	0xff

#define CAN4IDMR5	(*(volatile unsigned char *)(REG_BASE + 0x0000029D))

/* duplicate resolved by name mangling -- prepend CAN4IDMR5 */

#define CAN4IDMR5_AM0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDMR5 */
#define CAN4IDMR5_AM1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDMR5 */
#define CAN4IDMR5_AM2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDMR5 */
#define CAN4IDMR5_AM3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDMR5 */
#define CAN4IDMR5_AM4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDMR5 */
#define CAN4IDMR5_AM5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDMR5 */
#define CAN4IDMR5_AM6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDMR5 */
#define CAN4IDMR5_AM7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDMR5 */
#define CAN4IDMR5_AM	0xff

#define CAN4IDMR6	(*(volatile unsigned char *)(REG_BASE + 0x0000029E))

/* duplicate resolved by name mangling -- prepend CAN4IDMR6 */

#define CAN4IDMR6_AM0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDMR6 */
#define CAN4IDMR6_AM1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDMR6 */
#define CAN4IDMR6_AM2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDMR6 */
#define CAN4IDMR6_AM3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDMR6 */
#define CAN4IDMR6_AM4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDMR6 */
#define CAN4IDMR6_AM5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDMR6 */
#define CAN4IDMR6_AM6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDMR6 */
#define CAN4IDMR6_AM7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDMR6 */
#define CAN4IDMR6_AM	0xff

#define CAN4IDMR7	(*(volatile unsigned char *)(REG_BASE + 0x0000029F))

/* duplicate resolved by name mangling -- prepend CAN4IDMR7 */

#define CAN4IDMR7_AM0	0x1

/* duplicate resolved by name mangling -- prepend CAN4IDMR7 */
#define CAN4IDMR7_AM1	0x2

/* duplicate resolved by name mangling -- prepend CAN4IDMR7 */
#define CAN4IDMR7_AM2	0x4

/* duplicate resolved by name mangling -- prepend CAN4IDMR7 */
#define CAN4IDMR7_AM3	0x8

/* duplicate resolved by name mangling -- prepend CAN4IDMR7 */
#define CAN4IDMR7_AM4	0x10

/* duplicate resolved by name mangling -- prepend CAN4IDMR7 */
#define CAN4IDMR7_AM5	0x20

/* duplicate resolved by name mangling -- prepend CAN4IDMR7 */
#define CAN4IDMR7_AM6	0x40

/* duplicate resolved by name mangling -- prepend CAN4IDMR7 */
#define CAN4IDMR7_AM7	0x80

/* duplicate resolved by name mangling -- prepend CAN4IDMR7 */
#define CAN4IDMR7_AM	0xff

#define CAN4RXIDR0	(*(volatile unsigned char *)(REG_BASE + 0x000002A0))

/* duplicate resolved by name mangling -- prepend CAN4RXIDR0 */

#define CAN4RXIDR0_ID21	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXIDR0 */
#define CAN4RXIDR0_ID22	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXIDR0 */
#define CAN4RXIDR0_ID23	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXIDR0 */
#define CAN4RXIDR0_ID24	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXIDR0 */
#define CAN4RXIDR0_ID25	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXIDR0 */
#define CAN4RXIDR0_ID26	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXIDR0 */
#define CAN4RXIDR0_ID27	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXIDR0 */
#define CAN4RXIDR0_ID28	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXIDR0 */
#define CAN4RXIDR0_ID_21	0xff

#define CAN4RXIDR1	(*(volatile unsigned char *)(REG_BASE + 0x000002A1))

/* duplicate resolved by name mangling -- prepend CAN4RXIDR1 */

#define CAN4RXIDR1_ID15	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXIDR1 */
#define CAN4RXIDR1_ID16	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXIDR1 */
#define CAN4RXIDR1_ID17	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXIDR1 */
#define CAN4RXIDR1_IDE	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXIDR1 */
#define CAN4RXIDR1_SRR	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXIDR1 */
#define CAN4RXIDR1_ID18	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXIDR1 */
#define CAN4RXIDR1_ID19	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXIDR1 */
#define CAN4RXIDR1_ID20	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXIDR1 */
#define CAN4RXIDR1_ID_15	0x7

/* duplicate resolved by name mangling -- prepend CAN4RXIDR1 */
#define CAN4RXIDR1_ID_18	0xe0

#define CAN4RXIDR2	(*(volatile unsigned char *)(REG_BASE + 0x000002A2))

/* duplicate resolved by name mangling -- prepend CAN4RXIDR2 */

#define CAN4RXIDR2_ID7	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXIDR2 */
#define CAN4RXIDR2_ID8	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXIDR2 */
#define CAN4RXIDR2_ID9	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXIDR2 */
#define CAN4RXIDR2_ID10	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXIDR2 */
#define CAN4RXIDR2_ID11	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXIDR2 */
#define CAN4RXIDR2_ID12	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXIDR2 */
#define CAN4RXIDR2_ID13	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXIDR2 */
#define CAN4RXIDR2_ID14	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXIDR2 */
#define CAN4RXIDR2_ID_7	0xff

#define CAN4RXIDR3	(*(volatile unsigned char *)(REG_BASE + 0x000002A3))

/* duplicate resolved by name mangling -- prepend CAN4RXIDR3 */

#define CAN4RXIDR3_RTR	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXIDR3 */
#define CAN4RXIDR3_ID0	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXIDR3 */
#define CAN4RXIDR3_ID1	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXIDR3 */
#define CAN4RXIDR3_ID2	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXIDR3 */
#define CAN4RXIDR3_ID3	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXIDR3 */
#define CAN4RXIDR3_ID4	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXIDR3 */
#define CAN4RXIDR3_ID5	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXIDR3 */
#define CAN4RXIDR3_ID6	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXIDR3 */
#define CAN4RXIDR3_ID	0xfe

#define CAN4RXDSR0	(*(volatile unsigned char *)(REG_BASE + 0x000002A4))

/* duplicate resolved by name mangling -- prepend CAN4RXDSR0 */

#define CAN4RXDSR0_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXDSR0 */
#define CAN4RXDSR0_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXDSR0 */
#define CAN4RXDSR0_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXDSR0 */
#define CAN4RXDSR0_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXDSR0 */
#define CAN4RXDSR0_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXDSR0 */
#define CAN4RXDSR0_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXDSR0 */
#define CAN4RXDSR0_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXDSR0 */
#define CAN4RXDSR0_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXDSR0 */
#define CAN4RXDSR0_DB	0xff

#define CAN4RXDSR1	(*(volatile unsigned char *)(REG_BASE + 0x000002A5))

/* duplicate resolved by name mangling -- prepend CAN4RXDSR1 */

#define CAN4RXDSR1_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXDSR1 */
#define CAN4RXDSR1_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXDSR1 */
#define CAN4RXDSR1_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXDSR1 */
#define CAN4RXDSR1_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXDSR1 */
#define CAN4RXDSR1_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXDSR1 */
#define CAN4RXDSR1_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXDSR1 */
#define CAN4RXDSR1_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXDSR1 */
#define CAN4RXDSR1_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXDSR1 */
#define CAN4RXDSR1_DB	0xff

#define CAN4RXDSR2	(*(volatile unsigned char *)(REG_BASE + 0x000002A6))

/* duplicate resolved by name mangling -- prepend CAN4RXDSR2 */

#define CAN4RXDSR2_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXDSR2 */
#define CAN4RXDSR2_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXDSR2 */
#define CAN4RXDSR2_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXDSR2 */
#define CAN4RXDSR2_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXDSR2 */
#define CAN4RXDSR2_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXDSR2 */
#define CAN4RXDSR2_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXDSR2 */
#define CAN4RXDSR2_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXDSR2 */
#define CAN4RXDSR2_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXDSR2 */
#define CAN4RXDSR2_DB	0xff

#define CAN4RXDSR3	(*(volatile unsigned char *)(REG_BASE + 0x000002A7))

/* duplicate resolved by name mangling -- prepend CAN4RXDSR3 */

#define CAN4RXDSR3_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXDSR3 */
#define CAN4RXDSR3_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXDSR3 */
#define CAN4RXDSR3_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXDSR3 */
#define CAN4RXDSR3_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXDSR3 */
#define CAN4RXDSR3_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXDSR3 */
#define CAN4RXDSR3_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXDSR3 */
#define CAN4RXDSR3_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXDSR3 */
#define CAN4RXDSR3_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXDSR3 */
#define CAN4RXDSR3_DB	0xff

#define CAN4RXDSR4	(*(volatile unsigned char *)(REG_BASE + 0x000002A8))

/* duplicate resolved by name mangling -- prepend CAN4RXDSR4 */

#define CAN4RXDSR4_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXDSR4 */
#define CAN4RXDSR4_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXDSR4 */
#define CAN4RXDSR4_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXDSR4 */
#define CAN4RXDSR4_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXDSR4 */
#define CAN4RXDSR4_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXDSR4 */
#define CAN4RXDSR4_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXDSR4 */
#define CAN4RXDSR4_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXDSR4 */
#define CAN4RXDSR4_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXDSR4 */
#define CAN4RXDSR4_DB	0xff

#define CAN4RXDSR5	(*(volatile unsigned char *)(REG_BASE + 0x000002A9))

/* duplicate resolved by name mangling -- prepend CAN4RXDSR5 */

#define CAN4RXDSR5_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXDSR5 */
#define CAN4RXDSR5_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXDSR5 */
#define CAN4RXDSR5_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXDSR5 */
#define CAN4RXDSR5_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXDSR5 */
#define CAN4RXDSR5_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXDSR5 */
#define CAN4RXDSR5_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXDSR5 */
#define CAN4RXDSR5_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXDSR5 */
#define CAN4RXDSR5_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXDSR5 */
#define CAN4RXDSR5_DB	0xff

#define CAN4RXDSR6	(*(volatile unsigned char *)(REG_BASE + 0x000002AA))

/* duplicate resolved by name mangling -- prepend CAN4RXDSR6 */

#define CAN4RXDSR6_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXDSR6 */
#define CAN4RXDSR6_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXDSR6 */
#define CAN4RXDSR6_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXDSR6 */
#define CAN4RXDSR6_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXDSR6 */
#define CAN4RXDSR6_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXDSR6 */
#define CAN4RXDSR6_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXDSR6 */
#define CAN4RXDSR6_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXDSR6 */
#define CAN4RXDSR6_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXDSR6 */
#define CAN4RXDSR6_DB	0xff

#define CAN4RXDSR7	(*(volatile unsigned char *)(REG_BASE + 0x000002AB))

/* duplicate resolved by name mangling -- prepend CAN4RXDSR7 */

#define CAN4RXDSR7_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXDSR7 */
#define CAN4RXDSR7_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXDSR7 */
#define CAN4RXDSR7_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXDSR7 */
#define CAN4RXDSR7_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXDSR7 */
#define CAN4RXDSR7_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4RXDSR7 */
#define CAN4RXDSR7_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4RXDSR7 */
#define CAN4RXDSR7_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4RXDSR7 */
#define CAN4RXDSR7_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4RXDSR7 */
#define CAN4RXDSR7_DB	0xff

#define CAN4RXDLR	(*(volatile unsigned char *)(REG_BASE + 0x000002AC))

/* duplicate resolved by name mangling -- prepend CAN4RXDLR */

#define CAN4RXDLR_DLC0	0x1

/* duplicate resolved by name mangling -- prepend CAN4RXDLR */
#define CAN4RXDLR_DLC1	0x2

/* duplicate resolved by name mangling -- prepend CAN4RXDLR */
#define CAN4RXDLR_DLC2	0x4

/* duplicate resolved by name mangling -- prepend CAN4RXDLR */
#define CAN4RXDLR_DLC3	0x8

/* duplicate resolved by name mangling -- prepend CAN4RXDLR */
#define CAN4RXDLR_DLC	0xf

#define CAN4TXIDR0	(*(volatile unsigned char *)(REG_BASE + 0x000002B0))

/* duplicate resolved by name mangling -- prepend CAN4TXIDR0 */

#define CAN4TXIDR0_ID21	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXIDR0 */
#define CAN4TXIDR0_ID22	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXIDR0 */
#define CAN4TXIDR0_ID23	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXIDR0 */
#define CAN4TXIDR0_ID24	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXIDR0 */
#define CAN4TXIDR0_ID25	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXIDR0 */
#define CAN4TXIDR0_ID26	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXIDR0 */
#define CAN4TXIDR0_ID27	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXIDR0 */
#define CAN4TXIDR0_ID28	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXIDR0 */
#define CAN4TXIDR0_ID_21	0xff

#define CAN4TXIDR1	(*(volatile unsigned char *)(REG_BASE + 0x000002B1))

/* duplicate resolved by name mangling -- prepend CAN4TXIDR1 */

#define CAN4TXIDR1_ID15	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXIDR1 */
#define CAN4TXIDR1_ID16	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXIDR1 */
#define CAN4TXIDR1_ID17	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXIDR1 */
#define CAN4TXIDR1_IDE	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXIDR1 */
#define CAN4TXIDR1_SRR	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXIDR1 */
#define CAN4TXIDR1_ID18	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXIDR1 */
#define CAN4TXIDR1_ID19	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXIDR1 */
#define CAN4TXIDR1_ID20	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXIDR1 */
#define CAN4TXIDR1_ID_15	0x7

/* duplicate resolved by name mangling -- prepend CAN4TXIDR1 */
#define CAN4TXIDR1_ID_18	0xe0

#define CAN4TXIDR2	(*(volatile unsigned char *)(REG_BASE + 0x000002B2))

/* duplicate resolved by name mangling -- prepend CAN4TXIDR2 */

#define CAN4TXIDR2_ID7	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXIDR2 */
#define CAN4TXIDR2_ID8	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXIDR2 */
#define CAN4TXIDR2_ID9	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXIDR2 */
#define CAN4TXIDR2_ID10	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXIDR2 */
#define CAN4TXIDR2_ID11	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXIDR2 */
#define CAN4TXIDR2_ID12	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXIDR2 */
#define CAN4TXIDR2_ID13	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXIDR2 */
#define CAN4TXIDR2_ID14	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXIDR2 */
#define CAN4TXIDR2_ID_7	0xff

#define CAN4TXIDR3	(*(volatile unsigned char *)(REG_BASE + 0x000002B3))

/* duplicate resolved by name mangling -- prepend CAN4TXIDR3 */

#define CAN4TXIDR3_RTR	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXIDR3 */
#define CAN4TXIDR3_ID0	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXIDR3 */
#define CAN4TXIDR3_ID1	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXIDR3 */
#define CAN4TXIDR3_ID2	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXIDR3 */
#define CAN4TXIDR3_ID3	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXIDR3 */
#define CAN4TXIDR3_ID4	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXIDR3 */
#define CAN4TXIDR3_ID5	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXIDR3 */
#define CAN4TXIDR3_ID6	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXIDR3 */
#define CAN4TXIDR3_ID	0xfe

#define CAN4TXDSR0	(*(volatile unsigned char *)(REG_BASE + 0x000002B4))

/* duplicate resolved by name mangling -- prepend CAN4TXDSR0 */

#define CAN4TXDSR0_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXDSR0 */
#define CAN4TXDSR0_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXDSR0 */
#define CAN4TXDSR0_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXDSR0 */
#define CAN4TXDSR0_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXDSR0 */
#define CAN4TXDSR0_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXDSR0 */
#define CAN4TXDSR0_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXDSR0 */
#define CAN4TXDSR0_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXDSR0 */
#define CAN4TXDSR0_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXDSR0 */
#define CAN4TXDSR0_DB	0xff

#define CAN4TXDSR1	(*(volatile unsigned char *)(REG_BASE + 0x000002B5))

/* duplicate resolved by name mangling -- prepend CAN4TXDSR1 */

#define CAN4TXDSR1_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXDSR1 */
#define CAN4TXDSR1_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXDSR1 */
#define CAN4TXDSR1_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXDSR1 */
#define CAN4TXDSR1_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXDSR1 */
#define CAN4TXDSR1_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXDSR1 */
#define CAN4TXDSR1_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXDSR1 */
#define CAN4TXDSR1_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXDSR1 */
#define CAN4TXDSR1_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXDSR1 */
#define CAN4TXDSR1_DB	0xff

#define CAN4TXDSR2	(*(volatile unsigned char *)(REG_BASE + 0x000002B6))

/* duplicate resolved by name mangling -- prepend CAN4TXDSR2 */

#define CAN4TXDSR2_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXDSR2 */
#define CAN4TXDSR2_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXDSR2 */
#define CAN4TXDSR2_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXDSR2 */
#define CAN4TXDSR2_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXDSR2 */
#define CAN4TXDSR2_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXDSR2 */
#define CAN4TXDSR2_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXDSR2 */
#define CAN4TXDSR2_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXDSR2 */
#define CAN4TXDSR2_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXDSR2 */
#define CAN4TXDSR2_DB	0xff

#define CAN4TXDSR3	(*(volatile unsigned char *)(REG_BASE + 0x000002B7))

/* duplicate resolved by name mangling -- prepend CAN4TXDSR3 */

#define CAN4TXDSR3_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXDSR3 */
#define CAN4TXDSR3_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXDSR3 */
#define CAN4TXDSR3_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXDSR3 */
#define CAN4TXDSR3_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXDSR3 */
#define CAN4TXDSR3_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXDSR3 */
#define CAN4TXDSR3_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXDSR3 */
#define CAN4TXDSR3_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXDSR3 */
#define CAN4TXDSR3_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXDSR3 */
#define CAN4TXDSR3_DB	0xff

#define CAN4TXDSR4	(*(volatile unsigned char *)(REG_BASE + 0x000002B8))

/* duplicate resolved by name mangling -- prepend CAN4TXDSR4 */

#define CAN4TXDSR4_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXDSR4 */
#define CAN4TXDSR4_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXDSR4 */
#define CAN4TXDSR4_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXDSR4 */
#define CAN4TXDSR4_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXDSR4 */
#define CAN4TXDSR4_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXDSR4 */
#define CAN4TXDSR4_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXDSR4 */
#define CAN4TXDSR4_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXDSR4 */
#define CAN4TXDSR4_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXDSR4 */
#define CAN4TXDSR4_DB	0xff

#define CAN4TXDSR5	(*(volatile unsigned char *)(REG_BASE + 0x000002B9))

/* duplicate resolved by name mangling -- prepend CAN4TXDSR5 */

#define CAN4TXDSR5_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXDSR5 */
#define CAN4TXDSR5_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXDSR5 */
#define CAN4TXDSR5_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXDSR5 */
#define CAN4TXDSR5_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXDSR5 */
#define CAN4TXDSR5_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXDSR5 */
#define CAN4TXDSR5_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXDSR5 */
#define CAN4TXDSR5_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXDSR5 */
#define CAN4TXDSR5_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXDSR5 */
#define CAN4TXDSR5_DB	0xff

#define CAN4TXDSR6	(*(volatile unsigned char *)(REG_BASE + 0x000002BA))

/* duplicate resolved by name mangling -- prepend CAN4TXDSR6 */

#define CAN4TXDSR6_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXDSR6 */
#define CAN4TXDSR6_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXDSR6 */
#define CAN4TXDSR6_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXDSR6 */
#define CAN4TXDSR6_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXDSR6 */
#define CAN4TXDSR6_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXDSR6 */
#define CAN4TXDSR6_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXDSR6 */
#define CAN4TXDSR6_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXDSR6 */
#define CAN4TXDSR6_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXDSR6 */
#define CAN4TXDSR6_DB	0xff

#define CAN4TXDSR7	(*(volatile unsigned char *)(REG_BASE + 0x000002BB))

/* duplicate resolved by name mangling -- prepend CAN4TXDSR7 */

#define CAN4TXDSR7_DB0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXDSR7 */
#define CAN4TXDSR7_DB1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXDSR7 */
#define CAN4TXDSR7_DB2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXDSR7 */
#define CAN4TXDSR7_DB3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXDSR7 */
#define CAN4TXDSR7_DB4	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXDSR7 */
#define CAN4TXDSR7_DB5	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXDSR7 */
#define CAN4TXDSR7_DB6	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXDSR7 */
#define CAN4TXDSR7_DB7	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXDSR7 */
#define CAN4TXDSR7_DB	0xff

#define CAN4TXDLR	(*(volatile unsigned char *)(REG_BASE + 0x000002BC))

/* duplicate resolved by name mangling -- prepend CAN4TXDLR */

#define CAN4TXDLR_DLC0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXDLR */
#define CAN4TXDLR_DLC1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXDLR */
#define CAN4TXDLR_DLC2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXDLR */
#define CAN4TXDLR_DLC3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXDLR */
#define CAN4TXDLR_DLC	0xf

#define CAN4TXTBPR	(*(volatile unsigned char *)(REG_BASE + 0x000002BF))

/* duplicate resolved by name mangling -- prepend CAN4TXTBPR */

#define CAN4TXTBPR_PRIO0	0x1

/* duplicate resolved by name mangling -- prepend CAN4TXTBPR */
#define CAN4TXTBPR_PRIO1	0x2

/* duplicate resolved by name mangling -- prepend CAN4TXTBPR */
#define CAN4TXTBPR_PRIO2	0x4

/* duplicate resolved by name mangling -- prepend CAN4TXTBPR */
#define CAN4TXTBPR_PRIO3	0x8

/* duplicate resolved by name mangling -- prepend CAN4TXTBPR */
#define CAN4TXTBPR_PRIO4	0x10

/* duplicate resolved by name mangling -- prepend CAN4TXTBPR */
#define CAN4TXTBPR_PRIO5	0x20

/* duplicate resolved by name mangling -- prepend CAN4TXTBPR */
#define CAN4TXTBPR_PRIO6	0x40

/* duplicate resolved by name mangling -- prepend CAN4TXTBPR */
#define CAN4TXTBPR_PRIO7	0x80

/* duplicate resolved by name mangling -- prepend CAN4TXTBPR */
#define CAN4TXTBPR_PRIO	0xff
#define UNSEC     	0x2
#define CLKSW     	0x4
#define TRACE     	0x8
#define SDV       	0x10
#define ENTAG     	0x20
#define BDMACT    	0x40
#define ENBDM     	0x80
#define CCR0      	0x1
#define CCR1      	0x2
#define CCR2      	0x4
#define CCR3      	0x8
#define CCR4      	0x10
#define CCR5      	0x20
#define CCR6      	0x40
#define CCR7      	0x80
#define CCR       	0xff

/* duplicate resolved by name mangling -- prepend BDMINR */
#define BDMINR_REG11	0x8

/* duplicate resolved by name mangling -- prepend BDMINR */
#define BDMINR_REG12	0x10

/* duplicate resolved by name mangling -- prepend BDMINR */
#define BDMINR_REG13	0x20

/* duplicate resolved by name mangling -- prepend BDMINR */
#define BDMINR_REG14	0x40
#define REG15     	0x80

/* duplicate resolved by name mangling -- prepend BDMINR */
#define BDMINR_REG_11	0xf8

#endif
