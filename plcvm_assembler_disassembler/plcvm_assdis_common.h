/*
 * PLCvm_assdis_common.h
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

#ifndef __PLCVM_ASSDIS_COMMON_H__
#define __PLCVM_ASSDIS_COMMON_H__

#include <ctype.h>
#include <string.h>

#include "plcvm_assdis_common.h"

#define EP(x) [x] = #x  // enum print

void trim(char *s) {
    char *p = s;
     int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}

void simplifyWhiteSpace(char *src) {
    char *dst = src;

    for (; *src; ++dst, ++src) {
        *dst = *src;
        if (isspace(*src))
            while (isspace(*(src + 1)))
                ++src;
    }
    *dst = '\0';
}

int getWords(char *base, char target[40][80]) {
    int n = 0, i, j = 0;

    trim(base);
    simplifyWhiteSpace(base);
    for (i = 0; 1; i++) {
        if (base[i] != ' ') {
            target[n][j++] = base[i];
        } else {
            target[n][j++] = '\0';
            n++;
            j = 0;
        }
        if (base[i] == '\0')
            break;
    }
    return n;
}

char *strlwr(char *str) {
    unsigned char *p = (unsigned char *)str;
    while (*p) {
        *p = tolower((unsigned char) *p);
        p++;
    }
    return str;
}

char *removeSubStr(char *str, const char *substr) {
    size_t m1 = strlen(str);
    size_t m2 = strlen(substr);
    if (!(m1 < m2)) {
        for (char *p = str; (p = strstr(p, substr)) != NULL;) {
            size_t n = m1 - (p + m2 - str);
            memmove(p, p + m2, n + 1);
        }
    }
    return str;
}

void removePrefix(char *str) {
    char strLocal[20];

    strcpy(strLocal, removeSubStr(str, "ALU_"));
    strcpy(strLocal, removeSubStr(str, "OP_"));
    strcpy(strLocal, removeSubStr(str, "F_"));
    strcpy(str, strLocal);
}

const char *ALU[] = {
    EP(ALU_OP_ALUTOP),
    EP(ALU_OP_ALUSCN),
    EP(ALU_OP_ALUTRS),
    EP(ALU_OP_ALUGET),
    EP(ALU_OP_ALUPUT),
    EP(ALU_OP_ALUDPL),
    EP(ALU_OP_ALUDML),
    EP(ALU_OP_ALUAND),
    EP(ALU_OP_ALUBOR),
    EP(ALU_OP_ALUXOR),
    EP(ALU_OP_ALUNOT),
    EP(ALU_OP_ALUDEC),
    EP(ALU_OP_ALUEQ0),
    EP(ALU_OP_ALUEQU),
    EP(ALU_OP_ALUUCP),
    EP(ALU_OP_ALUCMP),
    EP(ALU_OP_ALURSH),
    EP(ALU_OP_ALULSH),
    EP(ALU_OP_ALUGSP),
    EP(ALU_OP_ALUGRS),
    EP(ALU_OP_ALUSSP),
    EP(ALU_OP_ALUSRP),
    EP(ALU_OP_ALUREG),
    EP(ALU_OP_ALUSRG),
    EP(ALU_OP_ALUUMD),
    EP(ALU_OP_ALUMOD),
    EP(ALU_OP_ALUNXT),
    EP(ALU_OP_ALUGPC),
    EP(ALU_OP_ALUEXF),
    EP(ALU_OP_ALULOD),
    EP(ALU_OP_ALUSTR),
    EP(ALU_OP_ALUBYE)
};

const char *ALU_EX1[] = {
    EP(ALU_OP_CMPAND),
    EP(ALU_OP_CMPORF),
    EP(ALU_OP_CMPXOR),
    EP(ALU_OP_CMPNOT),
    EP(ALU_OP_ENCTBI),
    EP(ALU_OP_ENCTLI),
    EP(ALU_OP_NUMABS),
    EP(ALU_OP_NUMSQR),
    EP(ALU_OP_NUMLON),
    EP(ALU_OP_NUMLOG),
    EP(ALU_OP_NUMSIN),
    EP(ALU_OP_NUMCOS),
    EP(ALU_OP_NUMTAN),
    EP(ALU_OP_NUMASN),
    EP(ALU_OP_NUMACS),
    EP(ALU_OP_NUMATN),
    EP(ALU_OP_ATHADD),
    EP(ALU_OP_ATHMUL),
    EP(ALU_OP_ATHSUB),
    EP(ALU_OP_ATHDIV),
    EP(ALU_OP_ATHMOD),
    EP(ALU_OP_ATHEXP),
    EP(ALU_OP_ATHMOV),
    EP(ALU_OP_BITSHL),
    EP(ALU_OP_BITSHR),
    EP(ALU_OP_BITROR),
    EP(ALU_OP_BITROL),
    EP(ALU_OP_TIMADD),
    EP(ALU_OP_TIMSUM),
    EP(ALU_OP_TIMMUL),
    EP(ALU_OP_TIMDIV),
    EP(ALU_OP_TIMCNC)
};

const char *ALU_EX2[] = {
    EP(ALU_OP_VARCVR),
    EP(ALU_OP_VARSVR),
    EP(ALU_OP_VARTOT),
    EP(ALU_OP_SELMAX),
    EP(ALU_OP_SELMIN),
    EP(ALU_OP_SELMUX),
    EP(ALU_OP_STRLEN),
    EP(ALU_OP_STRLFT),
    EP(ALU_OP_STRRGH),
    EP(ALU_OP_STRMID),
    EP(ALU_OP_STRCNC),
    EP(ALU_OP_STRINS),
    EP(ALU_OP_STRDEL),
    EP(ALU_OP_STRRPL),
    EP(ALU_OP_STRFND),
    EP(ALU_OP_ENMSEL),
    EP(ALU_OP_ENMMUX),
    EP(ALU_OP_ENMEQU),
    EP(ALU_OP_ENMNEQ),
    EP(ALU_OP_02_x13),
    EP(ALU_OP_02_x14),
    EP(ALU_OP_02_x14),
    EP(ALU_OP_02_x16),
    EP(ALU_OP_02_x17),
    EP(ALU_OP_02_x18),
    EP(ALU_OP_02_x19),
    EP(ALU_OP_02_x1a),
    EP(ALU_OP_02_x1b),
    EP(ALU_OP_02_x1c),
    EP(ALU_OP_02_x1d),
    EP(ALU_OP_02_x1e),
    EP(ALU_OP_02_x1f)
};

const char *ALU_EX3[] = {
    EP(ALU_OP_03_x00),
    EP(ALU_OP_03_x01),
    EP(ALU_OP_03_x02),
    EP(ALU_OP_03_x03),
    EP(ALU_OP_03_x04),
    EP(ALU_OP_03_x05),
    EP(ALU_OP_03_x06),
    EP(ALU_OP_03_x07),
    EP(ALU_OP_03_x08),
    EP(ALU_OP_03_x09),
    EP(ALU_OP_03_x0a),
    EP(ALU_OP_03_x0c),
    EP(ALU_OP_03_x0d),
    EP(ALU_OP_03_x0c),
    EP(ALU_OP_03_x0d),
    EP(ALU_OP_03_x0f),
    EP(ALU_OP_03_x10),
    EP(ALU_OP_03_x11),
    EP(ALU_OP_03_x12),
    EP(ALU_OP_03_x13),
    EP(ALU_OP_03_x14),
    EP(ALU_OP_03_x15),
    EP(ALU_OP_03_x16),
    EP(ALU_OP_03_x17),
    EP(ALU_OP_03_x18),
    EP(ALU_OP_03_x19),
    EP(ALU_OP_03_x1a),
    EP(ALU_OP_03_x1b),
    EP(ALU_OP_03_x1c),
    EP(ALU_OP_03_x1d),
    EP(ALU_OP_03_x1e),
    EP(ALU_OP_03_x1f)
};

const char *OPTYPE[] = {
    EP(OP_LIT),
    EP(OP_ALU),
    EP(OP_JMP),
    EP(OP_JMZ),
    EP(OP_CLL)
};

const char *VMFLAGS[] = {
    EP(ALU_F_T2N),
    EP(ALU_F_T2R),
    EP(ALU_F_N2T),
    EP(ALU_F_R2P)
};

const char *DELTA[] = {
    "d+1",
    "d-1",
    "ex0",
    "r+1",
    "r-1",
    "ex1"
};

const uint8_t DELTA_CODE[] = {
    0x1,
    0x2,
    0x3,
    0x4,
    0x8,
    0xC
};

#endif
