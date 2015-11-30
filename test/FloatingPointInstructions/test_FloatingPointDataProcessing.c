#include "unity.h"
#include <stdint.h>
#include "ExceptionObject.h"
#include "CMNImmediate.h"
#include "ADCImmediate.h"
#include "SBCImmediate.h"
#include "MOVT.h"
#include "SignedAndUnsignedSaturate.h"
#include "SignedAndUnsignedBitFieldExtract.h"
#include "BFIandBFC.h"
#include "RRX.h"
#include "RORImmediate.h"
#include "ORNRegister.h"
#include "TEQRegister.h"
#include "RSBRegister.h"
#include "CLZ.h"
#include "BL.h"
#include "BKPT.h"
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
#include "ADDSPImmediate.h"
#include "STRImmediate.h"
#include "LDRRegister.h"
#include "REV.h"
#include "SignedAndUnsignedExtend.h"
#include "CBZandCBNZ.h"
#include "PUSH.h"
#include "POP.h"
#include "SUBSPImmediate.h"
#include "Thumb32bitsTable.h"
#include "LoadAndWriteMemory.h"
#include "ShiftOperation.h"
#include "ANDImmediate.h"
#include "TSTImmediate.h"
#include "BICImmediate.h"
#include "ORRImmediate.h"
#include "ORNImmediate.h"
#include "MVNImmediate.h"
#include "EORImmediate.h"
#include "TEQImmediate.h"
#include "NOP.h"
#include "MLA.h"
#include "MLS.h"
#include "SignedUnsignedLongMultiplyDivide.h"
#include "VMOV.h"
#include "VMSR.h"
#include "VMRS.h"
#include "VMLAandVMLS.h"
#include "VMUL.h"
#include "VNMLAandVNMLSandVNMUL.h"
#include "VSTM.h"
#include "VSTR.h"
#include "VPUSH.h"
#include "VLDM.h"
#include "VLDR.h"
#include "VPOP.h"
#include "VNEG.h"
#include "VCMP.h"
#include "VABS.h"
#include "VCVT.h"
#include "VSQRT.h"
#include "MiscellaneousInstructions.h"
#include "VADD.h"
#include "VSUB.h"
#include "VDIV.h"
#include "VCVTBandVCVTT.h"
#include "VCVTandVCVTR.h"
#include "VDIV.h"


void setUp(void)
{
  initializeSimulator();
}

