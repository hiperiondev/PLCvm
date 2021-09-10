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

#include <math.h>

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

    if (vm->hp[varp].var != NULL)
        free(vm->hp[varp].var);

    switch (*t & 0x1f) {
        case VT_EMPTY: {
            free(vm->hp[varp].var);
            vm->hp[varp].type = 0;
            tmp = 0;
            break;
        }

        case VT_BOOL: {
            CC_VAR(varp, 1, VT_BOOL);
            break;
        }

        case VT_SINT: {
            CC_VAR(varp, 1, VT_SINT);
            break;
        }

        case VT_INT: {
            CC_VAR(varp, 1, VT_INT);
            break;
        }

        case VT_DINT: {
            CC_VAR(varp, 1, VT_DINT);
            break;
        }

        case VT_LINT: {
            CC_VAR(varp, 1, VT_LINT);
            break;
        }

        case VT_USINT:
        case VT_BYTE: {
            CC_VAR(varp, 1, VT_USINT);
            break;
        }

        case VT_UINT:
        case VT_WORD: {
            CC_VAR(varp, 1, VT_UINT);
            break;
        }

        case VT_UDINT:
        case VT_DWORD: {
            CC_VAR(varp, 1, VT_DINT);
            break;
        }

        case VT_ULINT:
        case VT_LWORD: {
            CC_VAR(varp, 1, VT_ULINT);
            break;
        }

        case VT_REAL: {
            CC_VAR(varp, 1, VT_REAL);
            break;
        }

        case VT_LREAL: {
            CC_VAR(varp, 1, VT_LREAL);
            break;
        }

        case VT_TIME: {
           CC_VAR(varp, 1, VT_TIME);
            break;
        }

        case VT_DATE: {
            CC_VAR(varp, 1, VT_DATE);
            ((date_t*) vm->hp[varp].var)->date.day = 1;
            ((date_t*) vm->hp[varp].var)->date.month = 1;
            ((date_t*) vm->hp[varp].var)->date.year = 1;
            break;
        }

        case VT_LDATE: {
            CC_VAR(varp, 1, VT_LDATE);
            break;
        }

        case VT_TOD: {
            CC_VAR(varp, 1, VT_TOD);
            break;
        }

        case VT_LTOD: { // TODO: implement
            break;
        }

        case VT_DT: {
            CC_VAR(varp, 1, VT_DT);
            ((dat_t*) vm->hp[varp].var)->dat.date.date.day = 1;
            ((dat_t*) vm->hp[varp].var)->dat.date.date.month = 1;
            ((dat_t*) vm->hp[varp].var)->dat.date.date.year = 1;
            break;
        }

        case VT_LDT: {
            CC_VAR(varp, 1, VT_LDT);
            break;
        }

        case VT_STRING: {
            CC_VAR(varp, *n, VT_STRING);
            vm->dp--;
            break;
        }

        case VT_WSTRING: {
            CC_VAR(varp, *n, VT_WSTRING);
            vm->dp--;
            break;
        }

        case VT_CHAR: {
            CC_VAR(varp, 1, VT_CHAR);
            break;
        }

        case VT_SE: {
            CC_VAR(varp, 1, VT_SE);
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
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_varsvr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_VARSVR) ");
#endif
    uint8_t pop = 0;

    if (vm->hp[*t].type == 0)
        return RC_NO_VAR;

    switch (VAR_TYPE(*t)) {
        // max 16 bits
        case VT_BOOL:
        case VT_SINT:
        case VT_INT:
        case VT_USINT:
        case VT_UINT:
        case VT_BYTE:
        case VT_WORD:
        case VT_CHAR: {
            *((uint16_t*) vm->hp[*t].var) = *n;
            pop = 1;
            break;
        }

        // 32 bits
        case VT_TOD:
        case VT_TIME:
        case VT_DATE:
        case VT_REAL:
        case VT_UDINT:
        case VT_DINT:
        case VT_DWORD: {
            *((uint32_t*) vm->hp[*t].var) = ((uint32_t)vm->ds[vm->dp - 1] << 16) | ((uint32_t)vm->ds[vm->dp - 2]);
            pop = 2;
            break;
        }

        // 64 bits
        case VT_DT:
        case VT_LDT:
        case VT_LTOD:
        case VT_LDATE:
        case VT_LINT:
        case VT_LREAL:
        case VT_ULINT:
        case VT_LWORD: {
            *((uint64_t*) vm->hp[*t].var) = (((uint64_t)vm->ds[vm->dp - 1]) << 48) | ((uint64_t)vm->ds[vm->dp - 2] << 32) | ((uint64_t)vm->ds[vm->dp - 3] << 16) | ((uint64_t)vm->ds[vm->dp - 4]);
            pop = 4;
            break;
        }

        case VT_STRING: {
            if (*n > vm->hp[*t].len)
                return RC_VAR_OOR;

            uint64_t cnt;
            for (cnt = 0; cnt < *n; cnt++) {
                ((char*) vm->hp[*t].var)[cnt] = vm->ds[vm->dp - 2 - cnt];
            }
            vm->hp[*t].len = *n;
            pop = *n + 1;
            break;
        }

        case VT_WSTRING: {
            if ((*n * 2) > vm->hp[*t].len)
                return RC_VAR_OOR;

            uint64_t cnt;
            for (cnt = 0; cnt < (*n * 2); cnt += 2) {
                ((char*) vm->hp[*t].var)[cnt] = vm->ds[vm->dp - 2 - cnt];
                ((char*) vm->hp[*t].var)[cnt + 1] = vm->ds[vm->dp - 2 - cnt + 1];
            }
            vm->hp[*t].len = *n;
            pop = (*n * 2) + 1;
            break;
            break;
        }

        case VT_SE: {
            break;
        }
    }

    POP(pop)
    return RC_OK;
}

