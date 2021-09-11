/*
 * plcvm_bitwisebool.h
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

#ifndef __PLCVM_BITWISEBOOL_H__
#define __PLCVM_BITWISEBOOL_H__

uint8_t fnc_alu_bitshl(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_BITSHL) ");
#endif
    if (!(ANY_BIT(VAR_TYPE(*t)) || ANY_BIT(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_ULINT)
    *VAR_PTR(VT_ULINT,0) = *VAR_PTR(VT_ULINT,*t) << *VAR_PTR(VT_ULINT,*n);

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_bitshr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_BITSHR) ");
#endif
    if (!(ANY_BIT(VAR_TYPE(*t)) || ANY_BIT(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_ULINT)
    *VAR_PTR(VT_ULINT,0) = *VAR_PTR(VT_ULINT,*t) >> *VAR_PTR(VT_ULINT,*n);

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_bitror(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_BITROR) ");
#endif
    if (!(ANY_BIT(VAR_TYPE(*t)) || ANY_BIT(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_ULINT)
    *VAR_PTR(VT_ULINT,0) = (*VAR_PTR(VT_ULINT,*t) >> *VAR_PTR(VT_ULINT,*n)) | (*VAR_PTR(VT_ULINT,*t) << (64 - *VAR_PTR(VT_ULINT,*n)));

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_bitrol(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_BITROL) ");
#endif
    if (!(ANY_BIT(VAR_TYPE(*t)) || ANY_BIT(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_ULINT)
    *VAR_PTR(VT_ULINT,0) = (*VAR_PTR(VT_ULINT,*t) << *VAR_PTR(VT_ULINT,*n)) | (*VAR_PTR(VT_ULINT,*t) >> (64 - *VAR_PTR(VT_ULINT,*n)));

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_cmpand(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_CMPAND) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_ULINT)
    (*((TYPE_VT_ULINT*) vm->hp[*t].var)) = 0;

    uint16_t cnt;
    for (cnt = 0; cnt < *t; cnt++) {
        uint8_t type = (*((TYPE_VT_ULINT*) vm->hp[cnt].var));
        if (!(ANY_BIT(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        *VAR_PTR(VT_ULINT,0) &= *VAR_PTR(VT_ULINT, PICK(1 - cnt));
    }

    *alu = 0;
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_cmporf(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_CMPORF) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_ULINT)
    *VAR_PTR(VT_ULINT,0) = 0;

    uint16_t cnt;
    for (cnt = 0; cnt < *t; cnt++) {
        uint8_t type = (*((TYPE_VT_ULINT*) vm->hp[cnt].var));
        if (!(ANY_BIT(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        *VAR_PTR(VT_ULINT,0) |= *VAR_PTR(VT_ULINT,PICK(1 - cnt));
    }

    *alu = 0;
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_cmpxor(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_CMPXOR) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_ULINT)
    *VAR_PTR(VT_ULINT,0) = 0;

    uint16_t cnt;
    for (cnt = 0; cnt < *t; cnt++) {
        uint8_t type = (*((TYPE_VT_ULINT*) vm->hp[cnt].var));
        if (!(ANY_BIT(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        *VAR_PTR(VT_ULINT,0) ^= *VAR_PTR(VT_ULINT,PICK(1 - cnt));
    }

    *alu = 0;
    POP(*t)
    return RC_OK;
}

uint8_t fnc_alu_cmpnot(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_CMPNOT) ");
#endif
    if (!(ANY_BIT(VAR_TYPE(*t))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_ULINT)
    *VAR_PTR(VT_ULINT,0) = ~*VAR_PTR(VT_ULINT,*t);

    *alu = 0;
    return RC_OK;
}

#endif /*__PLCVM_BITWISEBOOL_H__*/
