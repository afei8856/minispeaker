/*
 *  linux/include/asm-mips/mach-jz4780/dma.h
 *
 *  JZ4780 DMA definition.
 *
 *  Copyright (C) 2008 Ingenic Semiconductor Inc.
 *
 *  Author: <cwjia@ingenic.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_JZ4780_DMA_H__
#define __ASM_JZ4780_DMA_H__

#include <linux/interrupt.h>
#include <asm/io.h>			/* need byte IO */
#include <linux/spinlock.h>		/* And spinlocks */
#include <linux/delay.h>
#include <asm/system.h>

/*
 * Descriptor structure for JZ4780 DMA engine
 * Note: this structure must always be aligned to a 16-bytes boundary.
 */

/* old descriptor 4-word */
typedef struct {
	volatile u32 dcmd;	/* DCMD value for the current transfer */
	volatile u32 dsadr;	/* DSAR value for the current transfer */
	volatile u32 dtadr;	/* DTAR value for the current transfer */
	volatile u32 ddadr;	/* Points to the next descriptor + transfer count */
} jz_dma_desc;

/* new descriptor 8-word */
typedef struct {
	volatile u32 dcmd;	/* DCMD value for the current transfer */
	volatile u32 dsadr;	/* DSAR value for the current transfer */
	volatile u32 dtadr;	/* DTAR value for the current transfer */
	volatile u32 ddadr;	/* Points to the next descriptor + transfer count */
	volatile u32 dstrd;     /* DMA source and target stride address */
	volatile u32 dreqt;     /* DMA request type for current transfer */
	volatile u32 reserved0;	/* Reserved */
	volatile u32 reserved1;	/* Reserved */
} jz_dma_desc_8word;

/* new descriptor 8-word */
typedef struct {
	volatile u32 dcmd;	/* DCMD value for the current transfer */
	volatile u32 dsadr;	/* DSAR value for the current transfer */
	volatile u32 dtadr;	/* DTAR value for the current transfer */
	volatile u32 dcnt;	/* transfer count */
	volatile u32 dstrd; /* DMA source and target stride address */
	volatile u32 dreqt; /* DMA request type for current transfer */
	volatile u32 dnt;	/* NAND detect timer enable(15) and value(0~5), and Tail counter(22~16)*/
	volatile u32 ddadr;	/* Next descriptor address(31~4)  */
} jz_bdma_desc_8word;

/* DMA Device ID's follow */
enum {
	DMA_ID_AUTO = 0,		/* Auto-request */
//	DMA_ID_TSSI_RX,		/* TSSI receive fifo full request */
	DMA_ID_UART3_TX,	/* UART3 transmit-fifo-empty request */
	DMA_ID_UART3_RX,	/* UART3 receve-fifo-full request */
	DMA_ID_UART2_TX,	/* UART2 transmit-fifo-empty request */
	DMA_ID_UART2_RX,	/* UART2 receve-fifo-full request */
	DMA_ID_UART1_TX,	/* UART1 transmit-fifo-empty request */
	DMA_ID_UART1_RX,	/* UART1 receve-fifo-full request */
	DMA_ID_UART0_TX,	/* UART0 transmit-fifo-empty request */
	DMA_ID_UART0_RX,	/* UART0 receve-fifo-full request */
	DMA_ID_SSI0_TX,		/* SSI0 transmit-fifo-full request */
	DMA_ID_SSI0_RX,		/* SSI0 receive-fifo-empty request */
	DMA_ID_AIC_TX,		/* AIC transmit-fifo-full request */
	DMA_ID_AIC_RX,		/* AIC receive-fifo-empty request */
	DMA_ID_TCU_OVERFLOW,	/* TCU channel n overflow interrupt */
	DMA_ID_SADC,		/* SADC transfer request */
	DMA_ID_MSC0,
	DMA_ID_MSC1,
	DMA_ID_MSC2,
	DMA_ID_MCU_BCH,
	DMA_ID_MCU_NAND,
	DMA_ID_MCU_TCSM,
	DMA_ID_MCU_MSG,
	DMA_ID_SSI1_TX,		/* SSI1 transmit-fifo-full request */
	DMA_ID_SSI1_RX,		/* SSI1 receive-fifo-empty request */
	DMA_ID_PCM0_TX,
	DMA_ID_PCM0_RX,
	DMA_ID_PCM1_TX,
	DMA_ID_PCM1_RX,
	DMA_ID_RAW_SET,
	DMA_ID_I2C0_RX,
	DMA_ID_I2C0_TX,
	DMA_ID_I2C1_RX,
	DMA_ID_I2C1_TX,
	DMA_ID_I2C2_RX,
	DMA_ID_I2C2_TX,
	DMA_ID_MAX
};

