#include "EORRegister.h"
#include "ITandHints.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ModifiedImmediateConstant.h"
#include "Thumb16bitsTable.h"
#include "ConditionalExecution.h"


/*Exclusive OR Register To Register Encoding T1
 
      EORS    <Rdn>,<Rm>    Outside IT block.
      EOR<c>  <Rdn>,<Rm>    Inside IT block.
  
  Exclusive OR (register) performs a bitwise Exclusive OR of a register value and an optionally-shifted
  register value, and writes the result to the destination register. It can optionally update the condition flags
  based on the result.
  
   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
  |0   1  0  0  0  0| 0  0  0  1|   Rm   |   Rdn  |             unused                  |
   
where:
        S             If present, specifies that the instruction updates the flags. Otherwise, the instruction does not
                      update the flags.
                      
        <c><q>        See Standard assembler syntax fields on page A6-7.
        
        <Rd>          Specifies the destination register. If <Rd> is omitted, this register is the same as <Rn>.
        
        <Rn>          Specifies the register that contains the first operand.
        
        <Rm>          Specifies the register that is optionally shifted and used as the second operand.
        
        <shift>       Specifies the shift to apply to the value read from <Rm>. If <shift> is omitted, no shift is
                      applied and both encodings are permitted. If <shift> is specified, only encoding T2 is
                      permitted. The possible shifts and how they are encoded are described in Shifts applied to a
                      register on page A6-12.
                      
        A special case is that if EOR<c> <Rd>,<Rn>,<Rd> is written with <Rd> and <Rn> both in the range R0-R7, it will
        be assembled using encoding T2 as though EOR<c> <Rd>,<Rn> had been written. To prevent this happening,
        use the .W qualifier.
*/

void EORRegisterT1(uint32_t instruction)
{
  uint32_t Rm = getBits(instruction, 21, 19);
  uint32_t Rdn = getBits(instruction, 18, 16);

  if(inITBlock())
  {
    if( checkCondition(cond) )
      executeEORRegister(Rm, Rdn, 0,-1);
    
    shiftITState();
  }
  else
    executeEORRegister(Rm, Rdn, 1,-1);
  
}




void executeEORRegister(uint32_t Rm, uint32_t Rdn, uint32_t S, uint32_t shiftType)
{
  coreReg[Rdn] = coreReg[Rdn] ^ coreReg[Rm];

  if(S == 1)
  {
    updateZeroFlag(coreReg[Rdn]);
    updateNegativeFlag(coreReg[Rdn]); 
  } 

}