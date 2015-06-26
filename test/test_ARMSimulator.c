#include "unity.h"
#include "ARMSimulator.h"
#include "ARMRegisters.h"
#include "ConditionalExecution.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include <stdint.h>
#include "Thumb16bitsTable.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "ModifiedImmediateConstant.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ADDSPRegister.h"

void setUp(void)
{
  initCoreRegister();
  initThumb16bitsOpcode00XXX();
}

void tearDown(void)
{
}


void test_is32or16instruction_given_32bits_instruction_should_return_bit32(void)
{
  uint32_t value = 0xF05F0B0F;      // an example of instruction taken from KEIL assembler
                                        // which is MOVS R11, #0xF
  uint32_t result;

  result = is32or16instruction(value);

  TEST_ASSERT_EQUAL( INSTRUCTION32bits, result);
}



void test_is32or16instruction_given_16bits_instruction_should_return_bit16()
{
  uint32_t value = 0x46E80000;      // an example of instruction taken from KEIL assembler
                                        // which is  MOV R8, SP

  value = is32or16instruction(value);

  TEST_ASSERT_EQUAL( INSTRUCTION16bits, value);

}


void test_ARMSimulator()
{
  uint32_t instruction1 = 0x23FF0000;
  uint32_t instruction2 = 0x24880000;
  uint32_t instruction3 = 0x1b1a0000;
  uint32_t instruction4 = 0x44140000;

  
  ARMSimulator(instruction1);
  ARMSimulator(instruction2);
  ARMSimulator(instruction3);
  ARMSimulator(instruction4);

  printRegister();
}