/* DMA modes, simulated by sw */
#define DMA_MODE_READ	0x0  /* I/O to memory, no autoinit, increment, single mode */
#define DMA_MODE_WRITE	0x1  /* memory to I/O, no autoinit, increment, single mode */
#define DMA_AUTOINIT	0x2
#define DMA_MODE_MASK	0x3

struct jz_dma_chan {
	int dev_id;	/* DMA ID: this channel is allocated if >=0, free otherwise */
	unsigned int io;        /* DMA channel number */
	const char *dev_str;    /* string describes the DMA channel */
	int irq;                /* DMA irq number */
	void *irq_dev;          /* DMA private device structure */
	unsigned int fifo_addr; /* physical fifo address of the requested device */
	unsigned int cntl;	/* DMA controll */
	unsigned int mode;      /* DMA configuration */
	unsigned int source;    /* DMA request source */
};

#if defined(__ASSEMBLY__) || defined(__LANGUAGE_ASSEMBLY)
        #ifndef __MIPS_ASSEMBLER
                #define __MIPS_ASSEMBLER
        #endif
        #define REG8(addr)      (addr)
        #define REG16(addr)     (addr)
        #define REG32(addr)     (addr)
#else
        #define REG8(addr)      *((volatile unsigned char *)(addr))
        #define REG16(addr)     *((volatile unsigned short *)(addr))
        #define REG32(addr)     *((volatile unsigned int *)(addr))

        #define INREG8(x)               ((unsigned char)(*(volatile unsigned char *)(x)))
        #define OUTREG8(x, y)           *(volatile unsigned char *)(x) = (y)
        #define SETREG8(x, y)           OUTREG8(x, INREG8(x)|(y))
        #define CLRREG8(x, y)           OUTREG8(x, INREG8(x)&~(y))
        #define CMSREG8(x, y, m)        OUTREG8(x, (INREG8(x)&~(m))|(y))

        #define INREG16(x)              ((unsigned short)(*(volatile unsigned short *)(x)))
        #define OUTREG16(x, y)          *(volatile unsigned short *)(x) = (y)
        #define SETREG16(x, y)          OUTREG16(x, INREG16(x)|(y))
        #define CLRREG16(x, y)          OUTREG16(x, INREG16(x)&~(y))
        #define CMSREG16(x, y, m)       OUTREG16(x, (INREG16(x)&~(m))|(y))

        #define INREG32(x)              ((unsigned int)(*(volatile unsigned int *)(x)))
        #define OUTREG32(x, y)          *(volatile unsigned int *)(x) = (y)
        #define SETREG32(x, y)          OUTREG32(x, INREG32(x)|(y))
        #define CLRREG32(x, y)          OUTREG32(x, INREG32(x)&~(y))
        #define CMSREG32(x, y, m)       OUTREG32(x, (INREG32(x)&~(m))|(y))

#endif


#define BIT0            (1 << 0)
#define BIT1            (1 << 1)
#define BIT2            (1 << 2)
#define BIT3            (1 << 3)
#define BIT4            (1 << 4)
#define BIT5            (1 << 5)
#define BIT6            (1 << 6)
#define BIT7            (1 << 7)
#define BIT8            (1 << 8)
#define BIT9            (1 << 9)
#define BIT10           (1 << 10)
#define BIT11           (1 << 11)
#define BIT12           (1 << 12)
#define BIT13           (1 << 13)
#define BIT14           (1 << 14)
#define BIT15           (1 << 15)
#define BIT16           (1 << 16)
#define BIT17           (1 << 17)
#define BIT18           (1 << 18)
#define BIT19           (1 << 19)
#define BIT20           (1 << 20)
#define BIT21           (1 << 21)
#define BIT22           (1 << 22)
#define BIT23           (1 << 23)
#define BIT24           (1 << 24)
#define BIT25           (1 << 25)
#define BIT26           (1 << 26)
#define BIT27           (1 << 27)
#define BIT28           (1 << 28)
#define BIT29           (1 << 29)
#define BIT30           (1 << 30)
#define BIT31           (1 << 31)

/* Generate the bit field mask from msb to lsb */
#define BITS_H2L(msb, lsb)  ((0xFFFFFFFF >> (32-((msb)-(lsb)+1))) << (lsb))

