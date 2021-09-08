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

// TODO: implement
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
            switch (*n) {
                case VT_INT: {
                    *((VTYPE(VT_INT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_DINT: {
                    *((VTYPE(VT_DINT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_LINT: {
                    *((VTYPE(VT_LINT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_BYTE: {
                    *((VTYPE(VT_BYTE)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_UINT:
                case VT_WORD: {
                    *((VTYPE(VT_UINT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_UDINT:
                case VT_DWORD: {
                    *((VTYPE(VT_UDINT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_ULINT:
                case VT_LWORD: {
                    *((VTYPE(VT_ULINT)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_REAL: {
                    *((VTYPE(VT_REAL)*)vm->hp[0].var) = *t;
                    break;
                }

                case VT_LREAL: {
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
                    ((VTYPE(VT_STRING)*)vm->hp[0].var)[0] = *(VTYPE(VT_CHAR)*)vm->hp[*t].var;
                    vm->hp[0].len = 1;
                    break;
                }

                case VT_WSTRING: { // TODO: implement
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

// TODO: implement
uint8_t fnc_alu_selmux(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_SELMUX) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_cmpgrt(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPGRT) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_cmpgeq(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPGEQ) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_cmpequ(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPEQU) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_cmples(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPLES) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_cmplth(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPLTH) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_cmpneq(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_CMPNEQ) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_strlen(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRLEN) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_strlft(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRLFT) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_strrgh(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRRGH) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_strmid(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRMID) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_strcnc(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRCNC) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_strins(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRINS) ");
#endif
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_strdel(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_STRDEL) ");
#endif
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