uint8_t fnc_alu_numabs(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMABS) ");
#endif
    if (!(ANY_NUM(VAR_TYPE(*t))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *((TYPE_VT_LREAL*) vm->hp[0].var) = abs(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numsqr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMSQR) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *((TYPE_VT_LREAL*) vm->hp[0].var) = sqrt(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numlon(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMLON) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *((TYPE_VT_LREAL*) vm->hp[0].var) = log(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numlog(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMLOG) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *((TYPE_VT_LREAL*) vm->hp[0].var) = log10(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numexp(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMEXP) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;
    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numsin(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMSIN) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *((TYPE_VT_LREAL*) vm->hp[0].var) = sin(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numcos(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMCOS) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *((TYPE_VT_LREAL*) vm->hp[0].var) = cos(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numtan(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMTAN) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;
    if (*((TYPE_VT_LREAL*) vm->hp[*t].var))
        return RC_EXPTN;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *((TYPE_VT_LREAL*) vm->hp[0].var) = tan(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numasn(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMASN) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *((TYPE_VT_LREAL*) vm->hp[0].var) = asin(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numacs(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMACS) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *((TYPE_VT_LREAL*) vm->hp[0].var) = acos(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_numatn(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_NUMATN) ");
#endif
    if (!ANY_REAL(VAR_TYPE(*t)))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    *((TYPE_VT_LREAL*) vm->hp[0].var) = atan(*((TYPE_VT_LREAL*) vm->hp[*t].var));
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_athadd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHADD) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    (*((TYPE_VT_LREAL*) vm->hp[*t].var)) = 0;

    uint16_t cnt;
    for (cnt = 0; cnt < *n; cnt++) {
        uint8_t type = (*((TYPE_VT_LREAL*) vm->hp[*t].var));
        if (!(ANY_NUM(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        (*((TYPE_VT_LREAL*) vm->hp[*t].var)) += (*((TYPE_VT_LREAL*) vm->hp[vm->ds[vm->dp - 1 - cnt]].var));
    }

    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_athmul(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHMUL) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    (*((TYPE_VT_LREAL*) vm->hp[*t].var)) = 0;

    uint16_t cnt;
    for (cnt = 0; cnt < *n; cnt++) {
        uint8_t type = (*((TYPE_VT_LREAL*) vm->hp[*t].var));
        if (!(ANY_NUM(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        (*((TYPE_VT_LREAL*) vm->hp[*t].var)) *= (*((TYPE_VT_LREAL*) vm->hp[vm->ds[vm->dp - 1 - cnt]].var));
    }

    *alu = 0;
    POP(*n)
    return RC_OK;
}

uint8_t fnc_alu_athsub(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHSUB) ");
#endif
    if (!(ANY_NUM(VAR_TYPE(*t)) || ANY_NUM(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    (*((TYPE_VT_LREAL*) vm->hp[0].var)) = (*((TYPE_VT_LREAL*) vm->hp[*t].var)) - (*((TYPE_VT_LREAL*) vm->hp[*n].var));

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_athdiv(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHDIV) ");
#endif
    if (!(ANY_NUM(VAR_TYPE(*t)) || ANY_NUM(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;
    if (*((TYPE_VT_LREAL*) vm->hp[*n].var) == 0)
        return RC_EXPTN;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    (*((TYPE_VT_LREAL*) vm->hp[0].var)) = (*((TYPE_VT_LREAL*) vm->hp[*t].var)) / (*((TYPE_VT_LREAL*) vm->hp[*n].var));

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_athmod(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHMOD) ");
#endif
    if (!(ANY_NUM(VAR_TYPE(*t)) || ANY_NUM(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;
    if (*((TYPE_VT_LREAL*) vm->hp[*n].var) == 0)
        return RC_EXPTN;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    (*((TYPE_VT_LREAL*) vm->hp[0].var)) = (*((TYPE_VT_LREAL*) vm->hp[*t].var)) * (*((TYPE_VT_LREAL*) vm->hp[*n].var));

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_athexp(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHEXP) ");
#endif
    if (!(ANY_NUM(VAR_TYPE(*t)) || ANY_NUM(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_LREAL);
    (*((TYPE_VT_LREAL*) vm->hp[0].var)) = pow((*((TYPE_VT_LREAL*) vm->hp[*t].var)), (*((TYPE_VT_LREAL*) vm->hp[*n].var)));

    *alu = 0;
    POP(1)
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_athmov(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_ATHMOV) ");
#endif
    return RC_OK;
}

uint8_t fnc_alu_bitshl(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_BITSHL) ");
#endif
    if (!(ANY_BIT(VAR_TYPE(*t)) || ANY_BIT(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_ULINT);
    (*((TYPE_VT_ULINT*) vm->hp[0].var)) = (*((TYPE_VT_ULINT*) vm->hp[*t].var)) << (*((TYPE_VT_ULINT*) vm->hp[*n].var));

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_bitshr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_BITSHR) ");
#endif
    if (!(ANY_BIT(VAR_TYPE(*t)) || ANY_BIT(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_ULINT);
    (*((TYPE_VT_ULINT*) vm->hp[0].var)) = (*((TYPE_VT_ULINT*) vm->hp[*t].var)) >> (*((TYPE_VT_ULINT*) vm->hp[*n].var));

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_bitror(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_BITROR) ");
#endif
    if (!(ANY_BIT(VAR_TYPE(*t)) || ANY_BIT(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_ULINT);
    (*((TYPE_VT_ULINT*) vm->hp[0].var)) = ((*((TYPE_VT_ULINT*) vm->hp[*t].var)) >> (*((TYPE_VT_ULINT*) vm->hp[*n].var)))
                                          | (*((TYPE_VT_ULINT*) vm->hp[*t].var)) << (64 - *((TYPE_VT_ULINT*) vm->hp[*n].var));
    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_bitrol(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_BITROL) ");
#endif
    if (!(ANY_BIT(VAR_TYPE(*t)) || ANY_BIT(VAR_TYPE(*n))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_ULINT);
    (*((TYPE_VT_ULINT*) vm->hp[0].var)) = ((*((TYPE_VT_ULINT*) vm->hp[*t].var)) >> (*((TYPE_VT_ULINT*) vm->hp[*n].var)))
                                        | (*((TYPE_VT_ULINT*) vm->hp[*t].var)) >> (64 - *((TYPE_VT_ULINT*) vm->hp[*n].var));

    *alu = 0;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_cmpand(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CMPAND) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_ULINT);
    (*((TYPE_VT_ULINT*) vm->hp[*t].var)) = 0;

    uint16_t cnt;
    for (cnt = 0; cnt < *n; cnt++) {
        uint8_t type = (*((TYPE_VT_ULINT*) vm->hp[*t].var));
        if (!(ANY_BIT(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        (*((TYPE_VT_ULINT*) vm->hp[*t].var)) &= (*((TYPE_VT_ULINT*) vm->hp[vm->ds[vm->dp - 1 - cnt]].var));
    }

    *alu = 0;
    POP(*n)
    return RC_OK;
}

uint8_t fnc_alu_cmporf(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CMPORF) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_ULINT);
    (*((TYPE_VT_ULINT*) vm->hp[*t].var)) = 0;

    uint16_t cnt;
    for (cnt = 0; cnt < *n; cnt++) {
        uint8_t type = (*((TYPE_VT_ULINT*) vm->hp[*t].var));
        if (!(ANY_BIT(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        (*((TYPE_VT_ULINT*) vm->hp[*t].var)) |= (*((TYPE_VT_ULINT*) vm->hp[vm->ds[vm->dp - 1 - cnt]].var));
    }

    *alu = 0;
    POP(*n)
    return RC_OK;
}

uint8_t fnc_alu_cmpxor(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CMPXOR) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_ULINT);
    (*((TYPE_VT_ULINT*) vm->hp[*t].var)) = 0;

    uint16_t cnt;
    for (cnt = 0; cnt < *n; cnt++) {
        uint8_t type = (*((TYPE_VT_ULINT*) vm->hp[*t].var));
        if (!(ANY_BIT(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        (*((TYPE_VT_ULINT*) vm->hp[*t].var)) ^= (*((TYPE_VT_ULINT*) vm->hp[vm->ds[vm->dp - 1 - cnt]].var));
    }

    *alu = 0;
    POP(*n)
    return RC_OK;
}

uint8_t fnc_alu_cmpnot(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CMPNOT) ");
#endif
    if (!(ANY_BIT(VAR_TYPE(*t))))
        return RC_VAR_NOT_ALLWD;

    FREE_ACC
    CC_VAR(0, 1, VT_ULINT);
    (*((TYPE_VT_ULINT*) vm->hp[0].var)) = ~(*((TYPE_VT_ULINT*) vm->hp[*t].var)) ;

    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_selmax(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_SELMAX) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_ULINT);
    (*((TYPE_VT_ULINT*) vm->hp[*t].var)) = 0;

    uint16_t cnt;
    TYPE_VT_ULINT max = 0;
    for (cnt = 0; cnt < *n; cnt++) {
        uint8_t type = (*((TYPE_VT_ULINT*) vm->hp[*t].var));
        if (!(ANY_BIT(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        if ((*((TYPE_VT_ULINT*) vm->hp[vm->ds[vm->dp - 1 - cnt]].var)) > max)
            max = (*((TYPE_VT_ULINT*) vm->hp[vm->ds[vm->dp - 1 - cnt]].var));
    }
    (*((TYPE_VT_ULINT*) vm->hp[*t].var)) = max;

    *alu = 0;
    POP(*n)
    return RC_OK;
}

uint8_t fnc_alu_selmin(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_SELMIN) ");
#endif
    FREE_ACC
    CC_VAR(0, 1, VT_ULINT);
    (*((TYPE_VT_ULINT*) vm->hp[*t].var)) = 0;

    uint16_t cnt;
    TYPE_VT_ULINT min = *((TYPE_VT_ULINT*) vm->hp[vm->ds[vm->dp - 1]].var);
    for (cnt = 0; cnt < *n; cnt++) {
        uint8_t type = (*((TYPE_VT_ULINT*) vm->hp[*t].var));
        if (!(ANY_BIT(VAR_TYPE(type))))
            return RC_VAR_NOT_ALLWD;

        if ((*((TYPE_VT_ULINT*) vm->hp[vm->ds[vm->dp - 1 - cnt]].var)) < min)
            min = (*((TYPE_VT_ULINT*) vm->hp[vm->ds[vm->dp - 1 - cnt]].var));
    }
    (*((TYPE_VT_ULINT*) vm->hp[*t].var)) = min;

    *alu = 0;
    POP(*n)
    return RC_OK;
}

#endif /* PLCVM_ALU_1_H_ */
