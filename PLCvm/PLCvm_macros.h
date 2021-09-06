/*
 * PLCvm_macros.h
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

#ifndef PLCVM_MACROS_H_
#define PLCVM_MACROS_H_

#define       OP(x) (x & 0xe000)                                     // operand
#define   ARG_OP(x) (x & 0x1fff)                                     // argument of operand
#define  ARG_LIT(x) (x & 0x7fff)                                     // literal

#define   ALU_OP(x) ((x >> 8) & 0x1F)                                // alu operation
#define   ALU_DS(x) (x & 0x03)                                       // alu data stack
#define   ALU_RS(x) ((x >> 2) & 0x03)                                // alu return stack
#define   ALU_EX(x) ((ALU_DS(x) == 0x03)|((ALU_RS(x) == 0x03) << 1)) // extended bits
#define  ALU_ARG(x) ((x & 0xFF))                                     // arguments of alu
#define VAR_TYPE(x) ((x & 0xF800) >> 11)                             // variable type

#endif /* PLCVM_MACROS_H_ */
