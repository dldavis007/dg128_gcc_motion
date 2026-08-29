#ifndef NOICE_VUART_H
#define NOICE_VUART_H

#define ENABLE_NOICE_VUART 1 /* Set to zero for stand-alone production use. */

/* Number of complete output records rejected because the queue was full. */
extern volatile unsigned int NoICE_VuartDroppedRecords;

/* Initialize the BDM mailbox and software transmit queue. */
void NoICE_VuartInit(void);

/* Nonblocking foreground service; transfers at most one queued byte. */
void NoICE_VuartService(void);

/* Queue an entire string; return zero rather than enqueue a partial record. */
unsigned char NoICE_VuartWrite(const char *text);

#endif
