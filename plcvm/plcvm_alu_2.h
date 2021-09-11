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
                    CC_VAR(0, 1, VT_INT)
                    *VAR_PTR(VT_INT, 0) = *t;
                    break;
                }

                case VT_DINT: {
                    CC_VAR(0, 1, VT_DINT)
                    *VAR_PTR(VT_DINT, 0) = *t;
                    break;
                }

                case VT_LINT: {
                    CC_VAR(0, 1, VT_LINT)
                    *VAR_PTR(VT_LINT, 0) = *t;
                    break;
                }

                case VT_BYTE: {
                    CC_VAR(0, 1, VT_BYTE)
                    *VAR_PTR(VT_BYTE, 0) = *t;
                    break;
                }

                case VT_UINT:
                case VT_WORD: {
                    CC_VAR(0, 1, VT_UINT)
                    *VAR_PTR(VT_UINT, 0) = *t;
                    break;
                }

                case VT_UDINT:
                case VT_DWORD: {
                    CC_VAR(0, 1, VT_UDINT)
                    *VAR_PTR(VT_UDINT, 0) = *t;
                    break;
                }

                case VT_ULINT:
                case VT_LWORD: {
                    CC_VAR(0, 1, VT_ULINT)
                    *VAR_PTR(VT_ULINT, 0) = *t;
                    break;
                }

                case VT_REAL: {
                    CC_VAR(0, 1, VT_REAL)
                    *VAR_PTR(VT_REAL, 0) = *t;
                    break;
                }

                case VT_LREAL: {
                    CC_VAR(0, 1, VT_LREAL)
                    *VAR_PTR(VT_LREAL,0) = *t;
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
                    CC_VAR(0, 1, VT_STRING)
                    VAR_PTR(VT_STRING,0)[0] = *VAR_PTR(VT_CHAR,*t);
                    vm->hp[0].len = 1;
                    break;
                }

                case VT_WSTRING: {
                    CC_VAR(0, 1, VT_WSTRING)
                    VAR_PTR(VT_WSTRING,0)[0] = *VAR_PTR(VT_WCHAR,*t);
                    vm->hp[0].len = 1;
                    break;
                }

                default:
                    goto exit;
            }

            vm->hp[0].type = *n;
            POP(1);
            *alu = 0;
            return RC_OK;

        } else if ((implicit_conversion[cnt][0] == *n) && (implicit_conversion[cnt][0] == src_type)) { // conversion allowed with truncated data
            // TODO: implement
            return RC_VAR_TRUNC;
        }
    }

    POP(1)
    exit:
    // conversion not allowed
    return RC_VAR_NOT_ALLWD;
}

