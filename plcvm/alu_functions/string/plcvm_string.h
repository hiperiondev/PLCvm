/*
 * plcvm_string.h
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

#ifndef PLCVM_STRING_H_
#define PLCVM_STRING_H_

uint8_t fnc_alu_strlen(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_STRLEN) ");
#endif
    if (!((vm->hp[*t].type == VT_STRING) || (vm->hp[*t].type == VT_WSTRING)))
        return RC_VAR_NOT_ALLWD;

    *alu = vm->hp[*t].len;
    return RC_OK;
}


uint8_t fnc_alu_strlft(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_STRLFT) ");
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
    DBG_PRINT("ALU_OP_STRRGH) ");
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
    DBG_PRINT("ALU_OP_STRMID) ");
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
    DBG_PRINT("ALU_OP_STRCNC) ");
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
    DBG_PRINT("ALU_OP_STRINS) ");
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
    DBG_PRINT("ALU_OP_STRDEL) ");
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
    DBG_PRINT("ALU_OP_STRRPL) ");
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
    DBG_PRINT("ALU_OP_STRFND) ");
#endif



    //vm->hp[0].len = len;
    *alu = 0;
    POP(1)
    return RC_OK;
}

#endif /*PLCVM_STRING_H_*/
