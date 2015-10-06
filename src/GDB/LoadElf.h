/*
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef LoadElf_H
#define LoadElf_H

#include <stdint.h>
#include "GetHeaders.h"

#define ELF_FILE    "C:/Users/user06D/Desktop/GDB-RSP-ARM-Cortex-M-Simulator/data/Ccode.elf"
#define COIDE_ELF_FILE    "C:/Users/user06D/Desktop/ARM-BlinkyLED/Test01/Debug/bin/Test01.elf"
#define getSectionVma(elfData, i)     getSectionVirtualAddress(elfData, i)

void loadElf(ElfData *elfData);
uint32_t getSectionLma(ElfData *elfData, int index);
int isWithinRange(uint32_t address, uint32_t startAddr, uint32_t size);

#endif // LoadElf_H
