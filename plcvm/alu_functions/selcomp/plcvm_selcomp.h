/*
 * plcvm_selcomp.h
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

#ifndef PLCVM_SELCOMP_H_
#define PLCVM_SELCOMP_H_

uint8_t fnc_alu_selmax(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_SELMAX) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_ULINT)
    *VAR_PTR(VT_ULINT,0) = 0;

    uint16_t cnt;
    TYPE_VT_ULINT max = 0;
    for (cnt = 0; cnt < *t; cnt++) {
        uint8_t type = (*((TYPE_VT_ULINT*) vm->hp[cnt].var));
        if (!(ANY_BIT(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        if (*VAR_PTR(VT_ULINT,PICK(1 - cnt)) > max)
            max = *VAR_PTR(VT_ULINT,PICK(1 - cnt));
    }
    *VAR_PTR(VT_ULINT,0) = max;

    *alu = 0;
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_selmin(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_SELMIN) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_ULINT)
    *VAR_PTR(VT_ULINT,0) = 0;

    uint16_t cnt;
    TYPE_VT_ULINT min = *VAR_PTR(VT_ULINT,*n);
    for (cnt = 0; cnt < *t; cnt++) {
        uint8_t type = (*((TYPE_VT_ULINT*) vm->hp[cnt].var));
        if (!(ANY_BIT(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        if (*VAR_PTR(VT_ULINT,PICK(1 - cnt)) < min)
            min = *VAR_PTR(VT_ULINT,PICK(1 - cnt));
    }
    *VAR_PTR(VT_ULINT,0) = min;

    *alu = 0;
    POP(*n)
    return RC_OK;
}

uint8_t fnc_alu_selmux(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_SELMUX) ");
#endif
    if ((*n > *t) || (*t == 0)) // K > available entries
        return RC_VAR_ERROR;

    *alu = vm->ds[*n + 2];
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_cmpgrt(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPGRT) ");
#endif
    if (*t == 0)
        return RC_VAR_ERROR;

    bool res = false;
    uint16_t cnt;
    for (cnt = 0; *n < *t; cnt++)
        res = res && (*VAR_PTR(VT_DWORD,PICK(cnt + 1)) > *VAR_PTR(VT_DWORD,PICK(cnt + 2)));

    *alu = res;
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_cmpgeq(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPGEQ) ");
#endif
    if (*t == 0)
        return RC_VAR_ERROR;

    bool res = false;
    uint16_t cnt;
    for (cnt = 0; *n < *t; cnt++)
        res = res && (*VAR_PTR(VT_DWORD,PICK(cnt + 1)) >= *VAR_PTR(VT_DWORD,PICK(cnt + 2)));

    *alu = res;
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_cmpequ(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPEQU) ");
#endif
    if (*t == 0)
        return RC_VAR_ERROR;

    bool res = false;
    uint16_t cnt;
    for (cnt = 0; *n < *t; cnt++)
        res = res && (*VAR_PTR(VT_DWORD,PICK(cnt + 1)) == *VAR_PTR(VT_DWORD,PICK(cnt + 2)));

    *alu = res;
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_cmples(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPLES) ");
#endif
    if (*t == 0)
        return RC_VAR_ERROR;

    bool res = false;
    uint16_t cnt;
    for (cnt = 0; *n < *t; cnt++)
        res = res && (*VAR_PTR(VT_DWORD,PICK(cnt + 1)) <= *VAR_PTR(VT_DWORD,PICK(cnt + 2)));

    *alu = res;
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_cmplth(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPLTH) ");
#endif
    if (*t == 0)
        return RC_VAR_ERROR;

    bool res = false;
    uint16_t cnt;
    for (cnt = 0; *n < *t; cnt++)
        res = res && (*VAR_PTR(VT_DWORD,PICK(cnt + 1)) < *VAR_PTR(VT_DWORD,PICK(cnt + 2)));

    *alu = res;
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_cmpneq(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPNEQ) ");
#endif
    *alu = *VAR_PTR(VT_DWORD,PICK(*t)) != *VAR_PTR(VT_DWORD,PICK(*n));
    POP(1)
    return RC_OK;
}

#endif /*PLCVM_ALU_1_H_*/
