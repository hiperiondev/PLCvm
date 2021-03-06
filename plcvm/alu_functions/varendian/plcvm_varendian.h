/*
 * plcvm_varendian.h
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

#ifndef PLCVM_VARENDIAN_H_
#define PLCVM_VARENDIAN_H_

uint8_t fnc_alu_varcvr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_VARCVR) ");
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
            CC_VAR(varp, 1, VT_BOOL)
            break;
        }

        case VT_SINT: {
            CC_VAR(varp, 1, VT_SINT)
            break;
        }

        case VT_INT: {
            CC_VAR(varp, 1, VT_INT)
            break;
        }

        case VT_DINT: {
            CC_VAR(varp, 1, VT_DINT)
            break;
        }

        case VT_LINT: {
            CC_VAR(varp, 1, VT_LINT)
            break;
        }

        case VT_USINT:
        case VT_BYTE: {
            CC_VAR(varp, 1, VT_USINT)
            break;
        }

        case VT_UINT:
        case VT_WORD: {
            CC_VAR(varp, 1, VT_UINT)
            break;
        }

        case VT_UDINT:
        case VT_DWORD: {
            CC_VAR(varp, 1, VT_DINT)
            break;
        }

        case VT_ULINT:
        case VT_LWORD: {
            CC_VAR(varp, 1, VT_ULINT)
            break;
        }

        case VT_REAL: {
            CC_VAR(varp, 1, VT_REAL)
            break;
        }

        case VT_LREAL: {
            CC_VAR(varp, 1, VT_LREAL)
            break;
        }

        case VT_TIME: {
           CC_VAR(varp, 1, VT_TIME)
            break;
        }

        case VT_DATE: {
            CC_VAR(varp, 1, VT_DATE)
            ((date_t*) vm->hp[varp].var)->date.day = 1;
            ((date_t*) vm->hp[varp].var)->date.month = 1;
            ((date_t*) vm->hp[varp].var)->date.year = 1;
            break;
        }

        case VT_LDATE: {
            CC_VAR(varp, 1, VT_LDATE)
            break;
        }

        case VT_TOD: {
            CC_VAR(varp, 1, VT_TOD)
            break;
        }

        case VT_LTOD: { // TODO: implement
            break;
        }

        case VT_DT: {
            CC_VAR(varp, 1, VT_DT)
            VAR_PTR(VT_DT,varp)->dat.date.date.day = 1;
            VAR_PTR(VT_DT,varp)->dat.date.date.month = 1;
            VAR_PTR(VT_DT,varp)->dat.date.date.year = 1;
            break;
        }

        case VT_LDT: {
            CC_VAR(varp, 1, VT_LDT)
            break;
        }

        case VT_STRING: {
            CC_VAR(varp, *n, VT_STRING)
            POP(1)
            break;
        }

        case VT_WSTRING: {
            CC_VAR(varp, *n, VT_WSTRING)
            POP(1)
            break;
        }

        case VT_CHAR: {
            CC_VAR(varp, 1, VT_CHAR)
            break;
        }

        case VT_SE: {
            CC_VAR(varp, 1, VT_SE);
            *VAR_PTR(VT_SE,varp) = *n;
            POP(1)
            //fnc_sev(vm, varp);
            break;
        }

        default:
            return RC_VTYPE_UNKNOWN;
    }

    if (tmp)
        vm->hp[varp].type = (uint8_t) *t;

    //if (*t & 0x20)
        //fnc_var_retain(vm, varp);
    //else if (*t & 40)
        //fnc_var_persist(vm, varp);

    *alu = varp;
    POP(1)
    return RC_OK;
}

uint8_t fnc_alu_varsvr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_VARSVR) ");
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
            *VAR_PTR(VT_CHAR,*t) = *n;
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
            *VAR_PTR(VT_DWORD,*t) = (((VTYPE(VT_DWORD))*n << 16) | (VTYPE(VT_DWORD))PICK(2));
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
            *VAR_PTR(VT_DWORD,*t) = (((VTYPE(VT_LWORD))*n << 48) | ((VTYPE(VT_LWORD))PICK(2) << 32) | ((VTYPE(VT_LWORD))PICK(3) << 16)| (VTYPE(VT_LWORD))PICK(4) << 4);
            pop = 4;
            break;
        }

        case VT_STRING: {
            if (*n > vm->hp[*t].len)
                return RC_VAR_OOR;

            uint64_t cnt;
            for (cnt = 0; cnt < *n; cnt++) {
                VAR_PTR(VT_STRING,*t)[cnt] = PICK(2 - cnt);
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
                VAR_PTR(VT_WSTRING,*t)[cnt] = PICK(2 - cnt);
                VAR_PTR(VT_WSTRING,*t)[cnt + 1] = PICK(2 - cnt + 1);
            }
            vm->hp[*t].len = *n;
            pop = (*n * 2) + 1;
            break;
            break;
        }

        case VT_SE: { // TODO: implement
            break;
        }
    }

    POP(pop)
    return RC_OK;
}

// TODO: finish implementation
uint8_t fnc_alu_vartot(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_VARTOT) ");
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

// TODO: implement
uint8_t fnc_alu_enctbi(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
    *alu = 0;
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_enctli(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
    *alu = 0;
    return RC_OK;
}

#endif /*PLCVM_VARENDIAN_H_*/
