/*
 * PLCvm_types.h
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

#ifndef PLCVM_TYPES_H_
#define PLCVM_TYPES_H_

// variables on heap: [tttttppppppppppp] t:type, p: pointer to heap. max 2048 variables (var[0] accumulator, reserved)
typedef struct {
    uint8_t type;  // variable type
       void *var;  // pointer to malloc
   uint64_t len;   // length
} var_t;

typedef union {
    struct {
         uint8_t day;
         uint8_t month;
        uint16_t year;
    } date;
    uint32_t dw_date;
} date_t;

typedef union {
    struct {
        uint8_t csec;
        uint8_t sec;
        uint8_t min;
        uint8_t hour;
    } tod;
    uint32_t dw_tod;
} tod_t;

typedef struct {
    struct {
        tod_t tod;
        date_t date;
    } dat;
    uint64_t dw_dat;
} dat_t;

// Registers
typedef struct {
         uint8_t dp;          // data stack pointer
         uint8_t rp;          // return stack pointer
        uint16_t pc;          // program counter
        uint16_t t;           // top of data stack
        uint16_t irq_addr;    // irq address
        uint16_t status;      // status register
        uint16_t *reg;        // register vector
         uint8_t reg_size;    // register size
        uint16_t *RAM;        // ram vector
        uint16_t *rs;         // return stack vector
        uint16_t *ds;         // data stack vector
         uint8_t ds_size;     // data stack size
         uint8_t rs_size;     // return stack size
           var_t *hp;         // variables heap
         uint8_t exception;   // last exception
#ifdef UNDER_OVER
        uint16_t RAM_size;    // ram size
#endif
} vm_t;

#endif /* PLCVM_TYPES_H_ */
