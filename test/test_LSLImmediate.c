#include "unity.h"
#include "LSLImmediate.h"
#include "ARMRegisters.h"
#include "StatusRegisters.h"
#include "getBits.h"
#include "getMask.h"
#include "MOVRegister.h"
#include <stdint.h>

void setUp(void)
{
  coreReg = initCoreRegister();
  initStatusRegister();
}

void tearDown(void)
{
}


//test LSLS r2,r1,#2 given r1 = 0x01
void test_LSLImmediateT1_given_0x008A_should_shift_left_r1_2_times_and_write_to_R2_no_flag_set(void)
{
  uint32_t instruction = 0x008A0000;
  
  coreReg->reg[1].data = 1;                             //set R1 to be 1
  LSLImmediateT1(instruction);
  
  TEST_ASSERT_EQUAL(0x01, coreReg->reg[1].data);        
  TEST_ASSERT_EQUAL(0x04, coreReg->reg[2].data);        //after shift 2 times, should get 0x04
  TEST_ASSERT_EQUAL(0x01000000, StatusRegisters);
  destroyCoreRegister(coreReg);
}

//boundary test, minimum shift
//test LSLS r1,#0 given r1 = 0x01
void test_LSLImmediateT1_given_0x0009_should_shift_left_r1_2_times_and_write_to_R1_no_flag_set(void)
{
  uint32_t instruction = 0x00090000;
  
  coreReg->reg[1].data = 1;                             //set R1 to be 1
  LSLImmediateT1(instruction);
         
  TEST_ASSERT_EQUAL(0x01, coreReg->reg[1].data);        //will execute MOVRegisterT2
  TEST_ASSERT_EQUAL(0x01000000, StatusRegisters);
  destroyCoreRegister(coreReg);
}

//boundary test, maximum shift
//test LSLS r1,#31 given r1 = 0x01
void test_LSLImmediateT1_given_0x07C9_should_shift_left_r1_31_times_and_write_to_R1_negative_flag_set(void)
{
  uint32_t instruction = 0x07C90000;
  
  coreReg->reg[1].data = 1;                                   //set R1 to be 1
  LSLImmediateT1(instruction);
  TEST_ASSERT_EQUAL(0x80000000, coreReg->reg[1].data);        //after shift 31 times, should get 0x80000000
  TEST_ASSERT_EQUAL(1, isNegative() );
  destroyCoreRegister(coreReg);
}











