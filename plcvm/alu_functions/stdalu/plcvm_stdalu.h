/*
 * PLCvm_stdalu.h
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

#ifndef PLCVM_STDALU_H_
#define PLCVM_STDALU_H_

uint16_t (*ext_funcs[EXT_FUNC])(vm_t *v);
extern uint8_t plcvm_mem_put (uint16_t addr, uint16_t value, vm_t*);
extern uint16_t plcvm_mem_get (uint16_t addr, vm_t*);

uint8_t fnc_alu_alutop(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_TOP) ");
#endif
    return RC_OK;
}

uint8_t fnc_alu_aluscn(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_SCN) ");
#endif
    *alu = *n;
    return RC_OK;
}

uint8_t fnc_alu_alutrs(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_TRS) ");
#endif
    *alu = *r;
    return RC_OK;
}

uint8_t fnc_alu_aluget(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_GET)  ");
#endif
#ifdef INDIRECT
                    if (vm->status & ST_INDGET) {
                        if (t > vm->reg_size - 1) return RC_REG_UNKNOWN;
                        aux = t;
                        t = vm->reg[t];
                    }
#endif
#ifdef UNDER_OVER
                    if ((t>>1) > vm->RAM_size) return RC_MEM_OVERFLOW;
#endif
    *alu = plcvm_mem_get(*t >> 1, vm);
#ifdef INDIRECT
#ifdef AUTOINCR
                    if ((t == 0) && (vm->status & ST_AUTOINC0)) vm->reg[t]++;
                    if ((t == 1) && (vm->status & ST_AUTOINC1)) vm->reg[t]++;
                    if ((t == 2) && (vm->status & ST_AUTOINC2)) vm->reg[t]++;
#endif
                    t = aux;
#endif
    return RC_OK;
}

uint8_t fnc_alu_aluput(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_PUT) ");
#endif
#ifdef INDIRECT
                    if (vm->status & ST_INDPUT) {
                        if (t > vm->reg_size - 1) return RC_REG_UNKNOWN;
                        aux = t;
                        t = vm->reg[t];
                    }
#endif
#ifdef UNDER_OVER
                    if ((t>>1) > vm->RAM_size) return RC_MEM_OVERFLOW;
#endif
    plcvm_mem_put(*t >> 1, *n, vm);
    *alu = vm->ds[--vm->dp];
#ifdef INDIRECT
#ifdef AUTOINCR
                    if ((t == 0) && (vm->status & ST_AUTOINC0)) vm->reg[t]++;
                    if ((t == 1) && (vm->status & ST_AUTOINC1)) vm->reg[t]++;
                    if ((t == 2) && (vm->status & ST_AUTOINC2)) vm->reg[t]++;
#endif
                    t = aux;
#endif
    return RC_OK;
}

uint8_t fnc_alu_aludpl(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_DPL) ");
#endif
    *aux = (uint32_t) (*t + *n);
#ifdef CARRY
                    aux            += (vm->status & ST_CARRY) >> 2;
                    vm->status     &= ~ST_RSVD;
                    vm->status     |= (vm->status & ST_CARRY) << 5;
                    vm->status     &= ~ST_CARRY;
                    vm->status     |= (uint32_t)(t > 0xffffffff - (n + ((vm->status & ST_CARRY) >> 7)))? ST_CARRY:0;
#endif
    *alu = *aux >> 16;
    vm->ds[vm->dp] = *aux;
    *n = *aux;
    return RC_OK;
}

uint8_t fnc_alu_aludml(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_DML) ");
#endif
    *aux = (uint32_t) (*t * *n);
    *n = *aux >> 16;
    vm->ds[vm->dp] = *aux;
    *alu = *aux;
#ifdef CARRY
                    vm->status &= ~ST_CARRY;
                    vm->status |= (t != 0 && aux / t != n) << 2;
#endif
    return RC_OK;
}

uint8_t fnc_alu_aluand(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_AND) ");
#endif
    *alu &= *n;
    return RC_OK;
}

uint8_t fnc_alu_alubor(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_BOR) ");
#endif
    *alu |= *n;
    return RC_OK;
}

uint8_t fnc_alu_aluxor(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_XOR) ");
#endif
    *alu ^= *n;
    return RC_OK;
}

uint8_t fnc_alu_alunot(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_NEG) ");
#endif
    *alu = ~*t;
    return RC_OK;
}

uint8_t fnc_alu_aludec(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_DEC) ");
#endif
    --*alu;
#ifdef CARRY
                    vm->status     &= ~ST_CARRY;
                    vm->status     |= (alu == 0xffff) << 2;
#endif
    return RC_OK;
}

uint8_t fnc_alu_alueq0(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EQ0) ");
#endif
    *alu = -(*t == 0);
    return RC_OK;
}

uint8_t fnc_alu_aluequ(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EQU) ");
#endif
    *alu = -(*t == *n);
    return RC_OK;
}

uint8_t fnc_alu_aluucp(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_UCP) ");
#endif
    *alu = -(*n < *t);
    return RC_OK;
}

uint8_t fnc_alu_alucmp(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_CMP) ");
#endif
    *alu = -((int16_t) *n < (int16_t) *t);
    return RC_OK;
}

uint8_t fnc_alu_alursh(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_RSH) ");
#endif

#ifdef CARRY
                    aux = (vm->status & ST_CARRY) << 13;
                    vm->status &= ~ST_CARRY;
                    vm->status |= (n & 0x0001) << 2;
#endif
    *alu = (*n >> *t);
#ifdef CARRY
                    alu |= aux;
#endif
    return RC_OK;
}

uint8_t fnc_alu_alulsh(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_LSH) ");
#endif
#ifdef CARRY
                    aux = (vm->status & ST_CARRY) >> 2;
                    vm->status &= ~ST_CARRY;
                    vm->status |= (n & 0x8000) >> 13;
#endif
    *alu = (*n << *t);
#ifdef CARRY
                    alu |= aux;
#endif
    return RC_OK;
}

uint8_t fnc_alu_alugsp(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_GSP) ");
#endif
    *alu = vm->dp << 1;
    return RC_OK;
}

uint8_t fnc_alu_alugrs(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_GRS) ");
#endif
    *alu = vm->rp << 1;
    return RC_OK;
}

uint8_t fnc_alu_alussp(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_SSP) ");
#endif
    vm->dp = *t >> 1;
    return RC_OK;
}

uint8_t fnc_alu_alusrp(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_SRP) ");
#endif
    vm->rp = *t >> 1;
    return RC_OK;
}

uint8_t fnc_alu_aluumd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_UMD) ");
#endif
    if (*t) {
        *aux = vm->ds[--vm->dp] | ((uint32_t) *n << 16);
        *alu = *aux / *t;
        *t = *aux % *t;
        *n = *t;
    } else {
        vm->status |= ST_EXPTN;
        return RC_EXPTN;
    }
    return RC_OK;
}

uint8_t fnc_alu_alumod(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_MOD) ");
#endif
    if (*t) {
        *alu = (int16_t) *n / *t;
        *t = (int16_t) *n % *t;
        *n = *t;
    } else {
        vm->status |= ST_EXPTN;
        return RC_EXPTN;
    }
    return RC_OK;
}

uint8_t fnc_alu_alureg(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_REG) ");
#endif
    if (*t == 0xff) {
        *alu = vm->status;
        return RC_OK;
    }

    if (*t == 0xff) {
        *alu = vm->exception;
        return RC_OK;
    }

    if (*t > vm->reg_size - 1)
        return RC_REG_UNKNOWN;
    *alu = vm->reg[*t];
#ifdef AUTOINCR
                   if ((*t == 0) && (vm->status & ST_AUTOINC0)) vm->reg[*t]++;
                   if ((*t == 1) && (vm->status & ST_AUTOINC1)) vm->reg[*t]++;
                   if ((*t == 2) && (vm->status & ST_AUTOINC2)) vm->reg[*t]++;
#endif
    return RC_OK;
}

uint8_t fnc_alu_alusrg(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_SRG) ");
#endif
    if (*t == 0xff) {
        vm->status = *t;
        return RC_OK;
    }
    if (*t > vm->reg_size - 1)
        return RC_REG_UNKNOWN;
    vm->reg[*t] = *n;
    return RC_OK;
}

uint8_t fnc_alu_alunxt(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_CRI) ");
#endif
    *alu = -(*r == vm->rs[vm->rp + 1]);
    if (alu) {
        vm->rp -= 2;
    } else {
        ++vm->rs[vm->rp + 1];
    }
    return RC_OK;
}

uint8_t fnc_alu_alugpc(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_GPC) ");
#endif
    *alu = vm->pc;
    return RC_OK;
}

uint8_t fnc_alu_aluexf(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EXF) ");
#endif
    *alu = (*ext_funcs[*t])(vm);
    return RC_OK;
}

uint8_t fnc_alu_alulod(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_LOD) ");
#endif
    if (vm->status & ST_LSDR) {
        *t = vm->rs[vm->rs_size - ALU_ARG(word) - 1];
    } else {
        *t = vm->ds[vm->ds_size - ALU_ARG(word) - 1];
    }
    return RC_OK;
}

uint8_t fnc_alu_alustr(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_STR) ");
#endif
    if (vm->status & ST_LSDR) {
        vm->rs[vm->rs_size - ALU_ARG(word) - 1] = *t;
    } else {
        vm->ds[vm->ds_size - ALU_ARG(word) - 1] = *t;
    }
    return RC_OK;
}

uint8_t fnc_alu_alubye(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_BYE) ");
#endif
    return RC_BYE;
    return RC_OK;
}

#endif /* PLCVM_STDALU_H_ */
