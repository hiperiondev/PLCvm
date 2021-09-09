/*
 * PLCvm.h
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

#ifndef __PLCVM_H__
#define __PLCVM_H__

#include <stdbool.h>
#include <inttypes.h>

#include "plcvm_macros.h"
#include "plcvm_enum.h"
#include "plcvm_types.h"
#include "plcvm_alu_0.h"
#include "plcvm_alu_1.h"
#include "plcvm_alu_2.h"
#include "plcvm_alu_3.h"
#include "plcvm_fn.h"

/////////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG
    #if DEBUG == 1
    #define DBG_PRINT(fmt, args...)  \
        fprintf(stderr, "" fmt, ##args)
#endif
#if DEBUG == 2
    #define DBG_PRINT(fmt, args...)  \
       fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif
#else
    #define DBG_PRINT(fmt, args...)
#endif

/////////////////////////////////////////////////////////////////////////////////////
/*
## Instruction Set Encoding

        +---------------------------------------------------------------+
        | F | E | D | C | B | A | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
        +---------------------------------------------------------------+
        | 1 |                    LITERAL VALUE                          |
        +---------------------------------------------------------------+
        | 0 | 0 | 0 |            BRANCH TARGET ADDRESS                  |
        +---------------------------------------------------------------+
        | 0 | 0 | 1 |            CONDITIONAL BRANCH TARGET ADDRESS      |
        +---------------------------------------------------------------+
        | 0 | 1 | 0 |            CALL TARGET ADDRESS                    |
        +---------------------------------------------------------------+
        | 0 | 1 | 1 |   ALU OPERATION   |T2N|T2R|N2T|R2P| RSTACK| DSTACK|
        +---------------------------------------------------------------+
        | F | E | D | C | B | A | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
        +---------------------------------------------------------------+

        T   : Top of data stack
        N   : Next on data stack
        PC  : Program Counter

        LITERAL VALUES : push a value onto the data stack
        CONDITIONAL    : BRANCHS pop and test the T
        CALLS          : PC+1 onto the return stack

        T2N : Move T to N
        T2R : Move T to top of return stack
        N2T : Move the new value of T (or D) to N
        R2P : Move top of return stack to PC

        RSTACK and DSTACK :
        00 = 0
        01 = +1
        10 = -1
        11 = extended bit (used for alu extended operations)
*/
/////////////////////////////////////////////////////////////////////////////////////


static inline vm_t* PLCvm_init(uint16_t ramSize, uint8_t rsSize, uint8_t dsSize,  uint8_t regQty) {
    vm_t* vm     =     (vm_t *) malloc(sizeof(vm_t));
    vm->RAM      = (uint16_t *) malloc(sizeof(uint16_t) * ramSize);
    vm->rs       = (uint16_t *) malloc(sizeof(uint16_t) * rsSize);
    vm->ds       = (uint16_t *) malloc(sizeof(uint16_t) * dsSize);
    vm->reg      = (uint16_t *) malloc(sizeof(uint16_t) * regQty);
    vm->hp       =    (var_t *) calloc(2048, sizeof(var_t));
    vm->reg_size = regQty;
    vm->ds_size  = dsSize;
    vm->rs_size  = rsSize;
#ifdef UNDER_OVER
    vm->RAM_size = ramSize;
#endif
    vm->pc = 0;
    vm->dp = 0;
    vm->rp = 0;
    vm->exception = 0;

    return vm;
}

