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
 * @file    wait.h
 * @brief   Contains some simple wait functions, heavily inspired by
 *          Erich Styger's mcuoneclipse project (McuWait module)
 */

#ifndef APPLICATION_HELPERS_WAIT_H_
#define APPLICATION_HELPERS_WAIT_H_

/* ****************************************************************************
 *                              GLOBAL INCLUDES                               *
 * ****************************************************************************/
#include "system_MK22F51212.h"

/* ****************************************************************************
 *                                 DEFINES                                    *
 * ****************************************************************************/
/* helper macros used to calculate a certain number of cycles */
#define GET_NOF_CYCLES_MS(ms)   ((uint32_t) (ms * (SystemCoreClock / 1000)))
#define GET_NOF_CYCLES_US(us)   ((uint16_t) (us * ((SystemCoreClock / 1000) / 1000)))
#define GET_NOF_CYCLES_100NS(ns100)   ((uint16_t) (ns100 * ((SystemCoreClock / 1000) / 10000)))
#define GET_NOF_CYCLES_NS(ns100)   ((uint16_t) (ns100 * (((SystemCoreClock / 1000) / 1000) / 1000)))

/* the following macros are used to drive the LED wall by "bit banging" ToDo: replace bitbanging by SPI usage */
#define WAIT_SHORT(x)   Wait10Cycles();
#define WAIT_LONG(x)    Wait10Cycles();Wait10Cycles();Wait10Cycles();Wait10Cycles();Wait10Cycles();Wait10Cycles();Wait10Cycles();Wait10Cycles();Wait10Cycles();Wait10Cycles();

/* ****************************************************************************
 *                          FUNCTION DECLARATIONS                             *
 * ****************************************************************************/
/**
 * This function is supposed to wait for 10 MCU instruction cycles.
 */
void Wait10Cycles(void);

/**
 * This function is supposed to wait for a number of milliseconds. Expect
 * accuracy in the range of 20%.
 *
 * \param[in] ms - the number of milliseconds to wait.
 */
void Waitms(uint32_t ms);

/**
 * This function is supposed to wait for a number of microseconds. Expect
 * accuracy in the range of 20%.
 *
 * \param[in] us - the number of microseconds to wait.
 */
void Waitus(uint32_t us);

#endif /* APPLICATION_HELPERS_WAIT_H_ */
