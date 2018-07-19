/*
 * delay.c - initialise values used to provide microsecond-order delays
 *
 * note that the timings are quite imprecise (but conservative) unless
 * you are running on at least a 32MHz 68030 processor
 *
 * Copyright (C) 2013-2017 The EmuTOS development team
 *
 * Authors:
 *  RFB    Roger Burrows
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */
#include <osbind.h>
#include "delay.h"

/*
 * initial 1 millisecond delay loop values
 */
#define LOOPS_68060         110000  /* 68060 timing assumes 110MHz for safety */
#define LOOPS_68030         3800    /* 68030 timing assumes 32MHz */
#define LOOPS_68000         760     /* 68000 timing assumes 16MHz */

#define CALIBRATION_TIME    100     /* target # millisecs to run calibration */

#define TIMERD_INTNUM       4       /* for jdisint() etc */

/*
 * global variables
 */
ulong loopcount_1_msec;

/*
 * function prototypes (functions in delayasm.S)
 */
ulong run_calibration(ulong loopcount);
void calibration_timer(void);

/*
 * initialise delay values
 *
 * this is called to set a reasonable default value for the actual calibration loop
 */
void init_delay(int mcpu)
{
    switch(mcpu) {
    case 60:
        loopcount_1_msec = LOOPS_68060;
        break;
    case 40:
    case 30:            /* assumes 68030 */
        loopcount_1_msec = LOOPS_68030;
        break;
    default:            /* assumes 68000 */
        loopcount_1_msec = LOOPS_68000;
    }
}

/*
 * calibrate delay values
 *
 * because this calls run_calibration() which needs to be in supervisor
 * state, we just Supexec the whole function
 *
 * NOTE: we use TimerD so we should restore the RS232 stuff
 */
void calibrate_delay(void)
{
    ulong loopcount, intcount;

	/* we should save the RS232 serial port status here */

    /*
     * disable interrupts then run the calibration
     */
    Jdisint(TIMERD_INTNUM);
    loopcount = CALIBRATION_TIME * loopcount_1_msec;
    intcount = run_calibration(loopcount);
    Jenabint(TIMERD_INTNUM);

    /* we should restore the RS232 serial port stuff here */

    /*
     * intcount is the number of interrupts that occur during 'loopcount'
     * loops.  an interrupt occurs every 1/960 sec (see delayasm.S).
     * so the number of loops per second = loopcount/(intcount/960).
     * so, loops per millisecond = (loopcount*960)/(intcount*1000)
     * = (loopcount*24)/(intcount*25).
     */
    if (intcount)       /* check for valid */
        loopcount_1_msec = (loopcount * 24) / (intcount * 25);
}
