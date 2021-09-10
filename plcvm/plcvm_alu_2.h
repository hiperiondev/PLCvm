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

// TODO: finish implementation
uint8_t fnc_alu_cnvtot(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX1_CNVTOT) ");
#endif
    uint8_t cnt;

    // iec-61131-3 2013-02 ed 3.0 table 12
    static int8_t implicit_conversion[20][2] = {
            { VT_BOOL,  VT_BYTE    },
            { VT_BYTE,  VT_WORD    },
            { VT_WORD,  VT_DWORD   },
            { VT_DWORD, VT_LWORD   },
            { VT_SINT,  VT_INT     },
            { VT_INT,   VT_DINT    },
            { VT_DINT,  VT_LINT    },
            { VT_REAL,  VT_LREAL   },
            { VT_USINT, VT_UINT    },
            { VT_USINT, VT_INT     },
            { VT_UINT,  VT_DINT    },
            { VT_UINT,  VT_REAL    },
            { VT_UINT,  VT_UDINT   },
            { VT_UDINT, VT_ULINT   },
            { VT_TIME,  VT_LTIME   },
            { VT_DT,    VT_LDT     },
            { VT_DATE,  VT_LDATE   },
            { VT_TOD,   VT_LTOD    },
            { VT_CHAR,  VT_STRING  },
            { VT_WCHAR, VT_WSTRING }
    };

    uint8_t src_type = VAR_TYPE(*t);
    for (cnt = 0; cnt > 20; cnt++) {
        if ((implicit_conversion[cnt][0] == src_type) && (implicit_conversion[cnt][1] == *n)) { //implicit conversion allowed
            FREE_ACC

            switch (*n) {
                case VT_INT: {
                    CC_VAR(0, 1, VT_INT);
                    *((VTYPE(VT_INT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_DINT: {
                    CC_VAR(0, 1, VT_DINT);
                    *((VTYPE(VT_DINT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_LINT: {
                    CC_VAR(0, 1, VT_LINT);
                    *((VTYPE(VT_LINT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_BYTE: {
                    CC_VAR(0, 1, VT_BYTE);
                    *((VTYPE(VT_BYTE)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_UINT:
                case VT_WORD: {
                    CC_VAR(0, 1, VT_UINT);
                    *((VTYPE(VT_UINT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_UDINT:
                case VT_DWORD: {
                    CC_VAR(0, 1, VT_UDINT);
                    *((VTYPE(VT_UDINT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_ULINT:
                case VT_LWORD: {
                    CC_VAR(0, 1, VT_ULINT);
                    *((VTYPE(VT_ULINT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_REAL: {
                    CC_VAR(0, 1, VT_REAL);
                    *((VTYPE(VT_REAL)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_LREAL: {
                    CC_VAR(0, 1, VT_LREAL);
                    *((VTYPE(VT_LREAL)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_LDATE: { // TODO: implement
                    break;
                }

                case VT_LTOD: { // TODO: implement
                    break;
                }

                case VT_LDT: { // TODO: implement
                    break;
                }

                case VT_STRING: {
                    CC_VAR(0, 1, VT_STRING);
                    ((VTYPE(VT_STRING)*)vm->hp[0].var)[0] = *(VTYPE(VT_CHAR)*)vm->hp[*t].var;
                    vm->hp[0].len = 1;
                    break;
                }

                case VT_WSTRING: {
                    CC_VAR(0, 1, VT_WSTRING);
                    ((VTYPE(VT_WSTRING)*)vm->hp[0].var)[0] = *(VTYPE(VT_WCHAR)*)vm->hp[*t].var;
                    vm->hp[0].len = 1;
                    break;
                }

                default:
                    goto exit;
            }
            vm->hp[0].type = *n;
            vm->dp--;
            *alu = 0;
            return RC_OK;

        } else if ((implicit_conversion[cnt][0] == *n) && (implicit_conversion[cnt][0] == src_type)) { // conversion allowed with truncated data
            // TODO: implement
            return RC_VAR_TRUNC;
        }
    }

    exit:
    // conversion not allowed
    vm->dp--;
    return RC_VAR_NOT_ALLWD;
}

uint8_t fnc_alu_selmux(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_SELMUX) ");
#endif
    if ((*n > *t) || (*t == 0)) // K > available entries
        return RC_VAR_ERROR;

    *alu = vm->ds[*n + 2];
    vm->dp -= *t;
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
        res = res && (vm->ds[cnt + 1] > vm->ds[cnt + 2]);

    *alu = res;
    vm->dp -= *t;
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
        res = res && (vm->ds[cnt + 1] >= vm->ds[cnt + 2]);

    *alu = res;
    vm->dp -= *t;
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
        res = res && (vm->ds[cnt + 1] == vm->ds[cnt + 2]);

    *alu = res;
    vm->dp -= *t;
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
        res = res && (vm->ds[cnt + 1] <= vm->ds[cnt + 2]);

    *alu = res;
    vm->dp -= *t;
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
        res = res && (vm->ds[cnt + 1] < vm->ds[cnt + 2]);

    *alu = res;
    vm->dp -= *t;
    return RC_OK;
}


uint8_t fnc_alu_cmpneq(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPNEQ) ");
#endif

    *alu = (*t != *n);
    return RC_OK;
}

uint8_t fnc_alu_strlen(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRLEN) ");
#endif
    if (!((vm->hp[*t].type == VT_STRING) || (vm->hp[*t].type == VT_WSTRING)))
        return RC_VAR_NOT_ALLWD;

    *alu = vm->hp[*t].len;
    return RC_OK;
}


uint8_t fnc_alu_strlft(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRLFT) ");
#endif
    uint64_t cnt;
    FREE_ACC

    switch (VAR_TYPE(*t)) {
        case VT_STRING:
            CC_VAR(0, *n, VT_STRING);
            for (cnt = 0; cnt < *n; cnt++)
                ((VTYPE(VT_STRING)*)(vm->hp[0].var))[cnt] = ((VTYPE(VT_STRING)*)(vm->hp[*t].var))[cnt];
            break;
        case VT_WSTRING:
            CC_VAR(0, *n, VT_WSTRING);
            for (cnt = 0; cnt < *n; cnt++)
                ((VTYPE(VT_WSTRING)*)(vm->hp[0].var))[cnt] = ((VTYPE(VT_WSTRING)*)(vm->hp[*t].var))[cnt];
            break;
        default:
            return RC_VAR_NOT_ALLWD;
    }

    vm->hp[0].len = *n;
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_strrgh(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRRGH) ");
#endif
    FREE_ACC

    uint64_t cnt;
    switch (VAR_TYPE(*t)) {
        case VT_STRING:
            CC_VAR(0, *n, VT_STRING);
            for (cnt = *n; cnt >= 0; cnt--)
                ((VTYPE(VT_STRING)*)(vm->hp[0].var))[cnt] = ((VTYPE(VT_STRING)*)(vm->hp[*t].var))[cnt];
            break;
        case VT_WSTRING:
            CC_VAR(0, *n, VT_WSTRING);
            for (cnt = *n; cnt >= 0; cnt--)
                ((VTYPE(VT_WSTRING)*)(vm->hp[0].var))[cnt] = ((VTYPE(VT_WSTRING)*)(vm->hp[*t].var))[cnt];
            break;
        default:
            return RC_VAR_NOT_ALLWD;
    }

    vm->hp[0].len = *n;
    vm->dp--;
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_strmid(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRMID) ");
#endif
    FREE_ACC

    uint64_t cnt;
    switch (VAR_TYPE(*t)) {
        case VT_STRING:
            CC_VAR(0, vm->ds[vm->dp - 2], VT_STRING);
            for (cnt = *n; cnt <= vm->ds[vm->dp - 2]; cnt++)
                ((VTYPE(VT_STRING)*)(vm->hp[0].var))[cnt] = ((VTYPE(VT_STRING)*)(vm->hp[*t].var))[cnt];
            break;
        case VT_WSTRING:
            CC_VAR(0, vm->ds[vm->dp - 2], VT_WSTRING);
            for (cnt = *n; cnt <= vm->ds[vm->dp - 2]; cnt++)
                ((VTYPE(VT_WSTRING)*)(vm->hp[0].var))[cnt] = ((VTYPE(VT_WSTRING)*)(vm->hp[*t].var))[cnt];
            break;
        default:
            return RC_VAR_NOT_ALLWD;
    }

    vm->hp[0].len = vm->ds[vm->dp - 2];
    vm->dp -= 2;
    *alu = 0;

    return RC_OK;
}

uint8_t fnc_alu_strcnc(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRCNC) ");
#endif
    FREE_ACC

    uint64_t cnt, cnt2, pos = 0, len = 0;
    for (cnt = 0; cnt < *t; cnt++) {
        int16_t var = vm->ds[vm->dp - 1 - cnt];
        if (!((vm->hp[var].type == VT_STRING) || (vm->hp[var].type == VT_WSTRING)))
            return RC_VAR_NOT_ALLWD;

        len += vm->hp[var].len;
    }

    switch (VAR_TYPE(*t)) {
        case VT_STRING:
            CC_VAR(0, len, VT_STRING);
            for (cnt = 0; cnt < *t; cnt++) {
                uint16_t var = vm->ds[vm->dp - 1 - cnt];
                for (cnt2 = pos; cnt2 < vm->hp[var].len; cnt2++) {
                    ((VTYPE(VT_STRING)*)(vm->hp[0].var))[cnt2] = ((VTYPE(VT_STRING)*)(vm->hp[var].var))[cnt2];
                    pos++;
                }
            }
            break;
        case VT_WSTRING:
            CC_VAR(0, len, VT_WSTRING);
            for (cnt = 0; cnt < *t; cnt++) {
                uint16_t var = vm->ds[vm->dp - 1 - cnt];
                for (cnt2 = pos; cnt2 < vm->hp[var].len; cnt2++) {
                    ((VTYPE(VT_WSTRING)*)(vm->hp[0].var))[cnt2] = ((VTYPE(VT_WSTRING)*)(vm->hp[var].var))[cnt2];
                    pos++;
                }
            }
            break;
        default:
        return RC_VAR_NOT_ALLWD;
    }

    vm->hp[0].len = len;
    vm->dp -= *t;
    *alu = 0;
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_strins(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRINS) ");
#endif

    if (!((ANY_STRING(vm->hp[*t].type) || ANY_STRING(vm->hp[*n].type)) && vm->hp[*t].type == vm->hp[*n].type))
            return RC_VAR_NOT_ALLWD;

    FREE_ACC
    uint64_t len = vm->hp[*t].len + vm->hp[*n].len;

    switch (VAR_TYPE(*t)) {
        case VT_STRING:
            CC_VAR(0, len, VT_STRING);

            break;
        case VT_WSTRING:
            CC_VAR(0, len, VT_WSTRING);

            break;
    }

    vm->hp[0].len = len;
    *alu = 0;
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_strdel(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRDEL) ");
#endif
    if (!((vm->hp[*t].type == VT_STRING) || (vm->hp[*t].type == VT_WSTRING)))
        return RC_VAR_NOT_ALLWD;
    FREE_ACC

    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_chrrpl(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CHRRPL) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_chrfnd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CHRFND) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timadd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMADD) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timsum(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMSUM) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timmul(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMMUL) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timdiv(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMDIV) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timcnc(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMCNC) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_enmsel(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMSEL) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_enmmux(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMMUX) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_enmequ(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMEQU) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_enmneq(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMNEQ) ");
#endif
    return RC_OK;
}

#endif /* PLCVM_ALU_2_H_ */
