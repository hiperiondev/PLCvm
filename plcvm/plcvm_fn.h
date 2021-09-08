/*
 * PLCvm_fn.h
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

#ifndef PLCVM_FN_H_
#define PLCVM_FN_H_

#include "plcvm_alu_0.h"
#include "plcvm_alu_1.h"
#include "plcvm_alu_2.h"
#include "plcvm_alu_3.h"

uint8_t (*alu_fn[])(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux)= {
    fnc_alu_alutop,
    fnc_alu_aluscn,
    fnc_alu_alutrs,
    fnc_alu_aluget,
    fnc_alu_aluput,
    fnc_alu_aludpl,
    fnc_alu_aludml,
    fnc_alu_aluand,
    fnc_alu_alubor,
    fnc_alu_aluxor,
    fnc_alu_alunot,
    fnc_alu_aludec,
    fnc_alu_alueq0,
    fnc_alu_aluequ,
    fnc_alu_aluucp,
    fnc_alu_alucmp,
    fnc_alu_alursh,
    fnc_alu_alulsh,
    fnc_alu_alugsp,
    fnc_alu_alugrs,
    fnc_alu_alussp,
    fnc_alu_alusrp,
    fnc_alu_alureg,
    fnc_alu_alusrg,
    fnc_alu_aluumd,
    fnc_alu_alumod,
    fnc_alu_alunxt,
    fnc_alu_alugpc,
    fnc_alu_aluexf,
    fnc_alu_alulod,
    fnc_alu_alustr,
    fnc_alu_alubye,

    fnc_alu_cnvtot,
    fnc_alu_numabs,
    fnc_alu_numsqr,
    fnc_alu_numlon,
    fnc_alu_numlog,
    fnc_alu_numexp,
    fnc_alu_numsin,
    fnc_alu_numcos,
    fnc_alu_numtan,
    fnc_alu_numasn,
    fnc_alu_numacs,
    fnc_alu_numatn,
    fnc_alu_athadd,
    fnc_alu_athmul,
    fnc_alu_athsub,
    fnc_alu_athdiv,
    fnc_alu_athmod,
    fnc_alu_athexp,
    fnc_alu_athmov,
    fnc_alu_bitshl,
    fnc_alu_bitshr,
    fnc_alu_bitror,
    fnc_alu_bitrol,
    fnc_alu_cmpand,
    fnc_alu_cmporf,
    fnc_alu_cmpxor,
    fnc_alu_cmpnot,
    fnc_alu_selsel,
    fnc_alu_selmax,
    fnc_alu_selmin,
    fnc_alu_sellmt,
    fnc_alu_alutop,

    fnc_alu_varcvr,
    fnc_alu_varsvr,
    fnc_alu_selmux,
    fnc_alu_cmpgrt,
    fnc_alu_cmpgeq,
    fnc_alu_cmpequ,
    fnc_alu_cmples,
    fnc_alu_cmplth,
    fnc_alu_cmpneq,
    fnc_alu_strlen,
    fnc_alu_strlft,
    fnc_alu_strrgh,
    fnc_alu_strmid,
    fnc_alu_strcnc,
    fnc_alu_strins,
    fnc_alu_strdel,
    fnc_alu_chrrpl,
    fnc_alu_chrfnd,
    fnc_alu_timadd,
    fnc_alu_timsum,
    fnc_alu_timmul,
    fnc_alu_timdiv,
    fnc_alu_timcnc,
    fnc_alu_enmsel,
    fnc_alu_enmmux,
    fnc_alu_enmequ,
    fnc_alu_enmneq,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,

    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
    fnc_alu_alutop,
};
#endif /* PLCVM_FN_H_ */
