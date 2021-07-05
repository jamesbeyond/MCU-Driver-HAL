/* Parser for C and Objective-C.
   Copyright (C) 1987-2021 Free Software Foundation, Inc.

   Parser actions based on the old Bison parser; structure somewhat
   influenced by and fragments based on the C++ parser.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/* TODO:

   Make sure all relevant comments, and all relevant code from all
   actions, brought over from old parser.  Verify exact correspondence
   of syntax accepted.

   Add testcases covering every input symbol in every state in old and
   new parsers.

   Include full syntax for GNU C, including erroneous cases accepted
   with error messages, in syntax productions in comments.

   Make more diagnostics in the front end generally take an explicit
   location rather than implicitly using input_location.  */

#include "hal/PinNameAliases.h"
#include "hal/spi_api.h"

int main()
{
    spi_t spi_object;
    uint8_t ret;
    uint8_t val = 0xAA;

    spi_init(
        &spi_object,
        ARDUINO_UNO_SPI_MOSI,
        ARDUINO_UNO_SPI_MISO,
        ARDUINO_UNO_SPI_SCK,
        ARDUINO_UNO_SPI_CS
    );
    
    ret = spi_master_write(&spi_object, val);

    while(1);
}