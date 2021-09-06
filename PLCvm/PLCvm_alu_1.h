/*
 * PLCvm_alu_1.h
 *
 * Copyright 2021 Emiliano Gonzalez LU3VEA (egonzalez . hiperion @ gmail . com))
 * * Project Site: https://github.com/hiperiondev/PLCvm *
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef PLCVM_ALU_1_H_
#define PLCVM_ALU_1_H_

// 00
uint8_t fnc_alu_cnvtot(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CNVTOT) ");
#endif
    return RC_OK;
}

// 01
uint8_t fnc_alu_cnvtrc(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CNVTRC) ");
#endif
    return RC_OK;
}

// 03
uint8_t fnc_alu_numabs(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMABS) ");
#endif
    return RC_OK;
}

// 04
uint8_t fnc_alu_numsqr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMSQR) ");
#endif
    return RC_OK;
}

// 05
uint8_t fnc_alu_numlon(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMLON) ");
#endif
    return RC_OK;
}

// 06
uint8_t fnc_alu_numlog(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMLOG) ");
#endif
    return RC_OK;
}

// 07
uint8_t fnc_alu_numexp(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMEXP) ");
#endif
    return RC_OK;
}

// 08
uint8_t fnc_alu_numsin(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMSIN) ");
#endif
    return RC_OK;
}

// 09
uint8_t fnc_alu_numcos(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMCOS) ");
#endif
    return RC_OK;
}

// 10
uint8_t fnc_alu_numtan(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMTAN) ");
#endif
    return RC_OK;
}

// 11
uint8_t fnc_alu_numasn(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMASN) ");
#endif
    return RC_OK;
}

// 12
uint8_t fnc_alu_numacs(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMACS) ");
#endif
    return RC_OK;
}

// 13
uint8_t fnc_alu_numatn(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMATN) ");
#endif
    return RC_OK;
}

// 14
uint8_t fnc_alu_athadd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHADD) ");
#endif
    return RC_OK;
}

// 15
uint8_t fnc_alu_athmul(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHMUL) ");
#endif
    return RC_OK;
}

// 16
uint8_t fnc_alu_athsub(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHSUB) ");
#endif
    return RC_OK;
}

// 17
uint8_t fnc_alu_athdiv(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHDIV) ");
#endif
    return RC_OK;
}

// 18
uint8_t fnc_alu_athmod(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHMOD) ");
#endif
    return RC_OK;
}

// 19
uint8_t fnc_alu_athexp(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHEXP) ");
#endif
    return RC_OK;
}

// 20
uint8_t fnc_alu_athmov(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHMOV) ");
#endif
    return RC_OK;
}

// 21
uint8_t fnc_alu_bitshl(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_BITSHL) ");
#endif
    return RC_OK;
}

// 22
uint8_t fnc_alu_bitshr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_BITSHR) ");
#endif
    return RC_OK;
}

// 23
uint8_t fnc_alu_bitror(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_BITROR) ");
#endif
    return RC_OK;
}

// 24
uint8_t fnc_alu_bitrol(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_BITROL) ");
#endif
    return RC_OK;
}

// 25
uint8_t fnc_alu_cmpand(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CMPAND) ");
#endif
    return RC_OK;
}

// 26
uint8_t fnc_alu_cmporf(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CMPORF) ");
#endif
    return RC_OK;
}

// 27
uint8_t fnc_alu_cmpxor(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CMPXOR) ");
#endif
    return RC_OK;
}

// 28
uint8_t fnc_alu_cmpnot(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CMPNOT) ");
#endif
    return RC_OK;
}

// 29
uint8_t fnc_alu_selsel(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_SELSEL) ");
#endif
    return RC_OK;
}

// 30
uint8_t fnc_alu_selmax(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_SELMAX) ");
#endif
    return RC_OK;
}

// 31
uint8_t fnc_alu_selmin(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_SELMIN) ");
#endif
    return RC_OK;
}

// 3
uint8_t fnc_alu_sellmt(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_SELLMT) ");
#endif
    return RC_OK;
}

#endif /* PLCVM_ALU_1_H_ */
