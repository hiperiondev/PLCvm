/*
 * PLCvm_enum.h
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

#ifndef PLCVM_ENUM_H_
#define PLCVM_ENUM_H_

// operation types
enum vm_optypes {
    OP_JMP = 0x0000,  // jump
    OP_JMZ = 0x2000,  // jump if zero
    OP_CLL = 0x4000,  // call
    OP_ALU = 0x6000,  // alu
    OP_LIT = 0x8000   // literal
};

// ALU flags
enum vm_aluflgs {
    ALU_F_T2N = 0x80,  // move T to N
    ALU_F_T2R = 0x40,  // move T to R
    ALU_F_N2T = 0x20,  // move N to T
    ALU_F_R2P = 0x10   // move R to PC
};

enum alu_0 {
    // standard ALU operations
    ALU_OP_ALUTOP = 0x00, // t
    ALU_OP_ALUSCN = 0x01, // n
    ALU_OP_ALUTRS = 0x02, // top of return stack
    ALU_OP_ALUGET = 0x03, // load from address t
    ALU_OP_ALUPUT = 0x04, // store n to address t
    ALU_OP_ALUDPL = 0x05, // double cell addition
    ALU_OP_ALUDML = 0x06, // double cell multiply
    ALU_OP_ALUAND = 0x07, // bitwise and
    ALU_OP_ALUBOR = 0x08, // bitwise or
    ALU_OP_ALUXOR = 0x09, // bitwise xor
    ALU_OP_ALUNOT = 0x0a, // bitwise inversion
    ALU_OP_ALUDEC = 0x0b, // decrement
    ALU_OP_ALUEQ0 = 0x0c, // equal to zero
    ALU_OP_ALUEQU = 0x0d, // equality test
    ALU_OP_ALUUCP = 0x0e, // unsigned comparison (n-t)
    ALU_OP_ALUCMP = 0x0f, // signed comparison (n<t)
    ALU_OP_ALURSH = 0x10, // logical right shift
    ALU_OP_ALULSH = 0x11, // logical left shift
    ALU_OP_ALUGSP = 0x12, // depth of data stack
    ALU_OP_ALUGRS = 0x13, // depth of return stack
    ALU_OP_ALUSSP = 0x14, // set data stack depth
    ALU_OP_ALUSRP = 0x15, // set return stack depth
    ALU_OP_ALUREG = 0x16, // get register t (t=0xff status; t=0xfe last exception )
    ALU_OP_ALUSRG = 0x17, // set n on register t (status t == 0xff)
    ALU_OP_ALUUMD = 0x18, // u/mod
    ALU_OP_ALUMOD = 0x19, // /mod
    ALU_OP_ALUNXT = 0x1a, // compare top and 2nd element of return stack. If not eq increment 2nd else drop top and 2nd
    ALU_OP_ALUGPC = 0x1b, // PC to t
    ALU_OP_ALUEXF = 0x1c, // execute external function
    ALU_OP_ALULOD = 0x1d, // load from stack position (from bottom)
    ALU_OP_ALUSTR = 0x1e, // store to stack position (from bottom)
    ALU_OP_ALUBYE = 0x1f  // return
};

enum alu_ex_1 { // can't use DSTACK
    // boolean functions
    ALU_OP_CMPAND = 0x00, // AND [t: qty, n+:vars return: acc]
    ALU_OP_CMPORF = 0x01, // OR [t: qty, n+:vars return: acc]
    ALU_OP_CMPXOR = 0x02, // XOR [t: qty, n+:vars return: acc]
    ALU_OP_CMPNOT = 0x03, // NOT [t: variable return: acc]
    // endian conversion
    ALU_OP_ENCTBI = 0x04, // TO_BIG_ENDIAN
    ALU_OP_ENCTLI = 0x05, // TO_LITTLE_ENDIAN
    // standard functions of one numeric variable
    ALU_OP_NUMABS = 0x06, // ABS [t: variable return: acc]
    ALU_OP_NUMSQR = 0x07, // SQRT [t: variable return: acc]
    ALU_OP_NUMLON = 0x08, // LN [t: variable return: acc]
    ALU_OP_NUMLOG = 0x09, // LOG [t: variable return: acc]
    ALU_OP_NUMSIN = 0x0a, // SIN [t: variable return: acc]
    ALU_OP_NUMCOS = 0x0b, // COS [t: variable return: acc]
    ALU_OP_NUMTAN = 0x0c, // TAN [t: variable return: acc]
    ALU_OP_NUMASN = 0x0d, // ASIN [t: variable return: acc]
    ALU_OP_NUMACS = 0x0e, // ACOS [t: variable return: acc]
    ALU_OP_NUMATN = 0x0f, // ATAN [t: variable return: acc]
    // standard arithmetic functions
    ALU_OP_ATHADD = 0x10, // ADD [t: qty, n+:vars return: acc]
    ALU_OP_ATHMUL = 0x11, // MUL [t: qty, n+:vars return: acc]
    ALU_OP_ATHSUB = 0x12, // SUB [t: variable n: variable return: acc]
    ALU_OP_ATHDIV = 0x13, // DIV [t: variable n: variable return: acc]
    ALU_OP_ATHMOD = 0x14, // MOD [t: variable n: variable return: acc]
    ALU_OP_ATHEXP = 0x15, // EXPT [t: variable n: variable return: acc]
    ALU_OP_ATHMOV = 0x16, // MOVE []
    // bit functions
    ALU_OP_BITSHL = 0x17, // SHL [t: variable n: variable return: acc]
    ALU_OP_BITSHR = 0x18, // SHR [t: variable n: variable return: acc]
    ALU_OP_BITROR = 0x19, // ROR [t: variable n: variable return: acc]
    ALU_OP_BITROL = 0x1a, // ROL [t: variable n: variable return: acc]
    // functions of time data types
    ALU_OP_TIMADD = 0x1b, // ADD []
    ALU_OP_TIMSUM = 0x1c, // SUB []
    ALU_OP_TIMMUL = 0x1d, // MUL []
    ALU_OP_TIMDIV = 0x1e, // DIV []
    ALU_OP_TIMCNC = 0x1f, // CONCAT_DATE_TOD []
};

enum alu_ex_2 { // can't use RSTACK
    // variable functions
    ALU_OP_VARCVR = 0x00, // create variable t:type, n:len (used on not fixed types ex: STRING). return t:pointer var [tttttppppppppppp]; type: [0000 0000 0prt tttt] t: type, r:retain p:persistent
    ALU_OP_VARSVR = 0x01, // set variable t:pointer var, n[+]: depend on type
    ALU_OP_VARTOT = 0x02, // convert to type t: variable, n: target type, return: acc
    // standard selection functions
    ALU_OP_SELMAX = 0x03, // MAX [t: qty, n+:vars return: acc]
    ALU_OP_SELMIN = 0x04, // MIN [t: qty, n+:vars return: acc]
    ALU_OP_SELMUX = 0x05, // MUX [t: entries. n+: variables (n: K). return: variable selected]
    // character string functions
    ALU_OP_STRLEN = 0x06, // LEN [t: variable return: acc]
    ALU_OP_STRLFT = 0x07, // LEFT [t: variable n: qty return: acc]
    ALU_OP_STRRGH = 0x08, // RIGHT [t: variable n: qty return: acc]
    ALU_OP_STRMID = 0x09, // MID [t: variable, n:pos n+1:length return: acc]
    ALU_OP_STRCNC = 0x0a, // CONCAT [t: entries n+: variables return: acc]
    ALU_OP_STRINS = 0x0b, // INSERT []
    ALU_OP_STRDEL = 0x0c, // DELETE []
    ALU_OP_STRRPL = 0x0d, // REPLACE []
    ALU_OP_STRFND = 0x0e, // FIND []
    // functions of enumerated data types
    ALU_OP_ENMSEL = 0x0f, // SEL []
    ALU_OP_ENMMUX = 0x10, // MUX []
    ALU_OP_ENMEQU = 0x11, // EQ []
    ALU_OP_ENMNEQ = 0x12, // NE []
    // not implemented
    ALU_OP_02_x13 = 0x13, // not implemented
    ALU_OP_02_x14 = 0x14, // not implemented
    ALU_OP_02_x15 = 0x15, // not implemented
    ALU_OP_02_x16 = 0x16, // not implemented
    ALU_OP_02_x17 = 0x17, // not implemented
    ALU_OP_02_x18 = 0x18, // not implemented
    ALU_OP_02_x19 = 0x19, // not implemented
    ALU_OP_02_x1a = 0x1a, // not implemented
    ALU_OP_02_x1b = 0x1b, // not implemented
    ALU_OP_02_x1c = 0x1c, // not implemented
    ALU_OP_02_x1d = 0x1d, // not implemented
    ALU_OP_02_x1e = 0x1e, // not implemented
    ALU_OP_02_x1f = 0x1f, // not implemented
};

enum alu_ex_3 { // can't use  RSTACK nor DSTACK
    ALU_OP_03_x00 = 0x00, // not implemented
    ALU_OP_03_x01 = 0x01, // not implemented
    ALU_OP_03_x02 = 0x02, // not implemented
    ALU_OP_03_x03 = 0x03, // not implemented
    ALU_OP_03_x04 = 0x04, // not implemented
    ALU_OP_03_x05 = 0x05, // not implemented
    ALU_OP_03_x06 = 0x06, // not implemented
    ALU_OP_03_x07 = 0x07, // not implemented
    ALU_OP_03_x08 = 0x08, // not implemented
    ALU_OP_03_x09 = 0x09, // not implemented
    ALU_OP_03_x0a = 0x0a, // not implemented
    ALU_OP_03_x0b = 0x0b, // not implemented
    ALU_OP_03_x0c = 0x0c, // not implemented
    ALU_OP_03_x0d = 0x0d, // not implemented
    ALU_OP_03_x0e = 0x0e, // not implemented
    ALU_OP_03_x0f = 0x0f, // not implemented
    ALU_OP_03_x10 = 0x10, // not implemented
    ALU_OP_03_x11 = 0x11, // not implemented
    ALU_OP_03_x12 = 0x12, // not implemented
    ALU_OP_03_x13 = 0x13, // not implemented
    ALU_OP_03_x14 = 0x14, // not implemented
    ALU_OP_03_x15 = 0x15, // not implemented
    ALU_OP_03_x16 = 0x16, // not implemented
    ALU_OP_03_x17 = 0x17, // not implemented
    ALU_OP_03_x18 = 0x18, // not implemented
    ALU_OP_03_x19 = 0x19, // not implemented
    ALU_OP_03_x1a = 0x1a, // not implemented
    ALU_OP_03_x1b = 0x1b, // not implemented
    ALU_OP_03_x1c = 0x1c, // not implemented
    ALU_OP_03_x1d = 0x1d, // not implemented
    ALU_OP_03_x1e = 0x1e, // not implemented
    ALU_OP_03_x1f = 0x1f, // not implemented
};

// return condition
enum vm_return {
    RC_OK            = 0x00, // ok
    RC_DS_UNDER_FLOW = 0x01, // data stack underflow
    RC_DS_OVER_FLOW  = 0x02, // data stack over flow
    RC_RS_OVER_FLOW  = 0x03, // return stack over flow
    RC_RS_UNDER_FLOW = 0x04, // return stack under flow
    RC_PC_OVER_FLOW  = 0x05, // program counter overflow
    RC_OP_UNKNOWN    = 0x06, // operator unknown
    RC_ROM_WRITE     = 0x07, // rom write
    RC_MEM_OVERFLOW  = 0x08, // out of memory access
    RC_IRQ           = 0x09, // irq execute
    RC_REG_UNKNOWN   = 0x0a, // unknown register
    RC_COLLISION     = 0x0b, // collision stack / local variable
    RC_NO_VAR_SPC    = 0x0c, // no more space for variables
    RC_VTYPE_UNKNOWN = 0x0d, // unknown variable type
    RC_NO_VAR        = 0x0e, // no allocated variable
    RC_VAR_TRUNC     = 0x0f, // result function on variable are truncated
    RC_VAR_OOR       = 0x10, // variable out of range (ex: string too long)
    RC_VAR_NOT_ALLWD = 0x11, // variable operation not allowed
    RC_VAR_ERROR     = 0x12, // variable generic error
    ///////////////////////////
    RC_EXPTN         = 0xfd, // alu exception
    RC_ERROR         = 0xfe, // generic error
    RC_BYE           = 0xff  // exit
};

// status register
enum vm_status {
    ST_CARRY    = 0x0001, // carry bit
    ST_IRQ      = 0x0002, // interrupt
    ST_IMK      = 0x0004, // interrupt mask
    ST_EXPTN    = 0x0008, // alu exception
    ST_AUTOINC0 = 0x0010, // autoincrement register #0 on every read
    ST_AUTOINC1 = 0x0020, // autoincrement register #1 on every read
    ST_AUTOINC2 = 0x0040, // autoincrement register #2 on every read
    ST_INDGET   = 0x0080, // indirect get on register #t
    ST_INDPUT   = 0x0100, // indirect put on register #t
    ST_LSDR     = 0x0200, // LOD and STR on data stack (0) or return stack (1)
//  ST_XXXX     = 0x0400, // not defined
//  ST_XXXX     = 0x0800, // not defined
//  ST_XXXX     = 0x1000  // not defined
//  ST_XXXX     = 0x2000, // not defined
//  ST_XXXX     = 0x4000, // not defined
//  ST_XXXX     = 0x8000, // not defined
};

// IEC 61131-3 data types
enum vm_vartypes {
    VT_EMPTY   = 0x00,  //
    VT_BOOL    = 0x01,  //
    VT_SINT    = 0x02,  //
    VT_INT     = 0x03,  //
    VT_DINT    = 0x04,  //
    VT_LINT    = 0x05,  //
    VT_USINT   = 0x06,  //
    VT_UINT    = 0x07,  //
    VT_UDINT   = 0x08,  //
    VT_ULINT   = 0x09,  //
    VT_REAL    = 0x0a,  //
    VT_LREAL   = 0x0b,  //
    VT_TIME    = 0x0c,  //
    VT_LTIME   = 0x0d,  //
    VT_DATE    = 0x0e,  //
    VT_LDATE   = 0x0f,  //
    VT_TOD     = 0x10,  //
    VT_LTOD    = 0x11,  //
    VT_DT      = 0x12,  //
    VT_LDT     = 0x13,  //
    VT_STRING  = 0x14,  // n: length
    VT_BYTE    = 0x15,  //
    VT_WORD    = 0x16,  //
    VT_DWORD   = 0x17,  //
    VT_LWORD   = 0x18,  //
    VT_WSTRING = 0x19,  // n: length
    VT_CHAR    = 0x1a,  //
    VT_WCHAR   = 0x1b,  //
    VT_SE      = 0x1c,  // single-element variables n: [aaaa bbbb 000p pttt] a,b: hierarchical address p:(00=I, 01=Q, 10=M) t:(000=X/None, 001=B, 010=W, 011=D, 100=L)
};

#endif /* PLCVM_ENUM_H_ */
