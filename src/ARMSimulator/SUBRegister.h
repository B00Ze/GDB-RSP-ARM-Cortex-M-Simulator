#ifndef SUBRegister_H
#define SUBRegister_H

#include "ARMRegisters.h"
#include "getAndSetBits.h"
#include "StatusRegisters.h"
#include <stdint.h>
#include "ModifiedImmediateConstant.h"

void SUBRegisterToRegisterT1(uint32_t instruction);
void SUBRegisterT2(uint32_t instruction);
void executeSUBRegister(uint32_t Rm, uint32_t Rd, uint32_t Rn, uint32_t S, uint32_t shiftType, uint32_t shiftImmediate);

#endif // SUBRegister_H
