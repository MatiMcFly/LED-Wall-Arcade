/*
 * MIT License
 *
 * Copyright (c) 2023 Matthias Schaer
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the “Software”),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/**
 * @file    wait.c
 * @brief   Contains some simple wait functions, heavily inspired by
 *          Erich Styger's mcuoneclipse project (McuWait module)
 */

/* ****************************************************************************
 *                              LOCAL INCLUDES                                *
 * ****************************************************************************/
#include "wait.h"

/* ****************************************************************************
 *                          GLOBAL FUNCTION BODIES                            *
 * ****************************************************************************/
__attribute__((naked, no_instrument_function))
void Wait10Cycles(void) {
  __asm(
      "nop   \n\t"
      "nop   \n\t"
      "nop   \n\t"
      "bx lr \n\t"
  );
}

__attribute__((naked, no_instrument_function))
void Wait100Cycles(void) {
  __asm (
   /* bl to here:               [4] */
   "push {r0}   \n\t"        /* [2] */
   "movs r0, #0 \n\t"        /* [1] */
   "loop:       \n\t"
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "add r0,#1   \n\t"        /* [1] */
   "cmp r0,#9   \n\t"        /* [1] */
   "bls loop    \n\t"        /* [3] taken, [1] not taken */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "nop         \n\t"        /* [1] */
   "pop {r0}    \n\t"        /* [2] */
   "bx lr       \n\t"        /* [3] */
  );
}

void WaitNofCycles(uint16_t cycles) {
  int32_t counter = cycles;

  /* wait in 100 steps if possible */
  while(counter > 100) {
    Wait100Cycles();
    counter -= 100;
  }

  /* wait in 10 steps if possible */
  while(counter > 10) {
    Wait10Cycles();
    counter -= 10;
  }
}

void WaitNofCyclesLong(uint32_t cycles) {
  /* wait 60000 cycles at a time (reduces function call overhead) */
  while (cycles > 60000) {
    WaitNofCycles(60000);
    cycles -= 60000;
  }

  /* wait for the remaining cycles */
  WaitNofCycles(cycles);
}

void Waitms(uint32_t msCount) {
  uint32_t nofCyclesPer_ms = GET_NOF_CYCLES_MS(1);

  /* wait for the calculated number of cycles, in 1ms steps */
  while (msCount) {
    WaitNofCyclesLong(nofCyclesPer_ms);
    msCount--;
  }
}

void Waitus(uint32_t usCount) {
  uint32_t nofCyclesPer_us = GET_NOF_CYCLES_US(1);

  /* wait for the calculated number of cycles, in 1us steps */
  while (usCount > 0) {
    WaitNofCyclesLong(nofCyclesPer_us);
    usCount--;
  }
}
