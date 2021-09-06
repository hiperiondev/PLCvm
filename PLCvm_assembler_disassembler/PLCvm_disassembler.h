/*
 * PLCvm_disassembler.h
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

#ifndef __PLCVM_DISASSEMBLER_H__
#define __PLCVM_DISASSEMBLER_H__

#include "PLCvm.h"
#include "PLCvm_assdis_common.h"

char* plcvm_disassembly(uint16_t word) {
    static char dis[100];

    int _delta[] = {
             0,
             1,
            -1,
             0
    };
    char hex[6];
    char tmpstr[6];
    int f = 0;
    strcpy(dis, "");

    if (word & OP_LIT) {
        sprintf(hex, "%04x", ARG_LIT(word));
        strcat(dis, OPTYPE[OP_LIT]);
        strcat(dis, " ");
        strcat(dis, hex);
    } else {
        switch (OP(word)) {
        case OP_JMZ:
            sprintf(hex, "%04x",  ARG_OP(word));
            strcat(dis, OPTYPE[OP_JMZ]);
            strcat(dis, " ");
            strcat(dis, hex);
            break;
        case OP_JMP:
            sprintf(hex, "%04x",  ARG_OP(word));
            strcat(dis, OPTYPE[OP_JMP]);
            strcat(dis, " ");
            strcat(dis, hex);
            break;
        case OP_CLL:
            sprintf(hex, "%04x",  ARG_OP(word));
            strcat(dis, OPTYPE[OP_CLL]);
            strcat(dis, " ");
            strcat(dis, hex);
            break;
        case OP_ALU:
            strcpy(dis, ALU[ALU_OP(word)]);
            if ((strcmp(dis, "ALU_OP_LOD") == 0) || (strcmp(dis, "ALU_OP_STR") == 0)) {
                sprintf(tmpstr, " %d", ALU_ARG(word));
                strcat(dis, tmpstr);
            } else {
                strcat(dis, " (");
                if (word & ALU_F_R2P) {
                    f = 1;
                    strcat(dis, VMFLAGS[ALU_F_R2P]);
                }
                if (word & ALU_F_T2N) {
                    if (f == 1)
                        strcat(dis, "|");
                    f = 1;
                    strcat(dis, VMFLAGS[ALU_F_T2N]);
                }
                if (word & ALU_F_T2R) {
                    if (f == 1)
                        strcat(dis, "|");
                    f = 1;
                    strcat(dis, VMFLAGS[ALU_F_T2R]);
                }
                if (word & ALU_F_N2T) {
                    if (f == 1)
                        strcat(dis, "|");
                    strcat(dis, VMFLAGS[ALU_F_N2T]);
                }

                strcat(dis, ") [dp:");
                sprintf(hex, "%*d|", 2, _delta[ALU_DS(word)]);
                strcat(dis, hex);
                strcat(dis, "rp:");
                sprintf(hex, "%*d", 2, _delta[ALU_RS(word)]);
                strcat(dis, hex);
                strcat(dis, "]");
            }
        }
    }
    removePrefix(dis);
    return strlwr(dis);
}

#endif
