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

#include "ADDSPRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ConditionalExecution.h"
#include "ShiftOperation.h"
#include <stdio.h>
#include <assert.h>


/*Add SP with Register Encoding T1
    ADD<c> <Rdm>, SP, <Rdm>

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  1| 0  0|DN|1  1  0  1|   Rdm  |                unused               |

  setflags = FALSE

where:
              S                 If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                                update the flags.

              <c><q>            See Standard assembler syntax fields on page A6-7.

              <Rd>              Specifies the destination register. If <Rd> is omitted, this register is SP.
                                The use of the PC as <Rd> in encoding T1 is deprecated.

              <Rm>              Specifies the register that is optionally shifted and used as the second operand.
                                The use of the SP as <Rm> in encoding T1 is deprecated.
                                The use of the PC as <Rm> in encoding T1 and encoding T2 is deprecated.
                                  ==> something wrong abt second statement as keil allow it

              <shift>           Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                                applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                                permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                                register on page A6-12.

              If <Rd> is SP or omitted, <shift> is only permitted to be LSL #0, LSL #1, LSL #2 or LSL #3.
*/
void ADDSPRegisterT1(uint32_t instruction)
{
  uint32_t DN = getBits(instruction,23,23);
  uint32_t Rdm = getBits(instruction,18,16);
  uint32_t d = (DN << 3) | Rdm;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADDSPRegister(d, d, 0, 0, 0);
    //here no need to shift IT State because it will be shifted when return back to its caller which is ADDRegister function
  }
  else
    executeADDSPRegister(d, d, 0, 0, 0);

}



/*Add SP with Register Encoding T2
    ADD<c> SP,<Rm>

  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  1| 0  0|1|     Rm    | 1  0  1|                unused               |

  setflags = FALSE

where:
              S                 If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                                update the flags.

              <c><q>            See Standard assembler syntax fields on page A6-7.

              <Rd>              Specifies the destination register. If <Rd> is omitted, this register is SP.
                                The use of the PC as <Rd> in encoding T1 is deprecated.

              <Rm>              Specifies the register that is optionally shifted and used as the second operand.
                                The use of the SP as <Rm> in encoding T1 is deprecated.
                                The use of the PC as <Rm> in encoding T1 and encoding T2 is deprecated.
                                  ==> something wrong abt second statement as keil allow it

              <shift>           Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                                applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                                permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                                register on page A6-12.

              If <Rd> is SP or omitted, <shift> is only permitted to be LSL #0, LSL #1, LSL #2 or LSL #3.
*/
void ADDSPRegisterT2(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction,22,19);
  uint32_t Rd = 0b1101;

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADDSPRegister(Rd, Rm, 0, 0, 0);
    //here no need to shift IT State because it will be shifted when return back to its caller which is ADDRegister function
  }
  else
    executeADDSPRegister(Rd, Rm, 0, 0, 0);
}


/* Add SP with Register Encoding T3

   ADD{S}<c>.W <Rd>,SP,<Rm>{,<shift>}

   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |1  1  1  0  1  0  1  1  0  0  0 |S| 1  1  0  1 |0|   imm3  |   Rd   |imm2| t |   Rm  |

  t => type

where:
          S           If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.

          <c><q>      See Standard assembler syntax fields on page A6-7.

          <Rd>        Specifies the destination register. If <Rd> is omitted, this register is SP.
                      The use of the PC as <Rd> in encoding T1 is deprecated.

          <Rm>        Specifies the register that is optionally shifted and used as the second operand.
                      The use of the SP as <Rm> in encoding T1 is deprecated.
                      The use of the PC as <Rm> in encoding T1 and encoding T2 is deprecated.
                        ==> something wrong abt second statement as keil allow it

          <shift>     Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and all encodings are permitted. If <shift> is specified, only encoding T3 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.

          If <Rd> is SP or omitted, <shift> is only permitted to be LSL #0, LSL #1, LSL #2 or LSL #3.
*/
void ADDSPRegisterT3(uint32_t instruction)
{
  uint32_t Rm =  getBits(instruction, 3, 0);
  uint32_t Rd = getBits(instruction, 11, 8);
  uint32_t imm2 = getBits(instruction, 7, 6);
  uint32_t imm3 = getBits(instruction, 14, 12);
  uint32_t statusFlag = getBits(instruction, 20, 20);
  uint32_t shiftType = getBits(instruction, 5, 4);

  uint32_t shiftImm = (imm3 << 2 ) | imm2;

  if(Rd == SP)
    assert(shiftType == 0 && shiftImm <= 3);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeADDSPRegister(Rd,Rm, statusFlag, shiftType, shiftImm);
    shiftITState();
  }
  else
    executeADDSPRegister(Rd, Rm, statusFlag, shiftType, shiftImm);

  coreReg[PC] += 4;
}


/* This instruction adds an optionally-shifted register value to the SP value, and writes the result to the
   destination register.

   Input: Rd          destination register
          Rm          register value which will be added with Rn after shifted
          S               indicator for affecting the flag or not
          shiftType       determine what type of shifting is needed
          shiftImmediate  shift range from 0 to 31
*/
void executeADDSPRegister(uint32_t Rd, uint32_t Rm, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate)
{
  uint32_t backupRn = coreReg[SP];
  uint32_t shiftedRm, temp;

  shiftType = determineShiftOperation(shiftType, shiftImmediate);
  shiftedRm = executeShiftOperation(shiftType, shiftImmediate, coreReg[Rm], 0);

  if(Rd == PC)
  {
    uint32_t address = shiftedRm + coreReg[SP] + 4;
    ALUWritePC(address);
  }
  else if(Rm == PC)
  {
    // coreReg[Rd] = alignPC(coreReg[Rm] + 2, 4) + coreReg[SP];
    coreReg[Rd] = shiftedRm + coreReg[SP] + 4;
  }
  else
  {
    temp = coreReg[SP] + shiftedRm;
    coreReg[Rd] = temp;

    if(S == 1)
    {
      updateZeroFlag(coreReg[Rd]);
      updateNegativeFlag(coreReg[Rd]);
      updateOverflowFlagAddition(backupRn, shiftedRm, coreReg[Rd]);
      updateCarryFlagAddition(backupRn, shiftedRm);
    }
  }
}


