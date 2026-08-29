#include "noice_vuart.h"
#include "debug_visibility.h"

#define VUART_TX (*(volatile unsigned char *)0x2000)
#define VUART_RX (*(volatile unsigned char *)0x2001)
#define VUART_QUEUE_SIZE 256u

FILE_LOCAL char VuartQueue[VUART_QUEUE_SIZE];
FILE_LOCAL unsigned char VuartWriteIndex;
FILE_LOCAL unsigned char VuartReadIndex;
volatile unsigned int NoICE_VuartDroppedRecords;

/*
 * NoICE_VuartInit
 * Initialize the RAM-backed NoICE BDM Virtual UART and its transmit queue.
 * Call once before interrupts are enabled or telemetry is queued.
 */
void NoICE_VuartInit(void)
{
    VUART_TX = 0u;
    VUART_RX = 0u;
    VuartWriteIndex = 0u;
    VuartReadIndex = 0u;
    NoICE_VuartDroppedRecords = 0u;
}

/*
 * NoICE_VuartService
 * Move at most one queued byte into the Virtual UART transmit mailbox when
 * NoICE has consumed the previous byte.  It is nonblocking and should be
 * called frequently from the main loop, never from the timer ISR.
 */
void NoICE_VuartService(void)
{
#if ENABLE_NOICE_VUART
    if ((VUART_TX == 0u) && (VuartReadIndex != VuartWriteIndex)) {
        VUART_TX = (unsigned char)VuartQueue[VuartReadIndex];
        ++VuartReadIndex;
    }
#endif
}

/*
 * NoICE_VuartWrite
 * Atomically enqueue one NUL-terminated text record.  Returns 1 when the full
 * record was queued and 0 when Virtual UART support is disabled or insufficient
 * queue space is available.  A rejected record increments the dropped count;
 * partial records are never transmitted.
 */
unsigned char NoICE_VuartWrite(const char *text)
{
#if ENABLE_NOICE_VUART
    unsigned int length;
    unsigned int free_count;
    unsigned char index;

    length = 0u;
    while (text[length] != '\0') {
        ++length;
    }

    free_count = (unsigned char)(VuartReadIndex - VuartWriteIndex - 1u);
    if (length > free_count) {
        ++NoICE_VuartDroppedRecords;
        return 0u;
    }

    index = VuartWriteIndex;
    while (*text != '\0') {
        VuartQueue[index] = *text;
        ++index;
        ++text;
    }
    VuartWriteIndex = index;
    return 1u;
#else
    (void)text;
    return 0u;
#endif
}
