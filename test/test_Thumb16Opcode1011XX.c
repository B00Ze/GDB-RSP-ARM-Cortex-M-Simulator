#include "unity.h"
#include "ModifiedImmediateConstant.h"
#include "ConditionalExecution.h"
#include "Thumb16bitsTable.h"
#include "StatusRegisters.h"
#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "getMask.h"
#include "ARMSimulator.h"
#include "ITandHints.h"
#include "ADDImmediate.h"
#include "LSLImmediate.h"
#include "LSRImmediate.h"
#include "MOVRegister.h"
#include "ASRImmediate.h"
#include "MOVImmediate.h"
#include "CMPImmediate.h"
#include "ADDImmediate.h"
#include "SUBImmediate.h"
#include "ADDRegister.h"
#include "SUBRegister.h"
#include "ADDSPRegister.h"
#include "ANDRegister.h"
#include "LSLRegister.h"
#include "LSRRegister.h"
#include "ASRRegister.h"
#include "CMPRegister.h"
#include "CMNRegister.h"
#include "EORRegister.h"
#include "ORRRegister.h"
#include "RORRegister.h"
#include "MVNRegister.h"
#include "BICRegister.h"
#include "ADCRegister.h"
#include "BX.h"
#include "BLXRegister.h"
#include "MOVRegister.h"
#include "CMPRegister.h"
#include "MULRegister.h"
#include "TSTRegister.h"
#include "RSBImmediate.h"
#include "SBCRegister.h"
#include "UnconditionalAndConditionalBranch.h"
#include "STRRegister.h"
#include "LDRImmediate.h"
#include "MemoryBlock.h"
#include "LDRLiteral.h"
#include "ErrorSignal.h"
#include "SVC.h"
#include "ADR.h"
#include "ADDSPRegister.h"
#include "ADDSPImmediate.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"



void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //IT block
  
// test ITTTT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf010000_should_change_coreReg_to_0x03000000(void)
{
  uint32_t instruction = 0xbf010000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x03000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test ITTT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf020000_should_change_coreReg_to_0x05000000(void)
{
  uint32_t instruction = 0xbf020000;
  
  ARMSimulator(instruction);
  
  TEST_ASSERT_EQUAL(0x05000000, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test ITT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf040000_should_change_coreReg_to_0x01000400(void)
{
  uint32_t instruction = 0xbf040000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x01000400, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test IT EQ 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf080000_should_change_coreReg_to_0x01000800(void)
{
  uint32_t instruction = 0xbf080000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x01000800, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( EQ ,cond);
}


// test IT MI 
void test_ITandHints_given_coreReg_0x00000000_instruction_0xbf480000_should_change_coreReg_to_0x01004800(void)
{
  uint32_t instruction = 0xbf480000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x01004800, coreReg[xPSR]);
  TEST_ASSERT_EQUAL( MI ,cond);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //ADD SP Immediate T1
  
//test case when carry is 1
//test add SP,SP,#0x14
void test_ADDSPImmediateT2_given_carry_is_1_SP_0x20001000_and_offset_20_should_get_SP_0x20001014()
{
  setCarryFlag();
  coreReg[SP] = 0x20001000;
  uint32_t instruction = 0xb0050000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x20001014, coreReg[SP]);

}



//test case when carry is 0
//test add SP,SP,#0x14
void test_ADDSPImmediateT2_given_carry_is_0_SP_0x20001000_and_offset_20_should_get_SP_0x20001014()
{
  resetCarryFlag();
  coreReg[SP] = 0x20001000;
  uint32_t instruction = 0xb0050000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x20001014, coreReg[SP]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //REV T1
  
//test REV r2,r3
void test_REVT1_given_r3_0xdeadbeef_should_get_r2_0xefbeadde()
{
  coreReg[3] = 0xdeadbeef;
  uint32_t instruction = 0xba1a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xefbeadde, coreReg[2]);
}



//test REV r2,r7
void test_REVT1_given_r7_0x10101010_should_get_r2_0x10101010()
{
  coreReg[7] = 0x10101010;
  uint32_t instruction = 0xba3a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x10101010, coreReg[2]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //REV16 T1
  
//test REV16 r2,r3
void test_REV16T1_given_r3_0xdeadbeef_should_get_r2_0xaddeefbe()
{
  coreReg[3] = 0xdeadbeef;
  uint32_t instruction = 0xba5a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xaddeefbe, coreReg[2]);
}


//test REV16 r2,r7
void test_REV16T1_given_r7_0x10101010_should_get_r2_0x10101010()
{
  coreReg[7] = 0x10101010;
  uint32_t instruction = 0xba7a0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x10101010, coreReg[2]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
  //REVSH T1
  
//test REVSH r2,r3
void test_REVSHT1_given_r3_0xdeadbeef_should_get_r2_0xffffefbe()
{
  coreReg[3] = 0xdeadbeef;
  uint32_t instruction = 0xbada0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0xffffefbe, coreReg[2]);
}


//test REVSH r2,r7
void test_REVSHT1_given_r7_0x10101010_should_get_r2_0x00001010()
{
  coreReg[7] = 0x10101010;
  uint32_t instruction = 0xbafa0000;
  
  ARMSimulator(instruction);
  TEST_ASSERT_EQUAL(0x00001010, coreReg[2]);
}