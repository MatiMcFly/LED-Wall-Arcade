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
 * @file    hw.h
 * @brief   Sourcefiles used for HW initializations
 */
#ifndef APPLICATION_HARDWARE_HW_H_
#define APPLICATION_HARDWARE_HW_H_

/******************************************************************************
 *                             GLOBAL INCLUDES                                *
 ******************************************************************************/
#include "fsl_gpio.h"

/******************************************************************************
 *                                 MACROS                                     *
 ******************************************************************************/
/** activating/ deactivating the TinyK22's onboard LED */
#define ONBOARD_LED_ON()     (GPIOC->PCOR |= 0x4)
#define ONBOARD_LED_OFF()    (GPIOC->PSOR |= 0x4)

/** activating/deactivating the pin for control of the DIN line */
#define NEOPIXEL_H()         (GPIOD->PSOR |= 0x8)
#define NEOPIXEL_L()         (GPIOD->PCOR |= 0x8)

/******************************************************************************
 *                          FUNCTION DECLARATIONS                             *
 ******************************************************************************/
/**
 * hwInit: calls all init functions of the used hardware.
 */
void hwInit();

#endif /* APPLICATION_HARDWARE_HW_H_ */
