/*
 * plcvm_timedate.h
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

#ifndef PLCVM_TIMEDATE_H_
#define PLCVM_TIMEDATE_H_

// TODO: implement
uint8_t fnc_alu_timadd(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_TIMADD) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timsum(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_TIMSUM) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timmul(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_EX2_TIMMUL) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timdiv(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_TIMDIV) ");
#endif

    //POP()
    return RC_OK;
}

// TODO: implement
uint8_t fnc_alu_timcnc(vm_t *vm, uint16_t word, uint16_t *t, uint16_t *n, uint16_t *r, uint16_t *alu, uint32_t *aux) {
#ifdef DEBUG
    DBG_PRINT("ALU_OP_TIMCNC) ");
#endif

    //POP()
    return RC_OK;
}

#endif /*PLCVM_TIMEDATE_H_*/