uint8_t fnc_alu_selmux(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_SELMUX) ");
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
            CC_VAR(0, *n, VT_STRING)
            for (cnt = 0; cnt < *n; cnt++)
                VAR_PTR(VT_STRING,0)[cnt] = VAR_PTR(VT_STRING,*t)[cnt];
            break;
        case VT_WSTRING:
            CC_VAR(0, *n, VT_WSTRING)
            for (cnt = 0; cnt < *n; cnt++)
                VAR_PTR(VT_WSTRING,0)[cnt] = VAR_PTR(VT_WSTRING,*t)[cnt];
            break;
        default:
            return RC_VAR_NOT_ALLWD;
    }

    vm->hp[0].len = *n;
    *alu = 0;
    POP(1)
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
            CC_VAR(0, *n, VT_STRING)
            for (cnt = *n; cnt >= 0; cnt--)
                VAR_PTR(VT_STRING,0)[cnt] = VAR_PTR(VT_STRING,*t)[cnt];
            break;
        case VT_WSTRING:
            CC_VAR(0, *n, VT_WSTRING)
            for (cnt = *n; cnt >= 0; cnt--)
                VAR_PTR(VT_WSTRING,0)[cnt] = VAR_PTR(VT_WSTRING,*t)[cnt];
            break;
        default:
            return RC_VAR_NOT_ALLWD;
    }

    vm->hp[0].len = *n;
    *alu = 0;
    POP(1)
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
            CC_VAR(0, PICK(2), VT_STRING)
            for (cnt = *n; cnt <= PICK(2); cnt++)
                VAR_PTR(VT_STRING,0)[cnt] = VAR_PTR(VT_STRING,*t)[cnt];
            break;
        case VT_WSTRING:
            CC_VAR(0, PICK(2), VT_WSTRING)
            for (cnt = *n; cnt <= PICK(2); cnt++)
                VAR_PTR(VT_WSTRING,0)[cnt] = VAR_PTR(VT_WSTRING,*t)[cnt];
            break;
        default:
            return RC_VAR_NOT_ALLWD;
    }

    vm->hp[0].len = vm->ds[vm->dp - 2];
    POP(2)
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
        int16_t var = PICK(1 - cnt);
        if (!((vm->hp[var].type == VT_STRING) || (vm->hp[var].type == VT_WSTRING)))
            return RC_VAR_NOT_ALLWD;

        len += vm->hp[var].len;
    }

    switch (VAR_TYPE(*t)) {
        case VT_STRING:
            CC_VAR(0, len, VT_STRING)
            for (cnt = 0; cnt < *t; cnt++) {
                uint16_t var = PICK(1 - cnt);
                for (cnt2 = pos; cnt2 < vm->hp[var].len; cnt2++) {
                    VAR_PTR(VT_STRING,0)[cnt2] = VAR_PTR(VT_STRING,var)[cnt2];
                    pos++;
                }
            }
            break;
        case VT_WSTRING:
            CC_VAR(0, len, VT_WSTRING)
            for (cnt = 0; cnt < *t; cnt++) {
                uint16_t var = PICK(1 - cnt);
                for (cnt2 = pos; cnt2 < vm->hp[var].len; cnt2++) {
                    VAR_PTR(VT_WSTRING,0)[cnt2] = VAR_PTR(VT_WSTRING,var)[cnt2];
                    pos++;
                }
            }
            break;
        default:
        return RC_VAR_NOT_ALLWD;
    }

    vm->hp[0].len = len;
    POP(*t);
    *alu = 0;
    return RC_OK;
}

uint8_t fnc_alu_strins(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRINS) ");
#endif

    if (!((ANY_STRING(vm->hp[*t].type) || ANY_STRING(vm->hp[*n].type)) && vm->hp[*t].type == vm->hp[*n].type))
            return RC_VAR_NOT_ALLWD;

    FREE_ACC
    uint64_t len = vm->hp[*t].len + vm->hp[*n].len;
    uint64_t cnt, pos = 0;
    switch (VAR_TYPE(*t)) {
        case VT_STRING:
            CC_VAR(0, len, VT_STRING)
            for (cnt = 0; cnt < PICK(2); cnt++)
                VAR_PTR(VT_STRING,0)[pos++] = VAR_PTR(VT_STRING,*t)[cnt];
            for (cnt = 0; cnt < vm->hp[*n].len;cnt++)
                VAR_PTR(VT_STRING,0)[pos++] = VAR_PTR(VT_STRING,*n)[cnt];
            for (cnt = PICK(2) + 1; cnt < vm->hp[*t].len - PICK(2);cnt++)
                VAR_PTR(VT_STRING,0)[pos++] = VAR_PTR(VT_STRING,*t)[cnt];
            break;
        case VT_WSTRING:
            CC_VAR(0, len, VT_WSTRING)
            for (cnt = 0; cnt < PICK(2); cnt++)
                VAR_PTR(VT_WSTRING,0)[pos++] = VAR_PTR(VT_WSTRING,*t)[cnt];
            for (cnt = 0; cnt < vm->hp[*n].len;cnt++)
                VAR_PTR(VT_WSTRING,0)[pos++] = VAR_PTR(VT_WSTRING,*n)[cnt];
            for (cnt = PICK(2) + 1; cnt < vm->hp[*t].len - PICK(2);cnt++)
                VAR_PTR(VT_WSTRING,0)[pos++] = VAR_PTR(VT_WSTRING,*t)[cnt];
            break;
    }

    vm->hp[0].len = len;
    *alu = 0;
    POP(2)
    return RC_OK;
}