/* Get the bit field value from the data which is read from the register */
#define get_bf_value(data, lsb, mask)  (((data) & (mask)) >> (lsb))

/*
extern struct jz_dma_chan jz_dma_table[];


#define DMA_8BIT_RX_CMD					\
	DMAC_DCMD_DAI |					\
	DMAC_DCMD_SWDH_8 | DMAC_DCMD_DWDH_32 |		\
	DMAC_DCMD_DS_8BIT | DMAC_DCMD_RDIL_IGN

#define DMA_8BIT_TX_CMD					\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_8 |		\
	DMAC_DCMD_DS_8BIT | DMAC_DCMD_RDIL_IGN

#define DMA_16BIT_RX_CMD				\
	DMAC_DCMD_DAI |					\
	DMAC_DCMD_SWDH_16 | DMAC_DCMD_DWDH_32 |		\
	DMAC_DCMD_DS_16BIT | DMAC_DCMD_RDIL_IGN

#define DMA_16BIT_TX_CMD				\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_16 |		\
	DMAC_DCMD_DS_16BIT | DMAC_DCMD_RDIL_IGN

#define DMA_32BIT_RX_CMD				\
	DMAC_DCMD_DAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_32 |		\
	DMAC_DCMD_DS_32BIT | DMAC_DCMD_RDIL_IGN

#define DMA_32BIT_TX_CMD				\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_32 |		\
	DMAC_DCMD_DS_32BIT | DMAC_DCMD_RDIL_IGN

#define DMA_16BYTE_RX_CMD				\
	DMAC_DCMD_DAI |					\
	DMAC_DCMD_SWDH_8 | DMAC_DCMD_DWDH_32 |		\
	DMAC_DCMD_DS_16BYTE | DMAC_DCMD_RDIL_IGN

#define DMA_16BYTE_TX_CMD				\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_8 |		\
	DMAC_DCMD_DS_16BYTE | DMAC_DCMD_RDIL_IGN

#define DMA_32BYTE_RX_CMD				\
	DMAC_DCMD_DAI |					\
	DMAC_DCMD_SWDH_8 | DMAC_DCMD_DWDH_32 |		\
	DMAC_DCMD_DS_32BYTE | DMAC_DCMD_RDIL_IGN

#define DMA_32BYTE_TX_CMD				\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_8 |		\
	DMAC_DCMD_DS_32BYTE | DMAC_DCMD_RDIL_IGN

#define DMA_AIC_32_32BYTE_TX_CMD		       	\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_32 |		\
	DMAC_DCMD_DS_32BYTE | DMAC_DCMD_RDIL_IGN
#define DMA_AIC_32_16BYTE_TX_CMD		       	\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_32 |		\
	DMAC_DCMD_DS_16BYTE | DMAC_DCMD_RDIL_IGN

#define DMA_AIC_32_16BYTE_RX_CMD			\
	DMAC_DCMD_DAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_32 |		\
	DMAC_DCMD_DS_16BYTE | DMAC_DCMD_RDIL_IGN

#define DMA_AIC_16BIT_TX_CMD				\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_16 | DMAC_DCMD_DWDH_16 |		\
	DMAC_DCMD_DS_16BIT | DMAC_DCMD_RDIL_IGN

#define DMA_AIC_16BIT_RX_CMD				\
	DMAC_DCMD_DAI |					\
	DMAC_DCMD_SWDH_16 | DMAC_DCMD_DWDH_16 |		\
	DMAC_DCMD_DS_16BIT | DMAC_DCMD_RDIL_IGN

#define DMA_AIC_16BYTE_RX_CMD				\
	DMAC_DCMD_DAI |					\
	DMAC_DCMD_SWDH_16 | DMAC_DCMD_DWDH_16 |		\
	DMAC_DCMD_DS_16BYTE | DMAC_DCMD_RDIL_IGN

#define DMA_AIC_16BYTE_TX_CMD				\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_16 | DMAC_DCMD_DWDH_16 |		\
	DMAC_DCMD_DS_16BYTE | DMAC_DCMD_RDIL_IGN

#define DMA_AIC_16BYTE_TX_CMD_UC			\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_16 |		\
	DMAC_DCMD_DS_16BYTE | DMAC_DCMD_RDIL_IGN

#define DMA_AIC_TX_CMD_UNPACK				\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_16 | DMAC_DCMD_DWDH_16 |		\
	DMAC_DCMD_DS_32BIT | DMAC_DCMD_RDIL_IGN

#define DMA_AIC_TX_CMD_PACK				\
	DMAC_DCMD_SAI |					\
	DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_32 |		\
	DMAC_DCMD_DS_32BIT | DMAC_DCMD_RDIL_IGN
*/
/*extern int jz_request_dma(int dev_id,
			  const char *dev_str,
			  irqreturn_t (*irqhandler)(int, void *),
			  unsigned long irqflags,
			  void *irq_dev_id);
*/
/*
extern void jz_stop_dma(unsigned int chan);
extern void jz_free_dma(unsigned int dmanr);

extern int jz_dma_read_proc(char *buf, char **start, off_t fpos,
			      int length, int *eof, void *data);
extern void dump_jz_dma_channel(unsigned int dmanr);
extern void dump_jz_bdma_channel(unsigned int dmanr);

extern void enable_dma(unsigned int dmanr);
extern void disable_dma(unsigned int dmanr);
extern void set_dma_addr(unsigned int dmanr, unsigned int phyaddr);
extern void set_dma_count(unsigned int dmanr, unsigned int bytecnt);
extern void set_dma_mode(unsigned int dmanr, unsigned int mode);
extern void jz_set_oss_dma(unsigned int dmanr, unsigned int mode, unsigned int audio_fmt);
extern void jz_set_alsa_dma(unsigned int dmanr, unsigned int mode, unsigned int audio_fmt);
extern void jz_set_dma_src_width(int dmanr, int nbit);
extern void jz_set_dma_dest_width(int dmanr, int nbit);
extern void jz_set_dma_block_size(int dmanr, int nbyte);
extern unsigned int get_dma_residue(unsigned int dmanr);
extern spinlock_t  dma_spin_lock;



*/
/* Clear the 'DMA Pointer Flip Flop'.
 * Write 0 for LSB/MSB, 1 for MSB/LSB access.
 */
