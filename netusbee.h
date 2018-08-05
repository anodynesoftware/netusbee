/*
 * NetUSBee USB driver for TOS
 *
 * netusbee.h: miscellaneous header for netusbee.prg
 *
 * Copyright (C) 2018 Roger Burrows
 *
 * The delay_loop() function is derived from EmuTOS:
 * asm.h - Assembler help routines
 *
 * Copyright (C) 2013-2017 The EmuTOS development team
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

/*
 * quasi-standard C stuff
 */
#ifndef NULL
# define NULL	((void *)0L)
#endif

#define FALSE       (0)
#define TRUE        (!0)

#define UNUSED(x)	(void)x

typedef unsigned long ulong;


/*
 * TOS stuff
 */
#define E_OK		0L
#define ENOSYS		-32L

#define _p_cookie	0x5a0L

#define CPU_COOKIE	0x5f435055L		/* '_CPU' */
#define USB_COOKIE	0x5f555342L		/* '_USB' */


/*
 * delay stuff
 */
/*
 * Loops for the specified count; for a 1 millisecond delay on the
 * current system, use the value in the global 'loopcount_1_msec'.
 */
#define delay_loop(count)                   \
  __extension__                             \
  ({ulong _count = (count);                 \
    __asm__ volatile                        \
    ("0:\n\t"                               \
     "subq.l #1,%0\n\t"                     \
     "jpl    0b"                            \
    :                   /* outputs */       \
    : "d"(_count)       /* inputs  */       \
    : "cc", "memory"    /* clobbered */     \
    );                                      \
  })

static inline void mdelay(ulong millisecs)
{
	while(millisecs--)
		delay_loop(loopcount_1_msec);
}

extern ulong delay_1us;

static inline void udelay(ulong microsecs)
{
	while(microsecs--)
		delay_loop(delay_1us);
}

/*
 * The following is used as a sub-microsecond delay on "slow" machines:
 * on a 68000, it takes 4 cycles, which is 250ns on a 16MHz machine,
 * 500ns on an 8MHz machine.
 */
#define nop                                 \
  __extension__                             \
  ({                                        \
    __asm__ volatile                        \
    (                                       \
     "nop"                                  \
    :                   /* outputs */       \
    :                   /* inputs  */       \
    :                   /* clobbered */     \
    );                                      \
  })


/*
 * MiNT-related stuff
 */
#define FS_INFO		0xf100
#define c_conws(x)	(void)Cconws(x)

static inline unsigned short SWAP16(unsigned short value)
{
	return (value<<8) | (value>>8);
}
