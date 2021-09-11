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

#include <stdint.h>

#define                  EP(x) [x] = #x                                         // enum print

#define                  OP(x) (x & 0xe000)                                     // operand
#define              ARG_OP(x) (x & 0x1fff)                                     // argument of operand
#define             ARG_LIT(x) (x & 0x7fff)                                     // literal

#define              ALU_OP(x) ((x >> 8) & 0x1F)                                // alu operation
#define              ALU_DS(x) (x & 0x03)                                       // alu data stack
#define              ALU_RS(x) ((x >> 2) & 0x03)                                // alu return stack
#define              ALU_EX(x) ((ALU_DS(x) == 0x03)|((ALU_RS(x) == 0x03) << 1)) // extended bits
#define             ALU_ARG(x) ((x & 0xFF))                                     // arguments of alu

#define                 POP(x) vm->dp -= x;
#define                PICK(x) vm->ds[vm->dp - x]

#define            VAR_TYPE(x) ((x & 0xF800) >> 11)                             // variable type
#define VAR_COMPLETE(type, id) ((type <<11)|(id))
#define               VTYPE(x) TYPE_##x
#define      VAR_PTR(type, id) ((VTYPE(type)*)(vm->hp[id].var))

#define              FREE_ACC if (vm->hp[0].var != NULL) \
                                   free(vm->hp[0].var);
#define       CC_VAR(id, n, t) vm->hp[id].var = (VTYPE(t)*) calloc(n, sizeof(VTYPE(t))); \
                                   vm->hp[id].type = t;

#define             ANY_NUM(x) ( \
                                   (x == VT_SINT)  || \
                                   (x == VT_INT)   || \
                                   (x == VT_DINT)  || \
                                   (x == VT_LINT)  || \
                                   (x == VT_USINT) || \
                                   (x == VT_UINT)  || \
                                   (x == VT_UDINT) || \
                                   (x == VT_ULINT) || \
                                   (x == VT_REAL)  || \
                                   (x == VT_LREAL) || \
                                   (x == VT_BYTE)  || \
                                   (x == VT_WORD)  || \
                                   (x == VT_DWORD) || \
                                   (x == VT_LWORD) \
                               )
#define            ANY_REAL(x) ((x == VT_REAL) || (x == VT_LREAL))
#define             ANY_BIT(x) ( \
                                   (x == VT_BOOL)  || \
                                   (x == VT_SINT)  || \
                                   (x == VT_INT)   || \
                                   (x == VT_DINT)  || \
                                   (x == VT_LINT)  || \
                                   (x == VT_USINT) || \
                                   (x == VT_UINT)  || \
                                   (x == VT_UDINT) || \
                                   (x == VT_ULINT) || \
                                   (x == VT_BYTE)  || \
                                   (x == VT_WORD)  || \
                                   (x == VT_DWORD) || \
                                   (x == VT_LWORD) \
                                )

#define          ANY_STRING(x) (x == VT_STRING)  || \
                                   (x == VT_WSTRING)

/////// internal variable types ///////
#define TYPE_VT_BOOL    bool
#define TYPE_VT_SINT    int8_t
#define TYPE_VT_INT     int16_t
#define TYPE_VT_DINT    int32_t
#define TYPE_VT_LINT    int64_t
#define TYPE_VT_USINT   uint8_t
#define TYPE_VT_UINT    uint16_t
#define TYPE_VT_UDINT   uint32_t
#define TYPE_VT_ULINT   uint64_t
#define TYPE_VT_REAL    float
#define TYPE_VT_LREAL   double
#define TYPE_VT_STRING  char
#define TYPE_VT_BYTE    uint8_t
#define TYPE_VT_WORD    uint16_t
#define TYPE_VT_DWORD   uint32_t
#define TYPE_VT_LWORD   uint64_t
#define TYPE_VT_WSTRING wchar_t
#define TYPE_VT_CHAR    char
#define TYPE_VT_WCHAR   wchar_t
#define TYPE_VT_SE      uint16_t
#define TYPE_VT_LDT     uint64_t
#define TYPE_VT_DT      dat_t
#define TYPE_VT_TIME    time_t
#define TYPE_VT_DATE    date_t
#define TYPE_VT_LDATE   int64_t
#define TYPE_VT_TOD     tod_t

#endif /* PLCVM_MACROS_H_ */
