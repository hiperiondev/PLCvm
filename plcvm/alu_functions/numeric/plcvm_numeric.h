/*
 * plcvm_numeric.h
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

#ifndef __PLCVM_NUMERIC_H__
#define __PLCVM_NUMERIC_H__

#include <math.h>

uint8_t fnc_alu_numabs(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NUMABS) ");
#endif
    if (!(ANY_NUM(VAR_TYPE(*t))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = abs(*VAR_PTR(VT_LREAL,*t));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numsqr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NUMSQR) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = sqrt(*VAR_PTR(VT_LREAL,*t));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numlon(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NUMLON) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = log(*VAR_PTR(VT_LREAL,*t));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numlog(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NUMLOG) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = log10(*VAR_PTR(VT_LREAL,*t));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numsin(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NUMSIN) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = sin(*VAR_PTR(VT_LREAL,*t));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numcos(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NUMCOS) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = cos(*VAR_PTR(VT_LREAL,*t));
    *((TYPE_VT_LREAL*) vm->hp[0].var) = cos(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numtan(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NUMTAN) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;
    if (*((TYPE_VT_LREAL*) vm->hp[*t].var))
        return RC_EXPTN;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = tan(*VAR_PTR(VT_LREAL,*t));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numasn(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NUMASN) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = asin(*VAR_PTR(VT_LREAL,*t));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numacs(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NUMACS) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = acos(*VAR_PTR(VT_LREAL,*t));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numatn(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NUMATN) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = atan(*VAR_PTR(VT_LREAL,*t));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_athadd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_ATHADD) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = 0;

    uint16_t cnt;
    for (cnt = 0; cnt < *t; cnt++) {
        uint8_t type = (*((TYPE_VT_LREAL*) vm->hp[PICK(1 - cnt)].var));
        if (!(ANY_NUM(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;
        *VAR_PTR(VT_LREAL,0) += *VAR_PTR(VT_LREAL,PICK(1 - cnt));
    }

    POP(*t)
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_athmul(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_ATHMUL) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = 0;

    uint16_t cnt;
    for (cnt = 0; cnt < *t; cnt++) {
           uint8_t type = (*((TYPE_VT_LREAL*) vm->hp[PICK(1 - cnt)].var));
           if (!(ANY_NUM(VAR_TYPE(type))))
               return RC_VAR_NOT_ALLWD;
           *VAR_PTR(VT_LREAL,0) *= *VAR_PTR(VT_LREAL,PICK(1 - cnt));
       }

    *alu = 0;
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_athsub(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_ATHSUB) ");
#endif
    if (!(ANY_NUM(VAR_TYPE(*t)) || ANY_NUM(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = *VAR_PTR(VT_LREAL,*t) - *VAR_PTR(VT_LREAL,*n);

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_athdiv(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_ATHDIV) ");
#endif
    if (!(ANY_NUM(VAR_TYPE(*t)) || ANY_NUM(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;
    if (*((TYPE_VT_LREAL*) vm->hp[*n].var) == 0)
        return RC_EXPTN;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = *VAR_PTR(VT_LREAL,*t) / *VAR_PTR(VT_LREAL,*n);

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_athmod(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_ATHMOD) ");
#endif
    if (!(ANY_NUM(VAR_TYPE(*t)) || ANY_NUM(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;
    if (*((TYPE_VT_LREAL*) vm->hp[*n].var) == 0)
        return RC_EXPTN;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = fmodf(*VAR_PTR(VT_LREAL,*t), *VAR_PTR(VT_LREAL,*n));

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_athexp(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_ATHEXP) ");
#endif
    if (!(ANY_NUM(VAR_TYPE(*t)) || ANY_NUM(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL)
    *VAR_PTR(VT_LREAL,0) = pow(*VAR_PTR(VT_LREAL,*t),*VAR_PTR(VT_LREAL,*n));

    *alu = 0;
    POP(1)
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_athmov(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_ATHMOV) ");
#endif
    return RC_OK;
}

#endif /*__PLCVM_NUMERIC_H__*/
