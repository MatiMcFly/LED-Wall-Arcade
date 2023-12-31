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

/******************************************************************************
 *                                   INCLUDES                                 *
 ******************************************************************************/
#include "hw.h"
#include "fsl_port.h"

/******************************************************************************
 *                                FUNCTION BODIES                             *
 ******************************************************************************/
void hwInit() {
  /* enable clock for Port C and D */
  CLOCK_EnableClock(kCLOCK_PortC);
  CLOCK_EnableClock(kCLOCK_PortD);

  /* setup PTC2 as output (onboard LED) */
  ONBOARD_LED_OFF();
  PORT_SetPinMux(PORTC, 2U, kPORT_MuxAsGpio);
  GPIOC->PDDR |= 0x4; /* set PTC2 as output */

  /* setup PTD3 as output (neopixel DOUT) */
  NEOPIXEL_L();
  PORT_SetPinMux(PORTD, 3U, kPORT_MuxAsGpio);
  GPIOD->PDDR |= 0x8;

  ONBOARD_LED_ON();
  ONBOARD_LED_OFF();
  ONBOARD_LED_ON();
  ONBOARD_LED_OFF();
}