//////////////////// vm ////////////////////
static inline uint8_t PLCvm_step(uint16_t word, vm_t *vm) {
#ifdef DEBUG
    DBG_PRINT("[pc:%04x/dp:%02x/rp:%02x/rs[rp]:%04x/t:%04x/n:%04x/n-1:%04x/n-2:%04x] step(%04x):"
            ,vm->pc, vm->dp, vm->rp, vm->rs[vm->rp], vm->t, vm->ds[vm->dp], vm->ds[vm->dp-1], vm->ds[vm->dp-2], word);
#endif

    uint8_t return_status = RC_OK;
    static const int8_t delta[] = { 0, 1, -1, 0 };
    vm->pc++;

////////// irq
    if ((vm->status & ST_IRQ) && !(vm->status & ST_IMK)) {
#ifdef DEBUG
        DBG_PRINT("IRQ    (%04x)\n",ARG_OP(vm->t_ext));
#endif
#ifdef UNDER_OVER
        if (vm->rp == vm->ds_size) {
#ifdef DEBUG
            DBG_PRINT("RC_RS_OVER_FLOW\n");
#endif
            return RC_RS_OVER_FLOW;
        }
#endif
        vm->rs[++vm->rp] = vm->pc + 1;
        vm->pc = ARG_OP(vm->irq_addr);
        vm->status &= ~ST_IRQ;
        vm->status |= ST_IMK;
        return RC_IRQ;
    }

////////// literal
    if (word & OP_LIT) {
#ifdef DEBUG
        DBG_PRINT("OP_LIT (%04x)\n",ARG_LIT(word));
#endif
#ifdef UNDER_OVER
        if (vm->dp == vm->ds_size) {
#ifdef DEBUG
            DBG_PRINT("RC_DS_OVER_FLOW\n");
#endif
            return RC_DS_OVER_FLOW;
        }
        if (vm->pc == vm->RAM_size) {
#ifdef DEBUG
            DBG_PRINT("RC_PC_OVER_FLOW\n");
#endif
            return RC_PC_OVER_FLOW;
        }
#endif
        vm->ds[++vm->dp] = vm->t;
        vm->t = ARG_LIT(word);
        return RC_OK;
    }

    switch (OP(word)) {

////////// 0branch
        case OP_JMZ:
#ifdef DEBUG
            DBG_PRINT("OP_JZ  (%04x)\n",ARG_OP(word));
#endif
#ifdef UNDER_OVER
            if (vm->dp == 0) {
#ifdef DEBUG
                DBG_PRINT("RC_RS_UNDER_FLOW\n");
#endif
                return RC_DS_UNDER_FLOW;
            }
#endif
            vm->pc = !vm->t ? ARG_OP(word) : vm->pc;
            vm->t = vm->ds[vm->dp--];
#ifdef UNDER_OVER
            if (vm->pc > vm->RAM_size) {
#ifdef DEBUG
                DBG_PRINT("RC_PC_OVER_FLOW\n");
#endif
                return RC_PC_OVER_FLOW;
            }
#endif
            break;

////////// jump
        case OP_JMP:
#ifdef DEBUG
            DBG_PRINT("OP_JMP (%04x)\n",ARG_OP(word));
#endif
            vm->pc = ARG_OP(word);
            break;

////////// call
        case OP_CLL:
#ifdef DEBUG
            DBG_PRINT("OP_CALL(%04x)\n",ARG_OP(word));
#endif
#ifdef UNDER_OVER
            if (vm->rp == vm->rs_size) {
#ifdef DEBUG
                DBG_PRINT("RC_RS_OVER_FLOW\n");
#endif
                return RC_RS_OVER_FLOW;
            }
#endif
            vm->rs[++vm->rp] = vm->pc << 1;
            vm->pc = ARG_OP(word);
            break;

////////// alu
        case OP_ALU: {
#ifdef DEBUG
            DBG_PRINT("OP_ALU (");
#endif
            uint16_t t = vm->t;
            uint16_t n = vm->ds[vm->dp];
            uint16_t r = vm->rs[vm->rp];
            uint16_t alu = t;
            uint32_t aux = 0;
#ifdef DEBUG
            uint8_t r2p = 0;
#endif
            if (word & ALU_F_R2P) {
                vm->pc = vm->rs[vm->rp] >> 1;
#ifdef DEBUG
                r2p = 1;
#endif
            }

////////// alu function
            return_status = alu_fn[ALU_OP(word) + 32 * ALU_EX(word)](vm, word, &t, &n, &r, &alu, &aux);
//////////

#ifdef DEBUG
            DBG_PRINT("[dp:%d|dr:%d] ", delta[ALU_DS(word)], delta[ALU_RS(word)]);
#endif
            vm->dp += delta[ALU_DS(word)];
            vm->rp += delta[ALU_RS(word)];

            if (word & ALU_F_T2N) {
#ifdef DEBUG
                DBG_PRINT("/ALU_F_T2N ");
#endif
                vm->ds[vm->dp] = vm->t;
            }
            if (word & ALU_F_T2R) {
#ifdef DEBUG
                DBG_PRINT("/ALU_F_T2R ");
#endif
                vm->rs[vm->rp] = vm->t;
            }
            if (word & ALU_F_N2T) {
#ifdef DEBUG
                DBG_PRINT("/ALU_F_N2T ");
#endif
                vm->t = n;
            } else {
                vm->t = alu;
            }
#ifdef DEBUG
            if (r2p)
                DBG_PRINT("/ALU_F_R2P ");
#endif

#ifdef UNDER_OVER
            if (vm->rp == vm->RAM_size) {
#ifdef DEBUG
                DBG_PRINT("RC_PC_OVER_FLOW\n");
#endif
                return RC_PC_OVER_FLOW;
            }
#endif
        }
    }

#ifdef UNDER_OVER
    if (vm->rp > vm->rs_size) {
#ifdef DEBUG
        DBG_PRINT("\nRC_RS_OVER_FLOW_end");
#endif
        return RC_RS_OVER_FLOW;
    }
    if (vm->dp > vm->ds_size) {
#ifdef DEBUG
        DBG_PRINT("\nRC_DS_OVER_FLOW_end\n");
#endif
        return RC_DS_OVER_FLOW;
    }
    if (vm->dp < 0) {
#ifdef DEBUG
        DBG_PRINT("\nRC_DS_UNDER_FLOW_end\n");
#endif
        return RC_DS_UNDER_FLOW;
    }
    if (vm->rp < 0) {
#ifdef DEBUG
        DBG_PRINT("\nRC_RS_UNDER_FLOW_end\n");
#endif
        return RC_RS_UNDER_FLOW;
    }
#endif
    //exitvm:
    vm->exception = return_status;
    return return_status;
}

#endif /* __PLCVM_H__ */
