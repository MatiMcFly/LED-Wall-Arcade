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
 * @file    application.c
 * @brief   The application's main file
 */

/* ****************************************************************************
 *                              LOCAL INCLUDES                                *
 * ****************************************************************************/
#include "Application.h"
#include "hw.h"
#include "wait.h"

/* ****************************************************************************
 *                                 DEFINES                                    *
 * ****************************************************************************/
#define TOTAL_NOF_PIXELS     512

/* ****************************************************************************
 *                                TYPEDEFS                                    *
 * ****************************************************************************/
/* typically a neopixel is defined as 3x8bit array - G, R, B */
typedef uint8_t Neopixel_t;

/* ****************************************************************************
 *                           FORWARD DECLARATIONS                             *
 * ****************************************************************************/
void ClearPixels(void);

/* ****************************************************************************
 *                          GLOBAL FUNCTION BODIES                            *
 * ****************************************************************************/
void StartApp(void) {
  Neopixel_t neoPixel[] = {0, 0, 255};
  int32_t pixelIndex = 0;
  int32_t selectedPixel = 0;
  int32_t colorIndex = 0;
  int32_t colorBitIndex = 0;

  ClearPixels();

  for (;;) {
    /* create pattern for the current pixel's bit */
    NEOPIXEL_H();
    if ((neoPixel[colorIndex] & (1<<colorBitIndex)) && (selectedPixel == pixelIndex)) {
      WAIT_LONG();
      NEOPIXEL_L();
      WAIT_SHORT();
    } else {
      WAIT_SHORT();
      NEOPIXEL_L();
      WAIT_LONG();
    }
    colorBitIndex++;

    /* increment color index if all color bits have been written */
    if (colorBitIndex == 8) {
      colorBitIndex = 0;
      colorIndex++;
    }

    /* increment pixel index if all colors have been written */
    if (colorIndex == 3) {
      colorIndex = 0;
      pixelIndex++;
    }

    /* increment selected pixel if all pixels have been written */
    if (pixelIndex == TOTAL_NOF_PIXELS) {
      pixelIndex = 0;
      selectedPixel++;

      selectedPixel %= TOTAL_NOF_PIXELS;

      /* also reset the current neopixel sequence by waiting on low */
      Waitms(10);
    }
  }
}

/* ****************************************************************************
 *                          STATIC FUNCTION BODIES                            *
 * ****************************************************************************/
/**
 * Clears all the pixels
 */
void ClearPixels(void) {
  int pixelIndex = 0;

  /* make sure the neopixel line is cleared for a new pattern */
  NEOPIXEL_L();
  Waitus(100);

  /* create pattern for bit-baningly clearing the pixels */
  while (pixelIndex++ < (TOTAL_NOF_PIXELS * 24)) {
    NEOPIXEL_H();
    WAIT_SHORT();
    NEOPIXEL_L();
    WAIT_LONG();
  }

  Waitus(100);
}