//#define clear_dma_ff(channel)
/*
static __inline__ struct jz_dma_chan *get_dma_chan(unsigned int dmanr)
{
	if (dmanr > MAX_DMA_NUM
	    || jz_dma_table[dmanr].dev_id < 0)
		return NULL;
	return &jz_dma_table[dmanr];
}

static __inline__ int dma_halted(unsigned int dmanr)
{
	struct jz_dma_chan *chan = get_dma_chan(dmanr);
	if (!chan)
		return 1;
	return  __dmac_channel_transmit_halt_detected(dmanr) ? 1 : 0;
}

static __inline__ unsigned int get_dma_mode(unsigned int dmanr)
{
	struct jz_dma_chan *chan = get_dma_chan(dmanr);
	if (!chan)
		return 0;
	return chan->mode;
}

static __inline__ void clear_dma_done(unsigned int dmanr)
{
	struct jz_dma_chan *chan = get_dma_chan(dmanr);
	if (!chan)
		return;
	REG_DMAC_DCCSR(chan->io) &= ~(DMAC_DCCSR_HLT | DMAC_DCCSR_TT | DMAC_DCCSR_AR);
}

static __inline__ void clear_dma_halt(unsigned int dmanr)
{
	struct jz_dma_chan *chan = get_dma_chan(dmanr);
	if (!chan)
		return;
	REG_DMAC_DCCSR(chan->io) &= ~(DMAC_DCCSR_HLT);
	REG_DMAC_DMACR &= ~(DMAC_DMACR_HLT);
}

static __inline__ void clear_dma_flag(unsigned int dmanr)
{
	struct jz_dma_chan *chan = get_dma_chan(dmanr);
	if (!chan)
		return;
	REG_DMAC_DCCSR(chan->io) &= ~(DMAC_DCCSR_HLT | DMAC_DCCSR_TT | DMAC_DCCSR_AR);
	REG_DMAC_DMACR &= ~(DMAC_DMACR_HLT | DMAC_DMACR_AR);
}

static __inline__ void set_dma_page(unsigned int dmanr, char pagenr)
{
}

static __inline__ unsigned int get_dma_done_status(unsigned int dmanr)
{
	unsigned long dccsr;
	struct jz_dma_chan *chan = get_dma_chan(dmanr);
	if (!chan)
		return 0;
	dccsr = REG_DMAC_DCCSR(chan->io);
	return dccsr & (DMAC_DCCSR_HLT | DMAC_DCCSR_TT | DMAC_DCCSR_AR);
}

static __inline__ int get_dma_done_irq(unsigned int dmanr)
{
	struct jz_dma_chan *chan = get_dma_chan(dmanr);
	if (!chan)
		return -1;
	return chan->irq;
}
*/
#endif  /* __ASM_JZ4780_DMA_H__ */