uint8_t fnc_alu_strdel(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRDEL) ");
#endif
    if (!((vm->hp[*t].type == VT_STRING) || (vm->hp[*t].type == VT_WSTRING)))
        return RC_VAR_NOT_ALLWD;
    FREE_ACC
    TYPE_VT_LWORD len = vm->hp[*t].len - *n;
    TYPE_VT_LWORD cnt, lpos = 0;
    TYPE_VT_LWORD pos = *VAR_PTR(VT_LWORD,PICK(2));
    TYPE_VT_LWORD qty = *n;

    switch (VAR_TYPE(*t)) {
        case VT_STRING:
            CC_VAR(0, len, VT_STRING)
            for (cnt = 0; cnt < vm->hp[*t].len; cnt ++){
                if (cnt >= pos && cnt <= pos + qty)
                    continue;
                VAR_PTR(VT_STRING,0)[lpos++] = VAR_PTR(VT_STRING,*t)[cnt];
            }
            break;
        case VT_WSTRING:
            CC_VAR(0, len, VT_WSTRING)
            for (cnt = 0; cnt < vm->hp[*t].len; cnt++) {
                if (cnt >= pos && cnt <= pos + qty)
                    continue;
                VAR_PTR(VT_WSTRING, 0)[lpos++] = VAR_PTR(VT_WSTRING, *t)[cnt];
            }
            break;
    }

    vm->hp[0].len = len;
    *alu = 0;
    POP(2)
    return RC_OK;
}

uint8_t fnc_alu_strrpl(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CHRRPL) ");
#endif
    FREE_ACC
    TYPE_VT_LWORD len = vm->hp[*t].len;
    TYPE_VT_LWORD cnt, npos = 0;
    TYPE_VT_LWORD pos = *VAR_PTR(VT_LWORD, PICK(3));
    TYPE_VT_LWORD qty = *VAR_PTR(VT_LWORD, PICK(2));

    if(vm->hp[*n].len > qty)
        return RC_VAR_OOR;

    switch (VAR_TYPE(*t)) {
        case VT_STRING:
            CC_VAR(0, len, VT_STRING)
            for (cnt = 0; cnt < len; cnt++) {
                if (cnt >= pos && cnt <= pos + qty)
                    VAR_PTR(VT_STRING, 0)[cnt] = VAR_PTR(VT_STRING, *n)[npos++];
                else
                    VAR_PTR(VT_STRING, 0)[cnt] = VAR_PTR(VT_STRING, *t)[cnt];
            }
            break;
        case VT_WSTRING:
            CC_VAR(0, len, VT_WSTRING)
            for (cnt = 0; cnt < len; cnt++) {
                if (cnt >= pos && cnt <= pos + qty)
                    VAR_PTR(VT_WSTRING, 0)[cnt] = VAR_PTR(VT_WSTRING, *n)[npos++];
                else
                    VAR_PTR(VT_WSTRING, 0)[cnt] = VAR_PTR(VT_WSTRING, *t)[cnt];
            }
            break;
    }

    vm->hp[0].len = len;
    *alu = 0;
    POP(3)
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_strfnd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CHRFND) ");
#endif



    //vm->hp[0].len = len;
    *alu = 0;
    POP(1)
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timadd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMADD) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timsum(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMSUM) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timmul(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMMUL) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timdiv(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMDIV) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timcnc(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMCNC) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_enmsel(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMSEL) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_enmmux(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMMUX) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_enmequ(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMEQU) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_enmneq(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_ENMNEQ) ");
#endif

    //POP()
    return RC_OK;
}

#endif /* PLCVM_ALU_2_H_ */