void tearDown(void)
{
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VMLA 

// VMLA.F32 s0, s1, s2
void test_VMLA_given_s1_0x2DE12E13_and_s2_0x2D893814_should_get_s0_0x2e0cbccc()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  writeSinglePrecision(0, 0x2e0cbccc);
  
  writeInstructionToMemoryGivenByAddress(0xee000a81, 0x08000046);  // VMLA.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x2de12e132e0cbccc, fpuDoublePrecision[0]);
  TEST_ASSERT_EQUAL(0x2e0cbccc, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



// VMLS.F32 s0, s1, s2
void test_VMLS_given_s1_0x2DE12E13_and_s2_0x2D893814_should_get_s0_0x9BF165F8()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee000ac1, 0x08000046);  // VMLS.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x9BF165F8, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}



/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VMOVImmediate

// VMOV.F32 s5, #0xbff80000
void test_VMOVImmediate_should_load_0xBFF80000_into_s5()
{
  
  writeInstructionToMemoryGivenByAddress(0xeeff2a0f, 0x08000046);  // VMOV.F32 s5, #0xbff80000
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xBFF80000, fpuSinglePrecision[5] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


// VMOV.F32 s5, #0x40000000
void test_VMOVImmediate_should_load_0x40000000_into_s5()
{
  writeInstructionToMemoryGivenByAddress(0xeef02a00, 0x08000046);  // VMOV.F32 s5, #0x40000000
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x40000000, fpuSinglePrecision[5] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VMOVRegister

// VMOV.F32 s6, s2
void test_VMOVRegister_should_load_value_of_s2_into_s6()
{
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xeeb03a41, 0x08000046);  // VMOV.F32 s6, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x2D893814, fpuSinglePrecision[6] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}    

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VNEG

    
// VNEG.F32 s7, s2
void test_VNEG_should_negate_the_value_of_s2_and_put_into_s7()
{
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xeef13a41, 0x08000046);  // VNEG.F32 s7, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xAD893814, fpuSinglePrecision[7] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


// VNEG.F32 s7, s1
void test_VNEG_should_negate_the_value_of_s1_and_put_into_s7()
{
  writeSinglePrecision(1, 0x0DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeef13a60, 0x08000046);  // VNEG.F32 s7, s1
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x8DE12E13, fpuSinglePrecision[7] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VABS
    
// VABS.F32 s8, s7
void test_VABS_given_s7_is_0x8DE12E13_should_get_s8_0x0DE12E13()
{
  writeSinglePrecision(7, 0x8DE12E13);
  
  writeInstructionToMemoryGivenByAddress(0xeeb04ae3, 0x08000046);  // VABS.F32 s8, s7
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x0DE12E13, fpuSinglePrecision[8] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VSQRT
    
//test positive value
// VSQRT.F32 s8, s0
void test_VSQRT_given_s0_is_0x2E0CBCCC_should_get_s8_0x36BDD002()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  
  writeInstructionToMemoryGivenByAddress(0xeeb14ac0, 0x08000046);  // VSQRT.F32 s8, s0
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();
  
  TEST_ASSERT_EQUAL(0x36BDD002, fpuSinglePrecision[8] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VNMLA
    
// VNMLA.F32 s0, s1, s2
void test_VNMLA_given_s1_is_0x2DE12E13_s2_is_0x2D893814_s0_is_0x2E0CBCCC_should_get_s0_0xAE0CBCCC()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee100ac1, 0x08000046);  // VNMLA.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xAE0CBCCC, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VNMLS

// VNMLS.F32 s0, s1, s2
void test_VNMLS_given_s1_is_0x2DE12E13_s2_is_0x2D893814_s0_is_0x2E0CBCCC_should_get_s0_0xAE0CBCCC()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee100a81, 0x08000046);  // VNMLS.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0xAE0CBCCC, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VNMUL
    
// VNMUL.F32 s0, s1, s2
void test_VNMUL_given_s1_is_0x2DE12E13_s2_is_0x2D893814_s0_is_0x2E0CBCCC_should_get_s0_0x9BF165F8()
{
  writeSinglePrecision(0, 0x2E0CBCCC);
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee200ac1, 0x08000046);  // VNMUL.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x9BF165F8, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}


/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VADD

// VADD.F32 s0, s1, s2
void test_VADD_given_s1_is_0x2DE12E13_s2_is_0x2D893814_should_get_s0_0x2E3533148()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee300a81, 0x08000046);  // VADD.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x2E353314, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}
    
/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VSUB
  
// VSUB.F32 s0, s1, s2
void test_VSUB_given_s1_is_0x2DE12E13_s2_is_0x2D893814_should_get_s0_0x2D2FEBFE()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee300ac1, 0x08000046);  // VSUB.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x2D2FEBFE, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000000, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VDIV

// VDIV.F32 s0, s1, s2
void test_VDIV_given_s1_is_0x2DE12E13_s2_is_0x2D893814_should_get_s0_0x2D2FEBFE()
{
  writeSinglePrecision(1, 0x2DE12E13);
  writeSinglePrecision(2, 0x2D893814);
  
  writeInstructionToMemoryGivenByAddress(0xee800a81, 0x08000046);  // VDIV.F32 s0, s1, s2
  coreReg[PC] = 0x08000046;
  
  writeByteToMemory(CPACR, 0x00F00000, 4);  // enable floating point
  armStep();

  TEST_ASSERT_EQUAL(0x3FD20D20, fpuSinglePrecision[0] );
  TEST_ASSERT_EQUAL(0x00000010, coreReg[fPSCR] );
  TEST_ASSERT_EQUAL(0x0800004a, coreReg[PC]);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------*/
    //VCVTB
    
