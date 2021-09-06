/*
 * PLCvm_alu_2.h
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

#ifndef PLCVM_ALU_2_H_
#define PLCVM_ALU_2_H_

uint8_t fnc_sev(vm_t *vm, uint16_t var) { // TODO: implement
#ifdef DEBUG
    DBG_PRINT("VT_SEV) ");
#endif
    return RC_OK;
}

uint8_t fnc_var_retain(vm_t *vm, uint16_t var) { // TODO: implement
#ifdef DEBUG
    DBG_PRINT("VAR RETAIN) ");
#endif
    return RC_OK;
}

uint8_t fnc_var_persist(vm_t *vm, uint16_t var) { // TODO: implement
#ifdef DEBUG
    DBG_PRINT("VAR PERSIST) ");
#endif
    return RC_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t fnc_alu_varcvr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_VARCVR) ");
#endif
    uint16_t tmp, varp = 0xffff;

    for (tmp = 1; tmp <= 2047; tmp++) {
        if (vm->hp[tmp].type == 0) {
            varp = tmp;
            break;
        }
    }
    if (varp == 0xffff) // no more room
        return RC_NO_VAR_SPC;

    tmp = 1;
    switch (*t & 0x1f) {
        case VT_EMPTY: {
            free(vm->hp[varp].var);
            vm->hp[varp].type = 0;
            tmp = 0;
            break;
        }

        case VT_BOOL: {
            vm->hp[varp].var = (bool*) calloc(1, sizeof(bool));
            break;
        }

        case VT_SINT: {
            vm->hp[varp].var = (int8_t*) calloc(1, sizeof(int8_t));
            break;
        }

        case VT_INT: {
            vm->hp[varp].var = (int16_t*) calloc(1, sizeof(int16_t));
            break;
        }

        case VT_DINT: {
            vm->hp[varp].var = (int32_t*) calloc(1, sizeof(int32_t));
            break;
        }

        case VT_LINT: {
            vm->hp[varp].var = (int64_t*) calloc(1, sizeof(int64_t));
            break;
        }

        case VT_USINT:
        case VT_BYTE: {
            vm->hp[varp].var = (uint8_t*) calloc(1, sizeof(uint8_t));
            break;
        }

        case VT_UINT:
        case VT_WORD: {
            vm->hp[varp].var = (uint16_t*) calloc(1, sizeof(uint16_t));
            break;
        }

        case VT_UDINT:
        case VT_DWORD: {
            vm->hp[varp].var = (uint32_t*) calloc(1, sizeof(uint32_t));
            break;
        }

        case VT_ULINT:
        case VT_LWORD: {
            vm->hp[varp].var = (uint64_t*) calloc(1, sizeof(uint64_t));
            break;
        }

        case VT_REAL: {
            vm->hp[varp].var = (float*) calloc(1, sizeof(float));
            break;
        }

        case VT_LREAL: {
            vm->hp[varp].var = (double*) calloc(1, sizeof(double));
            break;
        }

        case VT_TIME: {
            vm->hp[varp].var = (time_t*) calloc(1, sizeof(time_t));
            break;
        }

        case VT_DATE: {
            vm->hp[varp].var = (date_t*) malloc(sizeof(date_t));
            ((date_t*) vm->hp[varp].var)->date.day = 1;
            ((date_t*) vm->hp[varp].var)->date.month = 1;
            ((date_t*) vm->hp[varp].var)->date.year = 1;
            break;
        }

        case VT_TOD: {
            vm->hp[varp].var = (tod_t*) calloc(1, sizeof(tod_t));
            break;
        }

        case VT_DT: {
            vm->hp[varp].var = (dat_t*) calloc(1, sizeof(dat_t));
            ((dat_t*) vm->hp[varp].var)->date.date.day = 1;
            ((dat_t*) vm->hp[varp].var)->date.date.month = 1;
            ((dat_t*) vm->hp[varp].var)->date.date.year = 1;
            break;
        }

        case VT_STRING: {
            vm->hp[varp].var = (char*) calloc(1, (sizeof(char) * (*n)) + 1);
            vm->dp--;
            break;
        }

        case VT_WSTRING: {
            vm->hp[varp].var = (char*) calloc(1, (sizeof(char) * (*n) * 2) + 1);
            vm->dp--;
            break;
        }
        case VT_SE: {
            vm->hp[varp].var = (uint16_t*) malloc(sizeof(uint16_t));
            *((uint16_t*)vm->hp[varp].var) = *n;
            vm->dp--;
            fnc_sev(vm, varp);
            break;
        }

        default:
            return RC_VTYPE_UNKNOWN;
    }

    if (tmp)
        vm->hp[varp].type = (uint8_t) *t;

    if (*t & 0x20)
        fnc_var_retain(vm, varp);
    else if (*t & 40)
        fnc_var_persist(vm, varp);

    *alu = varp;

    return RC_OK;
}

uint8_t fnc_alu_varsvr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_VARSVR) ");
#endif
    return RC_OK;
}

uint8_t fnc_alu_vargvr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_VARGVR) ");
#endif
    if (vm->hp[*t].type == 0)
        return RC_NO_VAR;

    uint16_t tmp = 0;
    tmp = (vm->hp[*t].type << 10);
    tmp |= *t;

    return RC_OK;
}

// 4
uint8_t fnc_alu_selmux(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_SELMUX) ");
#endif
    return RC_OK;
}

// 5
uint8_t fnc_alu_cmpgrt(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPGRT) ");
#endif
    return RC_OK;
}

// 6
uint8_t fnc_alu_cmpgeq(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPGEQ) ");
#endif
    return RC_OK;
}

// 7
uint8_t fnc_alu_cmpequ(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPEQU) ");
#endif
    return RC_OK;
}

// 8
uint8_t fnc_alu_cmples(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPLES) ");
#endif
    return RC_OK;
}

// 9
uint8_t fnc_alu_cmplth(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPLTH) ");
#endif
    return RC_OK;
}

// 10
uint8_t fnc_alu_cmpneq(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPNEQ) ");
#endif
    return RC_OK;
}

// 11
uint8_t fnc_alu_strlen(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRLEN) ");
#endif
    return RC_OK;
}

// 12
uint8_t fnc_alu_strlft(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRLFT) ");
#endif
    return RC_OK;
}

// 13
uint8_t fnc_alu_strrgh(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRRGH) ");
#endif
    return RC_OK;
}

// 14
uint8_t fnc_alu_strmid(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRMID) ");
#endif
    return RC_OK;
}

// 15
uint8_t fnc_alu_strcnc(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRCNC) ");
#endif
    return RC_OK;
}

// 16
uint8_t fnc_alu_strins(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRINS) ");
#endif
    return RC_OK;
}

// 17
uint8_t fnc_alu_strdel(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRDEL) ");
#endif
    return RC_OK;
}

// 18
uint8_t fnc_alu_chrrpl(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CHRRPL) ");
#endif
    return RC_OK;
}

// 19
uint8_t fnc_alu_chrfnd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CHRFND) ");
#endif
    return RC_OK;
}

// 20
uint8_t fnc_alu_timadd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMADD) ");
#endif
    return RC_OK;
}

// 21
uint8_t fnc_alu_timsum(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMSUM) ");
#endif
    return RC_OK;
}

// 22
uint8_t fnc_alu_timmul(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMMUL) ");
#endif
    return RC_OK;
}

// 23
uint8_t fnc_alu_timdiv(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMDIV) ");
#endif
    return RC_OK;
}

// 24
uint8_t fnc_alu_timcnc(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMCNC) ");
#endif
    return RC_OK;
}

// 25
uint8_t fnc_alu_enmsel(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMSEL) ");
#endif
    return RC_OK;
}

// 26
uint8_t fnc_alu_enmmux(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMMUX) ");
#endif
    return RC_OK;
}

// 27
uint8_t fnc_alu_enmequ(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMEQU) ");
#endif
    return RC_OK;
}

// 28
uint8_t fnc_alu_enmneq(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMNEQ) ");
#endif
    return RC_OK;
}

// 29
uint8_t fnc_alu_ex2_nop(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_NOP) ");
#endif
    return RC_OK;
}

#endif /* PLCVM_ALU_2_H_ */